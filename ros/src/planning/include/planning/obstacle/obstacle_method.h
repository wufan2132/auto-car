#pragma once

#include "planning/common.h"
#include "planning/obstacle/obstacle.h"

class ObstacleMethod{
public:
//t时刻，障碍物与曲线的最短距离
//思路：用几何求解太麻烦
//将曲线按点采样，求曲线上的点到障碍物的距离
//先稀疏采样，找到一个范围后再进行稠密采样
static double distance_OC(const Obstacle& obs, const VectorXf& QP, double t=0);
//坐标转换：XY to 


};