
#include "chassis_adapter.h"

ChassisAdapter::ChassisAdapter(YAML::Node yaml_conf) {}

void Init(ros::NodeHandle &node_handle) {
  // load mode
  if (conf_.mode == "gazebo") {
    LOG(INFO) << "Chassis mode: gazebo";
    imu_subscriber_ =
        node_handle.subscribe("imu", 1, &ChassisAdapter::imu_callback, this);
    pose_subscriber_ = node_handle.subscribe(
        "base_pose_ground_truth", 1, &ChassisAdapter::pose_callback, this);

  } else if (conf_.mode == "real") {
    LOG(INFO) << "Chassis mode: real";
    control_cmd_subscriber_ = node_handle.subscribe(
        "prius", 1, &ChassisAdapter::control_cmd_callback, this);
    imu_subscriber_ = node_handle.advertise<sensor_msgs::Imu>(
        "imu", 100, &ChassisAdapter::imu_callback, this);
    localization_subscriber_ = node_handle.subscribe(
        "tf", 1, &ChassisAdapter::localization_callback, this);

  } else {
    LOG(ERROR) << "Chassis mode: unknown!";
    ros::shutdown();
  }

  // send mode
  if (conf_.mode == "preiod") {
    LOG(INFO) << "Send mode: preiod";
    timer_ = node_handle.createTimer(ros::Duration(conf_.send_preiod),
                                     &ChassisAdapter::RunOnce, this);
  } else if (conf_.mode == "callback") {
    LOG(INFO) << "Send mode: callback";

  } else {
    LOG(ERROR) << "Send mode: unknown!";
    ros::shutdown();
  }
}

void RunOnce() {}

void Stop(){LOG(INFO) << "chassis adapter stop!"};
