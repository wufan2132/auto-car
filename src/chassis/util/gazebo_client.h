#pragma once

#include <gazebo_msgs/SetModelState.h>
#include "yaml-cpp/yaml.h"
#include <ros/ros.h>

//用于给gazebo发送reset之类的指令
namespace chassis {
class GazeboClient {
 public:
  GazeboClient(const YAML::Node& yaml_conf);
  ~GazeboClient();

  void Init(ros::NodeHandle *node_handle);

  void ResetCar();

  void SetCar();

 private:
  // publisher
  ros::ServiceClient client_;
  // conf
  gazebo_msgs::ModelState default_state_;
};
}  // namespace chassis