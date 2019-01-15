#include "perception/perception.h"


Car_Perception::Car_Perception(YAML::Node planning_conf)
{
    conf.period = planning_conf["period"].as<double>();
    obstacleset = new ObstacleSet(planning_conf["ObstacleSet_conf"]);
    lidarhandle = new LidarHandle(planning_conf);
}

void Car_Perception::pointcloud2_callback(const sensor_msgs::PointCloud2& msg){
    pointcloud2_msg = msg;
}


void Car_Perception::OnTimer(const ros::TimerEvent&){
    obstacleset->refresh(pointcloud2_msg, lidarhandle);
    obstacle_publisher.publish(obstacleset->obstacle_message);
}