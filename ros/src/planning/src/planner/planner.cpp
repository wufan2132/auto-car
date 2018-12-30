#include "planning/planner/planner.h"

Planner::Planner(YAML::Node yaml_conf){
    conf.step_t     = yaml_conf["step_t"].as<double>();
    interpolating = new Interpolating(yaml_conf["Interpolating_conf"]);
}


Spline_Out* Planner::get_refrenceline(const car_msgs::trajectory& trajectory_in, car_msgs::trajectory& trajectory_now){
    return interpolating->process(trajectory_in, trajectory_now);
}
