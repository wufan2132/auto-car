#include "gazebo_chassis.h"

namespace chassis {

//单位m
#define POSITION_OFFSET 1

using common::util::Activator;

GazeboChassis::GazeboChassis(const YAML::Node& yaml_conf) : Chassis(yaml_conf) {
  AINFO << "gazebo chassis start...";
  // load config
  conf_.send_mode = yaml_conf["gazebo_chassis"]["send_mode"].as<std::string>();
  conf_.send_period = yaml_conf["gazebo_chassis"]["send_period"].as<double>();
  //
  activator_ = std::make_unique<Activator>(2);
}

GazeboChassis::~GazeboChassis() { this->Stop(); }

void GazeboChassis::Init(ros::NodeHandle *node_handle) {
  // subscriber
  imu_subscriber_ = node_handle->subscribe(FLAGS_gazebo_imu_topic, 1,
                                           &GazeboChassis::ImuCallback, this);
  odo_subscriber_ = node_handle->subscribe(FLAGS_gazebo_Odometry_topic, 1,
                                           &GazeboChassis::OdoCallback, this);
  //
  localization_publisher_ = node_handle->advertise<car_msgs::localization>(
      FLAGS_chassis_localization_topic, 1000);
  car_state_publisher_ = node_handle->advertise<car_msgs::chassis>(
      FLAGS_chassis_car_state_topic, 1000);
  // send mode
  if (conf_.send_mode == "period") {
    AINFO << "Send mode: period";
    timer_ = node_handle->createTimer(ros::Duration(conf_.send_period),
                                      &GazeboChassis::OnTimer, this);
  } else if (conf_.send_mode == "callback") {
    AINFO << "Send mode: callback";

  } else {
    AERROR << "Send mode: unknown!";
    ros::shutdown();
  }
}

void GazeboChassis::OdoCallback(const nav_msgs::Odometry::ConstPtr &odo_msg) {
  activator_->Activate("OdoCallback");
  double roll, pitch, yaw;
  tf::Quaternion quat;
  //获取定位、航向信息
  car_localization_.header = odo_msg->header;

  tf::quaternionMsgToTF(odo_msg->pose.pose.orientation, quat);
  tf::Matrix3x3 RX = tf::Matrix3x3(quat);
  RX.getRPY(roll, pitch, yaw);
  car_localization_.angle.x = roll;
  car_localization_.angle.y = pitch;
  car_localization_.angle.z = yaw;
  car_localization_.angular_velocity = odo_msg->twist.twist.angular;

  car_localization_.position = odo_msg->pose.pose.position;
  car_localization_.position.x += POSITION_OFFSET * cos(yaw);
  car_localization_.position.y += POSITION_OFFSET * sin(yaw);

  double speed_roll, speed_pitch, speed_yaw;
  double speed_roll_out, speed_pitch_out, speed_yaw_out;
  tf::Quaternion speed_quat;
  //获取速度信息
  car_state_.header = odo_msg->header;
  //定义车的世界坐标系下的坐标
  //定义归一化的四元数
  //把四元数Q1的虚部取负值，表示和原四元数相反的旋转，相当于将theta变为-theta
  Eigen::Quaterniond Q1;
  //定义车在世界坐标系下的线速度
  Eigen::Matrix<double, 3, 1> Lw(odo_msg->twist.twist.linear.x,
                                 odo_msg->twist.twist.linear.y,
                                 odo_msg->twist.twist.linear.z);
  //定义车在车坐标下的线速度
  Eigen::Matrix<double, 3, 1> Lc;
  //给出世界坐标系下车的姿态
  Q1 = Eigen::Quaterniond(
           odo_msg->pose.pose.orientation.w, -odo_msg->pose.pose.orientation.x,
           -odo_msg->pose.pose.orientation.y, -odo_msg->pose.pose.orientation.z)
           .normalized();
  Lc = Q1 * Lw;

  car_state_.speed.x = Lc.x();
  car_state_.speed.y = Lc.y();
  car_state_.speed.z = Lc.z();

  if (conf_.send_mode == "callback" && activator_->State()) {
    localization_publisher_.publish(car_localization_);
    car_state_publisher_.publish(car_state_);
  }
}
void GazeboChassis::ImuCallback(const sensor_msgs::Imu::ConstPtr &imu_msg) {
  activator_->Activate("ImuCallback");
  car_state_.acc.x = -imu_msg->linear_acceleration.x;
  car_state_.acc.y = imu_msg->linear_acceleration.y;
  car_state_.acc.z = imu_msg->linear_acceleration.z;
}

void GazeboChassis::OnTimer(const ros::TimerEvent &) { this->RunOnce(); }
void GazeboChassis::RunOnce() {
  if (!activator_->State()) {
    // not ready
    return;
  }
  if (conf_.send_mode == "period") {
    localization_publisher_.publish(car_localization_);
    car_state_publisher_.publish(car_state_);
  }
};

void GazeboChassis::Stop() { AINFO << "gazebo chassis stop..."; };

};  // namespace chassis
