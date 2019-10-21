#pragma once

#include "car_msgs/control_cmd.h"
#include "car_msgs/debug.h"
#include "car_msgs/trajectory.h"
#include "car_msgs/vehicle_state.h"
#include "yaml-cpp/yaml.h"

namespace control {
/**
 * @class Controller
 * @brief A proportional–integral–derivative controller for speed and steering
 using defualt integral hold
 */
class Controller {
 public:
  Controller(YAML::Node yaml_conf){};
  virtual ~Controller() = default;

  virtual void Init() = 0;
  virtual void Reset() = 0;
  virtual void Stop() = 0;

  virtual void ComputeControlCommand(
      const car_msgs::trajectory &planning_published_trajectory,
      const car_msgs::vehicle_state &vehicle_state, car_msgs::control_cmd *cmd,
      car_msgs::debug *debug_msg) = 0;
};

}  // namespace control