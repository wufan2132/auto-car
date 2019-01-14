#include "perception/obstacle_set.h"


ObstacleSet::ObstacleSet(YAML::Node yaml_conf){
    conf.obstacle_path = Common::convert_to_debugpath(yaml_conf["obstacle_path"].as<string>());
}



bool ObstacleSet::refresh(string path){//从replay获得障碍物数据
    static reader Obstacle_reader(path,"read");
    Obstacle_reader.reset();
    obstacle_message.list.clear();
    car_msgs::base_obstacle obst;
    while(Obstacle_reader.readOnce(obst))
    {
        obstacle_message.list.push_back(obst);
    }
    //ROS_INFO("ObstacleSet::refresh: Obstacle size: %d", (int)obstacle_message.list.size());
}
