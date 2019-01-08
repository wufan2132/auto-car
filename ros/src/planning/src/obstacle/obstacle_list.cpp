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
    cout<< "Obstacle size:"<< this->list.size()<<endl;
}

bool ObstacleList::refresh(car_msgs::base_obstacle_list obstacle_list){//从chassis获得障碍物数据
}