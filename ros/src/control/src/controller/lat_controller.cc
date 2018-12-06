#include "ros/ros.h"
#include <ros/console.h>
#include "control/lat_controller.h"
#include "math/linear_quadratic_regulator.h"
#include "math/math_utils.h"
//#include "math/quaternion.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <string>
#include <utility>
#include <vector>

#include "Eigen/LU"

// #include "modules/common/configs/vehicle_config_helper.h"
// #include "modules/common/log.h"
// #include "modules/common/math/linear_quadratic_regulator.h"
// #include "modules/common/math/math_utils.h"
// #include "modules/common/math/quaternion.h"
// #include "modules/common/time/time.h"
// #include "modules/common/util/string_util.h"
// #include "modules/control/common/control_gflags.h"

namespace control {

// using apollo::common::ErrorCode;
// using apollo::common::Point3D;
// using apollo::common::Status;
// using apollo::common::TrajectoryPoint;
// using apollo::common::car_msgs::vehicle_stateProvider;
// using apollo::common::util::StrCat;
using Matrix = Eigen::MatrixXd;


LatController::LatController():name_("LQR-based LatController"){

}

bool LatController::LoadControlConf(const LatControllerConf *control_conf) {
  if (!control_conf) {
    ROS_INFO("[LatController] control_conf == nullptr");
    return false;
  }

  ts_ = control_conf->ts;
  cf_ = control_conf->cf;
  cr_ = control_conf->cr;
  preview_window_ = control_conf->preview_window;
  wheelbase_ = control_conf->wheel_base;
  steer_ratio_ = control_conf->steer_ratio;
  steer_single_direction_max_degree_ =
      control_conf->max_steer_angle / M_PI * 180;
  max_lat_acc_ = control_conf->max_lateral_acceleration;
  min_turn_radius_ = control_conf->min_turn_radius;

  const double mass_fl = control_conf->mass_fl;
  const double mass_fr = control_conf->mass_fr;
  const double mass_rl = control_conf->mass_rl;
  const double mass_rr = control_conf->mass_rr;
  const double mass_front = mass_fl + mass_fr;
  const double mass_rear = mass_rl + mass_rr;
  mass_ = mass_front + mass_rear;

  lf_ = wheelbase_ * (1.0 - mass_front / mass_);
  lr_ = wheelbase_ * (1.0 - mass_rear / mass_);

  // moment of inertia
  iz_ = lf_ * lf_ * mass_front + lr_ * lr_ * mass_rear;

  lqr_eps_ = control_conf->eps;
  lqr_max_iteration_ = control_conf->max_iteration;

  query_relative_time_ = control_conf->query_relative_time;

  minimum_speed_protection_ = control_conf->minimum_speed_protection;

  return true;
}

void LatController::Init(const LatControllerConf *control_conf) {
  if (!LoadControlConf(control_conf)) {
    ROS_INFO("failed to load control conf");
  }
  // Matrix init operations.
  const int matrix_size = basic_state_size_ + preview_window_;
  matrix_a_ = Matrix::Zero(basic_state_size_, basic_state_size_);
  matrix_ad_ = Matrix::Zero(basic_state_size_, basic_state_size_);
  matrix_adc_ = Matrix::Zero(matrix_size, matrix_size);

  matrix_a_(0, 1) = 1.0;
  matrix_a_(1, 2) = (cf_ + cr_) / mass_;
  matrix_a_(2, 3) = 1.0;
  matrix_a_(3, 2) = (lf_ * cf_ - lr_ * cr_) / iz_;

  matrix_a_coeff_ = Matrix::Zero(matrix_size, matrix_size);
  matrix_a_coeff_(1, 1) = -(cf_ + cr_) / mass_;
  matrix_a_coeff_(1, 3) = (lr_ * cr_ - lf_ * cf_) / mass_;
  matrix_a_coeff_(2, 3) = 1.0;
  matrix_a_coeff_(3, 1) = (lr_ * cr_ - lf_ * cf_) / iz_;
  matrix_a_coeff_(3, 3) = -1.0 * (lf_ * lf_ * cf_ + lr_ * lr_ * cr_) / iz_;

  matrix_b_ = Matrix::Zero(basic_state_size_, 1);
  matrix_bd_ = Matrix::Zero(basic_state_size_, 1);
  matrix_bdc_ = Matrix::Zero(matrix_size, 1);
  matrix_b_(1, 0) = cf_ / mass_;
  matrix_b_(3, 0) = lf_ * cf_ / iz_;
  matrix_bd_ = matrix_b_ * ts_;

  matrix_state_ = Matrix::Zero(matrix_size, 1);
  matrix_k_ = Matrix::Zero(1, matrix_size);
  matrix_r_ = Matrix::Identity(1, 1);
  matrix_q_ = Matrix::Zero(matrix_size, matrix_size);

  matrix_q_(0, 0) = control_conf->matrix_q1;
  matrix_q_(1, 1) = control_conf->matrix_q2;
  matrix_q_(2, 2) = control_conf->matrix_q3;
  matrix_q_(3, 3) = control_conf->matrix_q4;

  matrix_q_updated_ = matrix_q_;

}

void LatController::Stop() { }

std::string LatController::Name() const { return name_; }

void LatController::ComputeControlCommand(
      const car_msgs::trajectory &planning_published_trajectory,
      const car_msgs::vehicle_state &vehicle_state,
      car_msgs::control_cmd &cmd,
      car_msgs::lat_debug &debug){
    //vehicle_state.timestamp = 

  trajectory_analyzer_ = std::move(TrajectoryAnalyzer(&planning_published_trajectory));

  // Update state = [Lateral Error, Lateral Error Rate, Heading Error, Heading
  // Error Rate, preview lateral error1 , preview lateral error2, ...]
  UpdateState(vehicle_state,debug);

  UpdateMatrix(vehicle_state);

  // Compound discrete matrix with road preview model
  UpdateMatrixCompound();

  // Add gain scheduler for higher speed steering

  common::math::SolveLQRProblem(matrix_adc_, matrix_bdc_, matrix_q_,
                                  matrix_r_, lqr_eps_, lqr_max_iteration_,
                                  &matrix_k_);

  // feedback = - K * state
  // Convert vehicle steer angle from rad to degree and then to steer degree
  // then to 100% ratio
  const double steer_angle_feedback = -(matrix_k_ * matrix_state_)(0, 0) * 180 /
                                      M_PI * steer_ratio_ /
                                      steer_single_direction_max_degree_ * 100;

  const double steer_angle_feedforward = 0;//ComputeFeedForward(debug.curvature,vehicle_state);

  // Clamp the steer angle to -100.0 to 100.0
  double steer_angle = common::math::Clamp(steer_angle_feedback + steer_angle_feedforward, -100.0, 100.0);

//   if (FLAGS_set_steer_limit) {
//     const double steer_limit =
//         std::atan(max_lat_acc_ * min_turn_radius_ /
//                   (vehicle_state.linear_velocity *
//                    vehicle_state.linear_velocity)) *
//         steer_ratio_ * 180 / M_PI / steer_single_direction_max_degree_ * 100;

//     // Clamp the steer angle
//     double steer_angle_limited = 0;//common::math::Clamp(steer_angle, -steer_limit, steer_limit);
//     steer_angle_limited = digital_filter_.Filter(steer_angle_limited);
//     steer_angle = steer_angle_limited;
//     debug.set_steer_angle_limited(steer_angle_limited);
//   } else {
//     steer_angle = digital_filter_.Filter(steer_angle);
//   }

//   if (vehicle_state.linear_velocity <
//           FLAGS_lock_steer_speed &&
//       vehicle_state.gear() == canbus::Chassis::GEAR_DRIVE &&
//       chassis->driving_mode() == canbus::Chassis::COMPLETE_AUTO_DRIVE) {
//     steer_angle = pre_steer_angle_;
//   }
  pre_steer_angle_ = steer_angle;
  cmd.steer = steer_angle/100.0;
  // compute extra information for logging and debugging
  const double steer_angle_lateral_contribution =
      -matrix_k_(0, 0) * matrix_state_(0, 0) * 180 / M_PI * steer_ratio_ /
      steer_single_direction_max_degree_ * 100;

  const double steer_angle_lateral_rate_contribution =
      -matrix_k_(0, 1) * matrix_state_(1, 0) * 180 / M_PI * steer_ratio_ /
      steer_single_direction_max_degree_ * 100;

  const double steer_angle_heading_contribution =
      -matrix_k_(0, 2) * matrix_state_(2, 0) * 180 / M_PI * steer_ratio_ /
      steer_single_direction_max_degree_ * 100;

  const double steer_angle_heading_rate_contribution =
      -matrix_k_(0, 3) * matrix_state_(3, 0) * 180 / M_PI * steer_ratio_ /
      steer_single_direction_max_degree_ * 100;

  debug.heading = vehicle_state.heading;
  debug.steer_angle = steer_angle;
  debug.steer_angle_feedforward = steer_angle_feedforward;
  debug.steer_angle_lateral_contribution = steer_angle_lateral_contribution;
  debug.steer_angle_lateral_rate_contribution = steer_angle_lateral_rate_contribution;
  debug.steer_angle_heading_contribution = steer_angle_heading_contribution;
  debug.steer_angle_heading_rate_contribution = steer_angle_heading_rate_contribution;
  debug.steer_angle_feedback = steer_angle_feedback;
  //debug.steering_position = chassis->steering_percentage;
  debug.ref_speed = vehicle_state.linear_velocity;
}

void LatController::Reset() {}

void LatController::UpdateState(const car_msgs::vehicle_state &vehicle_state,car_msgs::lat_debug &debug) {
//   if (FLAGS_use_navigation_mode) {
//     ComputeLateralErrors(0.0, 0.0, vehicle_state.heading(),
//                          vehicle_state.linear_velocity,
//                          vehicle_state.angular_velocity,
//                          trajectory_analyzer_, debug);
//   } else {
    // const auto &com = vehicle_state.ComputeCOMPosition(lr_);
    ComputeLateralErrors(vehicle_state.x, vehicle_state.y,
                         vehicle_state.heading,
                         vehicle_state.linear_velocity,
                         vehicle_state.angular_velocity,
                         trajectory_analyzer_, debug);
//   }

  // State matrix update;
  // First four elements are fixed;
  matrix_state_(0, 0) = debug.lateral_error;
  matrix_state_(1, 0) = debug.lateral_error_rate;
  matrix_state_(2, 0) = debug.heading_error;
  matrix_state_(3, 0) = debug.heading_error_rate;

  // Next elements are depending on preview window size;
  for (int i = 0; i < preview_window_; ++i) {
    const double preview_time = ts_ * (i + 1);
    const auto preview_point =
        trajectory_analyzer_.QueryNearestPointByRelativeTime(preview_time);

    const auto matched_point = trajectory_analyzer_.QueryNearestPointByPosition(
        preview_point.x, preview_point.y);

    const double dx =
        preview_point.x - matched_point.x;
    const double dy =
        preview_point.y - matched_point.y;

    const double cos_matched_theta =
        std::cos(matched_point.theta);
    const double sin_matched_theta =
        std::sin(matched_point.theta);
    const double preview_d_error =
        cos_matched_theta * dy - sin_matched_theta * dx;

    matrix_state_(basic_state_size_ + i, 0) = preview_d_error;
  }
}

void LatController::UpdateMatrix(const car_msgs::vehicle_state &vehicle_state) {
  const double v = std::max(vehicle_state.linear_velocity,
                            minimum_speed_protection_);
  matrix_a_(1, 1) = matrix_a_coeff_(1, 1) / v;
  matrix_a_(1, 3) = matrix_a_coeff_(1, 3) / v;
  matrix_a_(3, 1) = matrix_a_coeff_(3, 1) / v;
  matrix_a_(3, 3) = matrix_a_coeff_(3, 3) / v;
  Matrix matrix_i = Matrix::Identity(matrix_a_.cols(), matrix_a_.cols());
  matrix_ad_ = (matrix_i - ts_ * 0.5 * matrix_a_).inverse() *
               (matrix_i + ts_ * 0.5 * matrix_a_);
}

void LatController::UpdateMatrixCompound() {
  // Initialize preview matrix
  matrix_adc_.block(0, 0, basic_state_size_, basic_state_size_) = matrix_ad_;
  matrix_bdc_.block(0, 0, basic_state_size_, 1) = matrix_bd_;
  if (preview_window_ > 0) {
    matrix_bdc_(matrix_bdc_.rows() - 1, 0) = 1;
    // Update A matrix;
    for (int i = 0; i < preview_window_ - 1; ++i) {
      matrix_adc_(basic_state_size_ + i, basic_state_size_ + 1 + i) = 1;
    }
  }
}

double LatController::ComputeFeedForward(double ref_curvature,const car_msgs::vehicle_state &vehicle_state){
  const double kv =
      lr_ * mass_ / 2 / cf_ / wheelbase_ - lf_ * mass_ / 2 / cr_ / wheelbase_;

  // then change it from rad to %
  const double v = vehicle_state.linear_velocity;
  const double steer_angle_feedforwardterm =
      (wheelbase_ * ref_curvature + kv * v * v * ref_curvature -
       matrix_k_(0, 2) *
           (lr_ * ref_curvature -
            lf_ * mass_ * v * v * ref_curvature / 2 / cr_ / wheelbase_)) *
      180 / M_PI * steer_ratio_ / steer_single_direction_max_degree_ * 100;
  return steer_angle_feedforwardterm;
}

void LatController::ComputeLateralErrors(
    const double x,
    const double y, 
    const double theta, 
    const double linear_v,
    const double angular_v, 
    const TrajectoryAnalyzer &trajectory_analyzer,
    car_msgs::lat_debug &debug) {

  car_msgs::trajectory_point target_point;

    //target_point = trajectory_analyzer.QueryNearestPointByAbsoluteTime(ros::Time::now().toSec());
  target_point = trajectory_analyzer.QueryNearestPointByPosition(x, y);

  const double dx = x - target_point.x;
  const double dy = y - target_point.y;

  const double cos_target_heading = std::cos(target_point.theta);
  const double sin_target_heading = std::sin(target_point.theta);

  double lateral_error = cos_target_heading * dy - sin_target_heading * dx;

  debug.lateral_error = lateral_error;

  double heading_error = common::math::NormalizeAngle(theta - target_point.theta);

  debug.heading_error = heading_error;

  auto lateral_error_dot = linear_v * std::sin(heading_error);
  debug.lateral_error_rate = lateral_error_dot;

  auto heading_error_rate = angular_v - target_point.kappa * target_point.speed;
  debug.heading_error_rate = heading_error_rate;

  debug.ref_heading = target_point.theta;

  debug.curvature = target_point.kappa;
//total_path_length
}
}//namespace control
