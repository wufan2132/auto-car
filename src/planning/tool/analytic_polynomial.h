#pragma once
#include <math.h>
#include <Eigen/Dense>
#include "yaml-cpp/yaml.h"

namespace planning {
class AnalyticPolynomial {
 public:
  int length;
  Eigen::VectorXf s;
  Eigen::MatrixXf sx;
  Eigen::MatrixXf sy;
  Eigen::VectorXf x;
  Eigen::VectorXf y;
  Eigen::VectorXf yaw;
  Eigen::VectorXf curvature;
};

}  // namespace planning