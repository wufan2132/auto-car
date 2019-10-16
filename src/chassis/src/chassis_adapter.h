#pragma once

#include <ros/ros.h>
#include <Eigen/Dense>
#include <memory>
#include "usart.h"


class ChassisAdapterConf;

class ChassisAdapter {
 public:
  ChassisAdapter(YAML::Node yaml_conf);
  ~ChassisAdapter() = default;

  void Init(ros::NodeHandle &node_handle);
  void RunOnce();
  void Stop();
  // callback
  void pose_callback(const nav_msgs::Odometry::ConstPtr &pose_msg);
  void imu_callback(const sensor_msgs::Imu::ConstPtr &imu_msg);
  void control_cmd_callback(const car_msgs::control_cmd &control_cmd_msg);
  void localization_callback(const tf2_msgs::TFMessage::ConstPtr &tf_msg);

 private:
  ChassisAdapterConf conf_;
  // Timer
  ros::Timer timer_;
  // subscriber
  ros::Subscriber pose_subscriber_;
  ros::Subscriber imu_subscriber_;
  ros::Subscriber control_cmd_subscriber_;
  ros::Publisher localization_subscriber_;
  // publisher
  ros::Publisher localization_publisher_;
  ros::Publisher pose_publisher_;
  ros::Publisher imu_publisher_;
  // message buf
  car_msgs::localization car_localization_;
  car_msgs::chassis car_pose_;
  //
  std::unique_ptr<Usart> usart_;
}

class ChassisAdapterConf {
  // 对接方式
  string mode;
  // usart
  string usart_name;
  // 发送模式, 周期发送或者回调发送
  string send_mode;
  double send_preiod;
}