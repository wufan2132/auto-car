#pragma once

#include "common/base/log.h"
#include "planning/planner/planner.h"
#include "planning/tool/analytic_polynomial.h"

namespace planning {

class OgPlanner : public Planner {
 public:
  OgPlanner(const common::base::ConfNode& yaml_conf);
  ~OgPlanner();
  bool Init();
  bool Run(Frame* frame);
  bool Stop();

  /******path_planning******/
  //指定两个SL坐标系中的点进行planning_t时间的规划
  //起点中的所有数据用到，终点的s，没有用到会被时间覆盖
  void path_planning(const CarStateSL& start_sl, const CarStateSL& end_sl,
                     const float planning_t,
                     const AnalyticPolynomial& refrenceline_Sp,
                     car_msgs::trajectory& trajectory_out, int start_index = 0);

 private:
  class Conf {
   public:
    double step_t;
    double planning_t;
    double aim_speed;
    double speed_correction;
    double speed_min_limit;
  };
  Conf conf_;
  /*********车体参数************/
  Eigen::VectorXf QP4;  //速度规划
  Eigen::VectorXf QP5;  //位置规划
  CarStateSL last_sl_;
  /***************************/
};

}  // namespace planning