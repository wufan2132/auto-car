#pragma once

#include "perception/common.h"
#include "perception/reader.h"
class ObstacleSet_conf{
public:
    string obstacle_path;
};

class ObstacleSet{
public:
    ObstacleSet(YAML::Node yaml_conf);

    bool refresh(string path);//从reader获得障碍物数据

    car_msgs::base_obstacle_list obstacle_message;
    ObstacleSet_conf conf;
};
