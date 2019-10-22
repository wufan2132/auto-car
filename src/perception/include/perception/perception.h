#pragma once

#include "perception/common.h"
#include "perception/lidar_handle.h"
#include "perception/obstacle_set.h"
#include <iostream>


using namespace std;


class Car_Perception_Conf{
public:
    double period;
    string obstacle_source;
};

class Car_Perception{
    public:
        Car_Perception(const YAML::Node& yaml_conf);

        void OnTimer(const ros::TimerEvent&);

        void pointcloud2_callback(const sensor_msgs::PointCloud2& msg);

    //ros通信模块
    ros::Subscriber pointcloud2_subscriber;
    ros::Publisher obstacle_publisher;
    //配置参数
    Car_Perception_Conf conf;
    //模块
    ObstacleSet* obstacleset;
    LidarHandle* lidarhandle;
    /****实时更新数据***/
    //点云
    sensor_msgs::PointCloud2 pointcloud2_msg;
};
