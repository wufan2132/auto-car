#pragma once
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include "common/base/log.h"

namespace planning {

class Fitting {
 public:
  Fitting();
  ~Fitting();
  /*纵向四次多项式拟合*/
  // 用当前时刻xs，vxs，axs与目标时刻的速度vxe、加速度axe，时刻
  // 两个点拟合4次多项式
  static Eigen::VectorXf quartic4_polynomial(float now_s, float now_speed,
                                             float now_acc, float aim_speed,
                                             float aim_acc, float t);
  /*************** St 排列***********************/
  /*         s0,s_d0,s_dd0,s_ddd0           */
  /*         s1,s_d1,s_dd1,s_ddd1           */
  /*         ....................           */
  /*         sN,s_dN,s_ddN,s_dddN           */
  static void cal_point_quartic4(const Eigen::VectorXf& QP,
                                 const Eigen::VectorXf& t, Eigen::MatrixXf& St);
  static void cal_point_quartic4(const Eigen::VectorXf& QP, double t,
                                 Eigen::VectorXf& Xt);
  static double cal_point_quartic4(const Eigen::VectorXf& QP, double t);
  /*横向五次多项式拟合*/
  static Eigen::VectorXf quintic5_polynomial(float now_hs, float now_hs_d,
                                             float now_hs_dd, float aim_hs,
                                             float aim_hs_d, float aim_hs_dd,
                                             float t);
  static void cal_point_quintic5(const Eigen::VectorXf& QP,
                                 const Eigen::VectorXf& t, Eigen::MatrixXf& Xt);
  static void cal_point_quintic5(const Eigen::VectorXf& QP, double t,
                                 Eigen::VectorXf& Xt);
  static double cal_point_quintic5(const Eigen::VectorXf& QP, double t);
  /*N多项式优化*/
  static void gradient_descent(const Eigen::VectorXf& y, Eigen::VectorXf& QP,
                               int dime);
  static void gradient_descent_optimizer(Eigen::VectorXf& y, int dime = 2);
  static void newton(const Eigen::VectorXf& y, Eigen::VectorXf& QP);
};

}  // namespace planning