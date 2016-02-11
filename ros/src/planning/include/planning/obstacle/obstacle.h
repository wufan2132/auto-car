#pragma once

#include "planning/common.h"

//base_obstacle
/*
Header header
uint8 type
float64[] xa
float64[] ya
float64[] za
float64[] theta_a
float64 a
float64 b
*/
//
/*
type 0:圆形
type 1:矩形
*/

class Obstacle:public car_msgs::base_obstacle{
public:
    Obstacle();
    Obstacle(const car_msgs::base_obstacle& object);
    
    //sl坐标
    vector<double> sa;
    vector<double> la;

};









