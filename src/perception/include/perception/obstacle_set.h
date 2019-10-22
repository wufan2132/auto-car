#pragma once

#include "perception/common.h"
#include "perception/reader.h"
#include "perception/lidar_handle.h"

class ObstacleSet_conf{
public:
    string obstacle_path;
};

class ObstacleSet{
public:
    ObstacleSet(const YAML::Node& yaml_conf);

    bool refresh(string path);//从reader获得障碍物数据
    bool refresh(const sensor_msgs::PointCloud2& msg, LidarHandle* handle);

    car_msgs::base_obstacle_list obstacle_message;
    ObstacleSet_conf conf;
};
