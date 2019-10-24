
#pragma once

#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "planning/coordinate/car_state_sl.h"
#include "planning/tool/analytic_polynomial.h"
#include "yaml-cpp/yaml.h"

namespace planning {
// 数据帧
class Frame {
 public:
  Frame();
  ~Frame();
  void Init();

  // refrenceline
  const car_msgs::trajectory& refrenceline() { return refrenceline_; };
  car_msgs::trajectory* mutable_refrenceline() { return &refrenceline_; };
  const car_msgs::trajectory& raw_refrenceline() { return raw_refrenceline_; };
  car_msgs::trajectory* mutable_raw_refrenceline() {
    return &raw_refrenceline_;
  };
  const AnalyticPolynomial& analytic_refrenceline() {
    return analytic_refrenceline_;
  };
  AnalyticPolynomial* mutable_analytic_refrenceline() {
    return &analytic_refrenceline_;
  };
  // car state
  const car_msgs::trajectory_point& car_state() { return car_state_; };
  car_msgs::trajectory_point* mutable_car_state() { return &car_state_; };
  const CarStateSL& car_state_sl() { return car_state_sl_; };
  CarStateSL* mutable_car_state_sl() { return &car_state_sl_; };

 private:
  // refrenceline
  car_msgs::trajectory refrenceline_;
  car_msgs::trajectory raw_refrenceline_;
  AnalyticPolynomial analytic_refrenceline_;
  // car state
  car_msgs::trajectory_point car_state_;
  CarStateSL car_state_sl_;
};

}  // namespace planning