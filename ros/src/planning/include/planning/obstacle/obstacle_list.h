#pragma once

#include "planning/common.h"
#include "planning/replay.h"
#include "planning/obstacle/obstacle.h"
#include "planning/obstacle/obstacle_method.h"
#include "planning/car_model.h"

class ObstacleList_conf{
public:
    string obstacle_path;
};

class ObstacleList{
public:
    ObstacleList(YAML::Node yaml_conf);

    void init(car_msgs::trajectory* p_reference_line,
              car_msgs::trajectory_point* p_car_status,
              Car_State_SL* p_status_sl){
        reference_line_ptr = p_reference_line;
        car_status_ptr = p_car_status;
        status_sl_ptr = p_status_sl;
    };

    bool refresh(string path);//从replay获得障碍物数据
    bool refresh(const car_msgs::base_obstacle_list& obstacle_list);//从chassis获得障碍物数据
    void process();

    vector<Obstacle> list;
    car_msgs::base_obstacle_list obstacle_msg;
    ObstacleList_conf conf;
    /*******临时变量指针*********/
    const car_msgs::trajectory_point* car_status_ptr;
    const car_msgs::trajectory* reference_line_ptr;
    const Car_State_SL* status_sl_ptr;

};
