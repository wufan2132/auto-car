#include "planning/path_optimizer.h"

path_optimizer::path_optimizer(YAML::Node optimizer_conf){
    interpolating = new Interpolating(optimizer_conf["Interpolating_conf"]);
}


Spline_Out* path_optimizer::get_refrenceline(const car_msgs::trajectory& trajectory_in, car_msgs::trajectory& trajectory_out){
    return interpolating->process(trajectory_in, trajectory_out);
}


void path_optimizer::process(const car_msgs::trajectory& trajectory_in, car_msgs::trajectory& trajectory_out){
    
}