#pragma once

#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include <math.h>
#include "planning/refrenceline.h"
#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "planning/Interpolating.h"
#include "planning/Fitting.h"
#include "planning/car_model.h"
#include "planning/trajectory_stitcher.h"
#include "planning/trajectory_generation.h"
#include "planning/sampler.h"
#include "yaml-cpp/yaml.h"

class Planner_Conf{
public:
    double step_t;
    double planning_t;
    double keep_t;
    double available_l;
    double aim_speed;
    double speed_correction;
    double speed_min_limit;
    double speed_max_limit;
};

class Planner{
public:
    Planner(YAML::Node yaml_conf);

    Spline_Out* get_refrenceline(const car_msgs::trajectory& trajectory_in, car_msgs::trajectory& trajectory_out);

    virtual void process(const car_msgs::trajectory_point car_status, const Car_State_SL& status_sl,
             const Spline_Out* refrenceline_Sp,const car_msgs::trajectory& reference_line,
             car_msgs::trajectory& trajectory_out){};
protected:
    
     /**********模块************/
    Interpolating* interpolating;

    /********配置参数************/
    Planner_Conf conf;

};