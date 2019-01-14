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
#include "planning/obstacle/obstacle_list.h"
#include "yaml-cpp/yaml.h"

class Planner_Conf{
public:
};

class Planner{
public:
    Planner(YAML::Node yaml_conf);

    Spline_Out* get_refrenceline(const car_msgs::trajectory& trajectory_in, car_msgs::trajectory& trajectory_out);
    virtual void init(ObstacleList* obslist){obstaclelist = obslist;};
    
    virtual void process(const car_msgs::trajectory_point car_status, const Car_State_SL& status_sl,
             const Spline_Out* refrenceline_Sp,const car_msgs::trajectory& reference_line,
             car_msgs::trajectory& trajectory_out){};
protected:
    
     /**********模块************/
    Interpolating* interpolating;
    /**********引用模块*************/
    ObstacleList* obstaclelist;
private:
    /********配置参数************/
    Planner_Conf bconf;
};