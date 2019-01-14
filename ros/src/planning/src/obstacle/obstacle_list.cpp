#include "planning/obstacle/obstacle_list.h"


ObstacleList::ObstacleList(YAML::Node yaml_conf){
    conf.obstacle_path = Common::convert_to_debugpath(yaml_conf["obstacle_path"].as<string>());
}



bool ObstacleList::refresh(string path){//从replay获得障碍物数据
    static replay Obstacle_reader(path,"read");
    Obstacle_reader.reset();
    this->list.clear();
    Obstacle obst;
    while(Obstacle_reader.readOnce(obst))
    {
        this->list.push_back(obst);
    }
    ROS_INFO("ObstacleList::refresh: Obstacle size: %d", (int)this->list.size());
}

bool ObstacleList::refresh(const car_msgs::base_obstacle_list& obstacle_list){//从chassis获得障碍物数据
    obstacle_msg = obstacle_list;
}

void ObstacleList::process(){
    list.clear();
    for(auto obs : obstacle_msg.list){
        if(ObstacleMethod::isconcern(obs, *car_status_ptr, conf)){
            list.emplace_back(obs);
            ObstacleMethod::XTtoSL(*reference_line_ptr, *status_sl_ptr, list.back());
            // cout<<"obstacle "
            // <<list.back().header.seq<<"."
            // << list.back().xa[0]<<","
            // << list.back().ya[0]<<","
            // << list.back().sa[0]<<","
            // << list.back().la[0]<<","
            // <<endl;
        }
    }
}