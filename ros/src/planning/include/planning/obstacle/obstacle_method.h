#pragma once

#include "planning/common.h"
#include "planning/obstacle/obstacle.h"
#include "planning/Interpolating.h"
#include "planning/car_model.h"
#include "planning/Fitting.h"

class ObstacleList_conf;

class ObstacleMethod{
public:
//该障碍物是否值得关注
static bool isconcern(const car_msgs::base_obstacle& b_obst, 
                        const car_msgs::trajectory_point& car_status,
                        const ObstacleList_conf& conf);
//t时刻，障碍物与曲线的最短距离
//思路：用几何求解太麻烦
//将曲线按点采样，求曲线上的点到障碍物的距离
//先稀疏采样，找到一个范围后再进行稠密采样
static double distance_Ob_QP(const Obstacle& obs, const VectorXf& QP,
                             double start_s, double end_s, double t=0);
static double distance_Ob_QP(const Obstacle& obs, const MatrixXf& QP,
                             const vector<double>& s_list, double t=0);
//坐标转换：XY to 
static void XTtoSL(const car_msgs::trajectory& reference_line,
                    const Car_State_SL& status_sl,
                    Obstacle& obs);

};