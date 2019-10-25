#pragma once

#include <Eigen/Dense>
#include <string>
#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "planning/tool/analytic_polynomial.h"
#include "yaml-cpp/yaml.h"

namespace planning {
class TrajectoryGeneration {
 public:
  static bool getTrajectory_from_SLT(const Eigen::MatrixXf& S,
                                     const Eigen::MatrixXf& L,
                                     const Eigen::VectorXf& T,
                                     const AnalyticPolynomial& refrenceline_Sp,
                                     car_msgs::trajectory& trajectory,
                                     int start_index);
};

}