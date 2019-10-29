#pragma once
#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <vector>
#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "planning/tool/interpolating.h"
#include "ros/ros.h"
#include "stdlib.h"
#include "yaml-cpp/yaml.h"

/*SL道路坐标系*/
class CarStateSL {
 public:
  CarStateSL(){};
  CarStateSL(double s_, double l_) : s(s_), l(l_){};
  CarStateSL(int i, double s_, double sv_, double sa_, double l_, double dl_,
               double ddl_)
      : index(i), s(s_), sv(sv_), sa(sa_), l(l_), dl(dl_), ddl(ddl_){};
  //纵向
  double s = 0;
  double sv = 0;
  double sa = 0;
  //横向
  double l = 0;
  double dl = 0;
  double ddl = 0;
  //
  double t = 0;
  double theta = 0;
  // 1.在POS转SL中表示refrenceline中对应点的序号
  int index = 0;
  // 2.在作为规划的起始点时，表示规划起始点在输出轨迹的序号
  int start_pos;
};
