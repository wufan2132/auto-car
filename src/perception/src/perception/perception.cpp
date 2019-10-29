#include "perception/perception.h"


Car_Perception::Car_Perception(const YAML::Node& planning_conf)
{
    conf.period = planning_conf["period"].as<double>();
    conf.obstacle_source = planning_conf["obstacle_source"].as<string>();
    obstacleset = new ObstacleSet(planning_conf["ObstacleSet_conf"]);
    lidarhandle = new LidarHandle(planning_conf["lidar_handle_conf"]);
}

void Car_Perception::pointcloud2_callback(const sensor_msgs::PointCloud2& msg){
    pointcloud2_msg = msg;
}


void Car_Perception::OnTimer(const ros::TimerEvent&){

    if(conf.obstacle_source == "lidar")
        obstacleset->refresh(pointcloud2_msg, lidarhandle);
    else if(conf.obstacle_source == "reader")
        obstacleset->refresh(obstacleset->conf.obstacle_path);
    else 
        ROS_ERROR("Car_Perception::OnTimer: conf.obstacle_source is error!");

    obstacle_publisher.publish(obstacleset->obstacle_message);
}