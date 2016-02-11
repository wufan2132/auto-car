#pragma once

#include "perception/common.h"
#include "perception/obstacle_set.h"
#include <iostream>


using namespace std;


class Car_Perception_Conf{
public:
    double period;
};

class Car_Perception{
    public:
        Car_Perception(YAML::Node yaml_conf);

        void OnTimer(const ros::TimerEvent&);

    //ros通信模块
    ros::Publisher obstacle_publisher;
    //配置参数
    Car_Perception_Conf conf;
    //模块
    ObstacleSet* obstacleset;
};
