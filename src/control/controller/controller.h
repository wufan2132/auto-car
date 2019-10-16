#pragma once

#include "car_msgs/lat_debug.h"
#include "car_msgs/lon_debug.h"
#include "car_msgs/mpc_debug.h"
#include "car_msgs/vehicle_state.h"

/**
 * @class Controller
 * @brief A proportional–integral–derivative controller for speed and steering
 using defualt integral hold
 */
class BaseControllerConf;

class BaseController {
 public:
  BaseController() = default;
  virtual ~BaseController() = default;

  virtual void Init(const BaseControllerConf &conf);
  virtual void Reset();
  virtual void Stop();

  void ComputeControlCommand(
      const car_msgs::trajectory &planning_published_trajectory,
      const car_msgs::vehicle_state &vehicle_state, car_msgs::control_cmd &cmd);
};

class BaseControllerConf {};