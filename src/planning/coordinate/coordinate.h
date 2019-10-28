#pragma once
#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <vector>
#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "ros/ros.h"
#include "common/base/log.h"
#include "stdlib.h"
#include "car_state_sl.h"
#include "yaml-cpp/yaml.h"

namespace planning {
/*转换器*/
class Coordinate {
 public:
  //这个只计算x,y
  static std::pair<double, double> POS_to_SL(
      const car_msgs::trajectory& refrenceline, double x, double y, int start,
      int end);
  static bool POS_to_SL(const car_msgs::trajectory& refrenceline,
                        car_msgs::trajectory_point& point,
                        CarStateSL& status_sl);
  static void SL_to_POS(const double s, const double l, const Eigen::MatrixXf& sx,
                        const Eigen::MatrixXf& sy, car_msgs::trajectory_point& point,
                        const int start_index = -1);

 private:
  static int search_index(double st, Eigen::VectorXf& s);
};

}  // namespace planning