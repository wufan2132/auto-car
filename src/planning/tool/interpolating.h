#pragma once
#include <math.h>
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include "analytic_polynomial.h"
#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "common/base/file_tool/conf_node.h"
#include "common/base/log.h"
#include "yaml-cpp/yaml.h"

namespace planning {

class Interpolating {
 public:
  Interpolating(const common::base::ConfNode& yaml_conf);
  ~Interpolating();
  //

  bool process(const car_msgs::trajectory& trajectory_in,
                              car_msgs::trajectory* trajectory_out,
                              AnalyticPolynomial* csp);

  // static function
  /*************三次样条插值***********/
  // x,y ���������
  // csp ������ݶ���
  // spacing ��ֵ����λm
  static void Spline2D(const Eigen::VectorXf& x, const Eigen::VectorXf& y,
                       AnalyticPolynomial& csp, float spacing = 0.5);

  class Conf {
   public:
    double Spline_space;
  };
  Conf conf_;
  // tool
  static float curvature(float dx, float ddx, float dy, float ddy);
  static float yaw(float dx, float dy);

 private:
  static void cal_s(const Eigen::VectorXf& x, const Eigen::VectorXf& y,
                    Eigen::VectorXf& s);
  static void spline(const Eigen::VectorXf& x, const Eigen::VectorXf& y,
                     Eigen::MatrixXf& sp);

  static void cal_position(const Eigen::VectorXf& step,
                           const Eigen::MatrixXf& sx, const Eigen::MatrixXf& sy,
                           Eigen::MatrixXf& xout, Eigen::MatrixXf& yout);
  static void cal_yaw(const Eigen::MatrixXf& xout, const Eigen::MatrixXf& yout,
                      Eigen::VectorXf& yaw);
  static void cal_curvature(const Eigen::MatrixXf& xout,
                            const Eigen::MatrixXf& yout,
                            Eigen::VectorXf& curvature);
  static int search_index(float st, Eigen::VectorXf& s);
};

}  // namespace planning
