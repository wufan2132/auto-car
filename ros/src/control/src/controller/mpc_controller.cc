#include "ros/ros.h"
#include <ros/console.h>
#include "control/mpc_controller.h"
#include "math/math_utils.h"
//#include "math/quaternion.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <string>
#include <utility>
#include <vector>

#include "Eigen/LU"


// #include <algorithm>
// #include <cmath>
// #include <iomanip>
// #include <string>
// #include <utility>
// #include <vector>

// #include "Eigen/LU"

// #include "modules/common/configs/vehicle_config_helper.h"
// #include "modules/common/log.h"
// #include "modules/common/math/math_utils.h"
#include "math/mpc_solver.h"
// #include "modules/common/time/time.h"
// #include "modules/common/util/string_util.h"
// #include "modules/control/common/control_gflags.h"

// using apollo::common::TrajectoryPoint;
// using apollo::common::VehicleStateProvider;
// using apollo::common::time::Clock;
using Matrix = Eigen::MatrixXd;
// using apollo::common::VehicleConfigHelper;
namespace control {

MPCController::MPCController() : name_("MPC Controller") {}

MPCController::~MPCController() {}

bool MPCController::LoadControlConf(const MPCControllerConf *control_conf) {
  if (!control_conf) {
    // AERROR << "[MPCController] control_conf == nullptr";
    return false;
  }
  max_abs_speed_when_stopped_ = control_conf->max_abs_speed_when_stopped;

  ts_ = control_conf->ts;
  // CHECK_GT(ts_, 0.0) << "[MPCController] Invalid control update interval.";
  cf_ = control_conf->cf;
  cr_ = control_conf->cr;
  wheelbase_ = control_conf->wheel_base;
  steer_ratio_ = control_conf->steer_ratio;
  steer_single_direction_max_degree_ =
      control_conf->max_steer_angle * 180 / M_PI;
  max_lat_acc_ = control_conf->max_lateral_acceleration;
  wheel_single_direction_max_degree_ =
      steer_single_direction_max_degree_ / steer_ratio_ / 180 * M_PI;
  max_acceleration_ = control_conf->max_acceleration;
  max_deceleration_ = control_conf->max_deceleration;

  const double mass_fl = control_conf->mass_fl;
  const double mass_fr = control_conf->mass_fr;
  const double mass_rl = control_conf->mass_rl;
  const double mass_rr = control_conf->mass_rr;
  const double mass_front = mass_fl + mass_fr;
  const double mass_rear = mass_rl + mass_rr;
  mass_ = mass_front + mass_rear;

  lf_ = wheelbase_ * (1.0 - mass_front / mass_);
  lr_ = wheelbase_ * (1.0 - mass_rear / mass_);
  iz_ = lf_ * lf_ * mass_front + lr_ * lr_ * mass_rear;

  mpc_eps_ = control_conf->eps;
  mpc_max_iteration_ = control_conf->max_iteration;
  throttle_deadzone_ = control_conf->throttle_deadzone;
  brake_deadzone_ = control_conf->brake_deadzone;

  minimum_speed_protection_ = control_conf->minimum_speed_protection;
  standstill_acceleration_ =
      control_conf->standstill_acceleration;

  // AINFO << "MPC conf loaded";
  return true;
}


void MPCController::InitializeFilters(const MPCControllerConf *control_conf) {
  // Low pass filter
  // std::vector<double> den(3, 0.0);
  // std::vector<double> num(3, 0.0);
  // common::LpfCoefficients(
  //     ts_, control_conf->cutoff_freq, &den, &num);
  // digital_filter_.coefficients(den, num);
  // lateral_error_filter_ = common::MeanFilter(
  //     control_conf->mean_filter_window_size);
  // heading_error_filter_ = common::MeanFilter(
  //     control_conf->mean_filter_window_size);
}

void MPCController::Init(const MPCControllerConf *control_conf) {
  if (!LoadControlConf(control_conf)) {
    // AERROR << "failed to load control conf";
    // return Status(ErrorCode::CONTROL_COMPUTE_ERROR,
    //               "failed to load control_conf");
    return;
  }
  // Matrix init operations.
  matrix_a_ = Matrix::Zero(basic_state_size_, basic_state_size_);
  matrix_ad_ = Matrix::Zero(basic_state_size_, basic_state_size_);
  matrix_a_(0, 1) = 1.0;
  matrix_a_(1, 2) = (cf_ + cr_) / mass_;
  matrix_a_(2, 3) = 1.0;
  matrix_a_(3, 2) = (lf_ * cf_ - lr_ * cr_) / iz_;
  matrix_a_(4, 5) = 1.0;
  matrix_a_(5, 5) = 0.0;
  // TODO(QiL): expand the model to accommodate more combined states.

  matrix_a_coeff_ = Matrix::Zero(basic_state_size_, basic_state_size_);
  matrix_a_coeff_(1, 1) = -(cf_ + cr_) / mass_;
  matrix_a_coeff_(1, 3) = (lr_ * cr_ - lf_ * cf_) / mass_;
  matrix_a_coeff_(2, 3) = 1.0;
  matrix_a_coeff_(3, 1) = (lr_ * cr_ - lf_ * cf_) / iz_;
  matrix_a_coeff_(3, 3) = -1.0 * (lf_ * lf_ * cf_ + lr_ * lr_ * cr_) / iz_;

  matrix_b_ = Matrix::Zero(basic_state_size_, controls_);
  matrix_bd_ = Matrix::Zero(basic_state_size_, controls_);
  matrix_b_(1, 0) = cf_ / mass_;
  matrix_b_(3, 0) = lf_ * cf_ / iz_;
  matrix_b_(4, 1) = 0.0;
  matrix_b_(5, 1) = -1.0;
  matrix_bd_ = matrix_b_ * ts_;

  matrix_c_ = Matrix::Zero(basic_state_size_, 1);
  matrix_c_(5, 0) = 1.0;
  matrix_cd_ = Matrix::Zero(basic_state_size_, 1);

  matrix_state_ = Matrix::Zero(basic_state_size_, 1);
  matrix_k_ = Matrix::Zero(1, basic_state_size_);

  matrix_r_ = Matrix::Identity(controls_, controls_);

  matrix_q_ = Matrix::Zero(basic_state_size_, basic_state_size_);

  // int r_param_size = 2;
  // for (int i = 0; i < r_param_size; ++i) {
  //   matrix_r_(i, i) = control_conf->matrix_r(i);
  // }
  matrix_r_(0, 0) = control_conf->matrix_r1;
  matrix_r_(1, 1) = control_conf->matrix_r2;

  // int q_param_size = control_conf->matrix_q_size;
  // if (basic_state_size_ != q_param_size) {
  //   const auto error_msg = common::util::StrCat(
  //       "MPC controller error: matrix_q size: ", q_param_size,
  //       " in parameter file not equal to basic_state_size_: ",
  //       basic_state_size_);
  //   AERROR << error_msg;
  //   return Status(ErrorCode::CONTROL_COMPUTE_ERROR, error_msg);
  // }
  // for (int i = 0; i < q_param_size; ++i) {
  //   matrix_q_(i, i) = control_conf->matrix_q(i);
  // }
  matrix_q_(0,0) = control_conf->matrix_q1;
  matrix_q_(1,1) = control_conf->matrix_q2;
  matrix_q_(2,2) = control_conf->matrix_q3;
  matrix_q_(3,3) = control_conf->matrix_q4;
  matrix_q_(4,4) = control_conf->matrix_q5;
  matrix_q_(5,5) = control_conf->matrix_q6;

  // Update matrix_q_updated_ and matrix_r_updated_
  matrix_r_updated_ = matrix_r_;
  matrix_q_updated_ = matrix_q_;

  InitializeFilters(control_conf);

}


double MPCController::Wheel2SteerPct(const double wheel_angle) {
  return wheel_angle / wheel_single_direction_max_degree_ * 1;
}

std::string MPCController::Name() const { return name_; }

          
    // const localization::LocalizationEstimate *localization,
    // const canbus::Chassis *chassis,
    // const planning::ADCTrajectory *planning_published_trajectory,
    // ControlCommand *cmd)
void MPCController::ComputeControlCommand(
            const car_msgs::trajectory &planning_published_trajectory,
          const car_msgs::vehicle_state &vehicle_state,
          car_msgs::control_cmd &cmd,
          car_msgs::mpc_debug &debug){

  trajectory_analyzer_ = std::move(TrajectoryAnalyzer(&planning_published_trajectory));

  ComputeLongitudinalErrors(trajectory_analyzer_,vehicle_state,debug);

  // Update state
  UpdateState(vehicle_state,debug);

  UpdateMatrix(vehicle_state,debug);

  FeedforwardUpdate(debug);

  // Add gain scheduler for higher speed steering
  // if (FLAGS_enable_gain_scheduler) {
  //   matrix_q_updated_(0, 0) =
  //       matrix_q_(0, 0) *
  //       lat_err_interpolation_->Interpolate(
  //           VehicleStateProvider::instance()->linear_velocity());
  //   matrix_q_updated_(2, 2) =
  //       matrix_q_(2, 2) *
  //       heading_err_interpolation_->Interpolate(
  //           VehicleStateProvider::instance()->linear_velocity());
  //   steer_angle_feedforwardterm_updated_ =
  //       steer_angle_feedforwardterm_ *
  //       feedforwardterm_interpolation_->Interpolate(
  //           VehicleStateProvider::instance()->linear_velocity());
  //   matrix_r_updated_(0, 0) =
  //       matrix_r_(0, 0) *
  //       steer_weight_interpolation_->Interpolate(
  //           VehicleStateProvider::instance()->linear_velocity());
  // } else {
    matrix_q_updated_ = matrix_q_;
    matrix_r_updated_ = matrix_r_;
    steer_angle_feedforwardterm_updated_ = steer_angle_feedforwardterm_;
  // }

  debug.matrix_q_updated1 = matrix_q_updated_(0, 0);
  debug.matrix_q_updated2 = matrix_q_updated_(1, 1);
  debug.matrix_q_updated3 = matrix_q_updated_(2, 2);
  debug.matrix_q_updated4 = matrix_q_updated_(3, 3);

  debug.matrix_r_updated1 = matrix_r_updated_(0, 0);
  debug.matrix_r_updated2 = matrix_r_updated_(1, 1);

  Eigen::MatrixXd control_matrix(controls_, 1);
  control_matrix << 0, 0;

  Eigen::MatrixXd reference_state(basic_state_size_, 1);
  reference_state << 0, 0, 0, 0, 0, 0;

  std::vector<Eigen::MatrixXd> reference(horizon_, reference_state);

  Eigen::MatrixXd lower_bound(controls_, 1);
  lower_bound << -wheel_single_direction_max_degree_, max_deceleration_;

  Eigen::MatrixXd upper_bound(controls_, 1);
  upper_bound << wheel_single_direction_max_degree_, max_acceleration_;

  std::vector<Eigen::MatrixXd> control(horizon_, control_matrix);

  double mpc_start_timestamp = ros::Time::now().toSec();
  double steer_angle_feedback = 0.0;
  double acc_feedback = 0.0;

  if (common::math::SolveLinearMPC(
          matrix_ad_, matrix_bd_, matrix_cd_, matrix_q_updated_,
          matrix_r_updated_, lower_bound, upper_bound, matrix_state_, reference,
          mpc_eps_, mpc_max_iteration_, &control) != true) {
    //ROS_INFO("MPC solver failed");
    steer_angle_feedback = 0.0;
    acc_feedback = 0.0;
  } else {
    //ROS_INFO("MPC problem solved! ");
    steer_angle_feedback = Wheel2SteerPct(control[0](0, 0));
    acc_feedback = control[0](1, 0);
  }

  double mpc_end_timestamp = ros::Time::now().toSec();

  // ADEBUG << "MPC core algorithm: calculation time is: "
  //        << (mpc_end_timestamp - mpc_start_timestamp) * 1000 << " ms.";

  // TODO(QiL): evaluate whether need to add spline smoothing after the result

  double steer_angle =
      steer_angle_feedback + steer_angle_feedforwardterm_updated_;

  // Clamp the steer angle to -100.0 to 100.0
  steer_angle = common::math::Clamp(steer_angle, -100.0, 100.0);

  // if (FLAGS_set_steer_limit) {
  //   const double steer_limit =
  //       std::atan(max_lat_acc_ * wheelbase_ /
  //                 (vehicle_state.linear_velocity() *
  //                  vehicle_state.linear_velocity())) *
  //       steer_ratio_ * 180 / M_PI / steer_single_direction_max_degree_ * 100;

  //   // Clamp the steer angle
  //   double steer_angle_limited =
  //       common::math::Clamp(steer_angle, -steer_limit, steer_limit);
  //   steer_angle_limited = digital_filter_.Filter(steer_angle_limited);
  //   cmd.steering_target = steer_angle_limited ;
  //   debug.steer_angle_limited = steer_angle_limited;
  // } else {
    // steer_angle = digital_filter_.Filter(steer_angle);
    cmd.steer = steer_angle;
  // }

  debug.acceleration_cmd_closeloop = acc_feedback;

  double acceleration_cmd = acc_feedback + debug.acceleration_reference;
  // TODO(QiL): add pitch angle feed forward to accommodate for 3D control

  // debug.is_full_stop = false;
  // if (std::fabs(debug.acceleration_reference) <=
  //         FLAGS_max_acceleration_when_stopped &&
  //     std::fabs(debug.speed_reference) <=
  //         max_abs_speed_when_stopped_) {
  //   acceleration_cmd = standstill_acceleration_;
  //   AINFO << "Stop location reached";
  //   debug.is_full_stop = true;
  // }

  debug.acceleration_cmd = acceleration_cmd;

  double calibration_value = acceleration_cmd;
  // if (FLAGS_use_preview_speed_for_table) {
  //   calibration_value = control_interpolation_->Interpolate(
  //       std::make_pair(debug.speed_reference, acceleration_cmd));
  // } else {
  //   calibration_value = control_interpolation_->Interpolate(std::make_pair(
  //       VehicleStateProvider::instance()->linear_velocity(), acceleration_cmd));
  // }

  debug.calibration_value = calibration_value;

  double throttle_cmd = 0.0;
  double brake_cmd = 0.0;
  if (calibration_value >= 0) {
    throttle_cmd = calibration_value > throttle_deadzone_ ? calibration_value
                                                          : throttle_deadzone_;
    brake_cmd = 0.0;
  } else {
    throttle_cmd = 0.0;
    brake_cmd = -calibration_value > brake_deadzone_ ? -calibration_value
                                                     : brake_deadzone_;
  }

  // cmd.steering_rate = FLAGS_steer_angle_rate;
  cmd.throttle = throttle_cmd;
  cmd.brake = brake_cmd;

  debug.heading = vehicle_state.heading;
  // debug.steering_position = chassis->steering_percentage();
  debug.steer_angle = steer_angle;
  debug.steer_angle_feedforward = steer_angle_feedforwardterm_updated_;
  debug.steer_angle_feedback = steer_angle_feedback;
  // debug.steering_position = chassis->steering_percentage();

  // if (std::fabs(vehicle_state.linear_velocity <=
  //         max_abs_speed_when_stopped_ ||
  //     chassis->gear_location() == planning_published_trajectory->gear() ||
  //     chassis->gear_location() == canbus::Chassis::GEAR_NEUTRAL) {
  //   cmd.gear_location = planning_published_trajectory->gear;
  // } else {
  //   cmd.gear_location = chassis->gear_location;
  // }

}

void MPCController::Reset() {
  previous_heading_error_ = 0.0;
  previous_lateral_error_ = 0.0;
}


void MPCController::UpdateState(const car_msgs::vehicle_state &vehicle_state,car_msgs::mpc_debug &debug) {
  // const auto &com = VehicleStateProvider::instance()->ComputeCOMPosition(lr_);
  ComputeLateralErrors(vehicle_state.x, vehicle_state.y,
                       vehicle_state.heading,
                       vehicle_state.linear_velocity,
                       vehicle_state.angular_velocity,
                       trajectory_analyzer_, 
                       debug);

  // State matrix update;
  matrix_state_(0, 0) = debug.lateral_error;
  matrix_state_(1, 0) = debug.lateral_error_rate;
  matrix_state_(2, 0) = debug.heading_error;
  matrix_state_(3, 0) = debug.heading_error_rate;
  matrix_state_(4, 0) = debug.station_error;
  matrix_state_(5, 0) = debug.speed_error;
}

void MPCController::UpdateMatrix(const car_msgs::vehicle_state &vehicle_state,car_msgs::mpc_debug &debug) {
  const double v = std::max(vehicle_state.linear_velocity,
                            minimum_speed_protection_);
  matrix_a_(1, 1) = matrix_a_coeff_(1, 1) / v;
  matrix_a_(1, 3) = matrix_a_coeff_(1, 3) / v;
  matrix_a_(3, 1) = matrix_a_coeff_(3, 1) / v;
  matrix_a_(3, 3) = matrix_a_coeff_(3, 3) / v;

  Matrix matrix_i = Matrix::Identity(matrix_a_.cols(), matrix_a_.cols());
  matrix_ad_ = (matrix_i - ts_ * 0.5 * matrix_a_).inverse() *
               (matrix_i + ts_ * 0.5 * matrix_a_);

  matrix_c_(1, 0) = (lr_ * cr_ - lf_ * cf_) / mass_ / v - v;
  matrix_c_(3, 0) = -(lf_ * lf_ * cf_ + lr_ * lr_ * cr_) / iz_ / v;
  matrix_cd_ = matrix_c_ * debug.heading_error_rate * ts_;
}

void MPCController::FeedforwardUpdate(car_msgs::mpc_debug &debug) {
  steer_angle_feedforwardterm_ =
      Wheel2SteerPct(wheelbase_ * debug.curvature);
}

void MPCController::ComputeLateralErrors(
    const double x, const double y, const double theta, const double linear_v,
    const double angular_v, const TrajectoryAnalyzer &trajectory_analyzer,
    car_msgs::mpc_debug &debug) {
  const auto matched_point =
      trajectory_analyzer.QueryNearestPointByPosition(x, y);

  const double dx = x - matched_point.x;
  const double dy = y - matched_point.y;

  const double cos_matched_theta = std::cos(matched_point.theta);
  const double sin_matched_theta = std::sin(matched_point.theta);
  // d_error = cos_matched_theta * dy - sin_matched_theta * dx;
  debug.lateral_error = cos_matched_theta * dy - sin_matched_theta * dx;

  const double delta_theta =
      common::math::NormalizeAngle(theta - matched_point.theta);
  const double sin_delta_theta = std::sin(delta_theta);
  // d_error_dot = chassis_v * sin_delta_theta;
  debug.lateral_error_rate = linear_v * sin_delta_theta;

  // theta_error = delta_theta;
  debug.heading_error = delta_theta;
  // theta_error_dot = angular_v - matched_point.path_point().kappa() *
  // matched_point.speed();
  debug.heading_error_rate = angular_v - matched_point.kappa *
                                                matched_point.speed;

  // matched_theta = matched_point.path_point().theta();
  debug.ref_heading = matched_point.theta;
  // matched_kappa = matched_point.path_point().kappa();
  debug.curvature = matched_point.kappa;
}

void MPCController::ComputeLongitudinalErrors(
    const TrajectoryAnalyzer &trajectory_analyzer,
    const car_msgs::vehicle_state &vehicle_state,
    car_msgs::mpc_debug &debug) {
  // the decomposed vehicle motion onto Frenet frame
  // s: longitudinal accumulated distance along reference trajectory
  // s_dot: longitudinal velocity along reference trajectory
  // d: lateral distance w.r.t. reference trajectory
  // d_dot: lateral distance change rate, i.e. dd/dt
  double s_matched = 0.0;
  double s_dot_matched = 0.0;
  double d_matched = 0.0;
  double d_dot_matched = 0.0;

  const auto matched_point = trajectory_analyzer.QueryMatchedPathPoint(vehicle_state.x,vehicle_state.y);

  trajectory_analyzer.ToTrajectoryFrame(
      vehicle_state.x,
      vehicle_state.y,
      vehicle_state.heading,
      vehicle_state.linear_velocity, matched_point,
      &s_matched, &s_dot_matched, &d_matched, &d_dot_matched);

  const double current_control_time = ros::Time::now().toSec();

  car_msgs::trajectory_point reference_point =
      trajectory_analyzer.QueryNearestPointByAbsoluteTime(
          current_control_time);

  // ADEBUG << "matched point:" << matched_point.DebugString();
  // ADEBUG << "reference point:" << reference_point.DebugString();
  debug.station_error = reference_point.s - s_matched;
  debug.speed_error = reference_point.speed - s_dot_matched;

  debug.station_reference = reference_point.s;
  debug.speed_reference = reference_point.speed;
  debug.acceleration_reference = reference_point.accel;

  debug.station_feedback = s_matched;
  debug.speed_feedback = vehicle_state.linear_velocity;
}
} //namespace control