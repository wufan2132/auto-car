#pragma once
#include "ros/ros.h"
#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "yaml-cpp/yaml.h"
#include "stdlib.h"
#include <iostream>
#include <string>
#include <vector>
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
    //当前最近的坐标点
    int index;
};

/*转换器*/
class Coordinate_converter{
public:
    static void SL_to_POS();
    static bool POS_to_SL(const car_msgs::trajectory& reference_line,const car_msgs::trajectory_point& point, Car_State_SL& status_sl);
};