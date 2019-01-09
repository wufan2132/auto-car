#include "perception/perception.h"


Car_Perception::Car_Perception(YAML::Node planning_conf)
{
    conf.period = planning_conf["period"].as<double>();
    obstacleset = new ObstacleSet(planning_conf["ObstacleSet_conf"]);
}

void Car_Perception::OnTimer(const ros::TimerEvent&){
    obstacleset->refresh(obstacleset->conf.obstacle_path);

    obstacle_publisher.publish(obstacleset->obstacle_message);
}