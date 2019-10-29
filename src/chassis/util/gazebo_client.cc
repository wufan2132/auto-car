#include "gazebo_client.h"

namespace chassis {
GazeboClient::GazeboClient(const YAML::Node& yaml_conf) {
  default_state_.pose.position.x =
      yaml_conf["default_position"]["x"].as<double>();
  default_state_.pose.position.y =
      yaml_conf["default_position"]["y"].as<double>();
  default_state_.pose.position.z =
      yaml_conf["default_position"]["z"].as<double>();
  default_state_.pose.orientation.x =
      yaml_conf["default_orientation"]["x"].as<double>();
  default_state_.pose.orientation.y =
      yaml_conf["default_orientation"]["y"].as<double>();
  default_state_.pose.orientation.z =
      yaml_conf["default_orientation"]["z"].as<double>();
  default_state_.pose.orientation.w =
      yaml_conf["default_orientation"]["w"].as<double>();
  default_state_.twist.linear.x = yaml_conf["defaule_linear"]["x"].as<double>();
  default_state_.twist.linear.y = yaml_conf["defaule_linear"]["y"].as<double>();
  default_state_.twist.linear.z = yaml_conf["defaule_linear"]["z"].as<double>();
  default_state_.twist.angular.x =
      yaml_conf["defaule_angular"]["x"].as<double>();
  default_state_.twist.angular.y =
      yaml_conf["defaule_angular"]["y"].as<double>();
  default_state_.twist.angular.z =
      yaml_conf["defaule_angular"]["z"].as<double>();
}
GazeboClient::~GazeboClient() = default;

void GazeboClient::Init(ros::NodeHandle *node_handle) {
  client_ = node_handle->serviceClient<gazebo_msgs::SetModelState>(
      "/gazebo/set_model_state");
}

void GazeboClient::ResetCar() {
  gazebo_msgs::SetModelState objstate;
  objstate.request.model_state = default_state_;
  client_.call(objstate);
}

void GazeboClient::SetCar() {}

}  // namespace chassis