#pragma once
#include "ros/ros.h"
#include <Eigen/Dense>
#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "yaml-cpp/yaml.h"
#include "planning/Interpolating.h"
#include "stdlib.h"
#include <iostream>
#include <string>
#include <vector>
using namespace Eigen;
using namespace std;
/*SL道路坐标系*/
class Car_State_SL{
public:
    Car_State_SL(){
        index = 0;
        s = 0;
        sv = 0;
        sa = 0;
        h = 0;
        dh = 0;
        ddh = 0;
    };
    //纵向
    float s;
    float sv;
    float sa;
    //横向
    float h;
    float dh;
    float ddh;
    //
    float theta;
    //当前最近的坐标点
    int index;
};

/*转换器*/
class Coordinate_converter{
public:
    //这个只计算x,y
    static void SL_to_POS(const float s, const float l, const MatrixXf& sx, const MatrixXf& sy, car_msgs::trajectory_point& point, const int start_index=-1);
    static bool POS_to_SL(const car_msgs::trajectory& reference_line,car_msgs::trajectory_point& point, Car_State_SL& status_sl);
private:
    static int search_index(float st, VectorXf& s, int index=-1);
};