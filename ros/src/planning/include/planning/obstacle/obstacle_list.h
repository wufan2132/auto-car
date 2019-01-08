#pragma once

#include "planning/common.h"
#include "planning/replay.h"
#include "planning/obstacle/obstacle.h"
#include "planning/obstacle/obstacle_method.h"

class ObstacleList_conf{
public:
    string obstacle_path;
};

class ObstacleList{
public:
    ObstacleList(YAML::Node yaml_conf);

    bool refresh(string path);//从replay获得障碍物数据
    bool refresh(car_msgs::base_obstacle_list obstacle_list);//从chassis获得障碍物数据


    vector<Obstacle> list;
    ObstacleList_conf conf;
};
