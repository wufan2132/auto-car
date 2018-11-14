#pragma once
#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include <math.h>
#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "planning/Interpolating.h"
#include "yaml-cpp/yaml.h"



class path_optimizer{
public:
    path_optimizer(YAML::Node yaml_conf);

    void process(const car_msgs::trajectory& trajectory_in, car_msgs::trajectory& trajectory_out);

    //模块
    Interpolating* interpolating;
};