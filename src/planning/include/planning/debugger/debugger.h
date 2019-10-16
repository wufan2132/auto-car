#pragma once
#include "planning/common.h"
#include "planning/sampler.h"
#include "planning/car_model.h"




class Debugger{
public:
    Debugger(){};
    bool isActive = 1;

    void set_NodeHandle(ros::NodeHandle* pNodeHandle);
    void init(Spline_Out* refrenceline_Sp);
    void show_sampler_points(const vector<vector<Car_State_SL> >& SamplerPointsSL);
    Spline_Out* refrenceline_Sp;
    car_msgs::trajectory sample_points;
    ros::NodeHandle* car_planning_NodeHandle;
    ros::Publisher sampler_points_publisher;
};

extern Debugger* debugger;