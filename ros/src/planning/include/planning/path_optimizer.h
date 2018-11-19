#pragma once
#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include <math.h>
#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "planning/Interpolating.h"
#include "planning/Fitting.h"
#include "planning/car_model.h"
#include "yaml-cpp/yaml.h"

class path_optimizer_Conf{
public:
    float step_t;
    float planning_t;
    float aim_speed;
};

class path_optimizer{
public:
    path_optimizer(YAML::Node yaml_conf);

    Spline_Out* get_refrenceline(const car_msgs::trajectory& trajectory_in, car_msgs::trajectory& trajectory_out);
    void get_sampling_line(const Car_State_SL& status_sl, const car_msgs::trajectory& refrenceline, car_msgs::trajectory& trajectory_out);

    void process(const Car_State_SL& status_sl, const car_msgs::trajectory& refrenceline, car_msgs::trajectory& trajectory_outt);

    //配置参数
    path_optimizer_Conf conf;
    //模块
    Interpolating* interpolating;
private:
    void get_pos_in_refrenceline(const car_msgs::trajectory& refrenceline, float s,int start_index, float& refrenceline_x, float& refrenceline_y);
};