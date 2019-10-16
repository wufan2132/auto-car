// #pragma once

// #include "yaml-cpp/yaml.h"
// #include <string>
// #include <vector>
// using namespace std;

// class user_config{
// public:
//     class Car_Planning_Conf{
// public:
//         Car_Planning_Conf(YAML::Node yaml_conf);
//         string mode;
//         double period;
//         double wait_time;
//         string trajectory_dir;
//         int sampling_period;
//     };

//     class Interpolating_conf{
// public:
//         Interpolating_conf(YAML::Node yaml_conf);
//         double Spline_space;
//     };

//     class path_optimizer_Conf{
// public:
//         path_optimizer_Conf(YAML::Node yaml_conf);
//         float step_t;
//         float planning_t;
//         float keep_t;
//         double aim_speed;
//         double speed_correction;
//         double speed_min_limit;
//         double speed_max_limit;
//     };
// public:
//     user_config(YAML::Node yaml_conf);
//     Car_Planning_Conf planning_conf;
//     Interpolating_conf interpolating_conf;
//     path_optimizer_Conf optimizer_conf;

// };
