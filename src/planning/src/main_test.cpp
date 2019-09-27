
#include "planning/common.h"
#include "planning/planning.h"
#include "car_msgs/base_obstacle_list.h"

#define PLANNING_CONF_DIR "../my-code/auto-car/ros/src/planning/planning_conf.yaml"

bool DEBUG=0;


int main(int argc, char **argv)
{
    //判断是否为debug模式
    Common::debug_check();

    /* code for main function */
     ros::init(argc, argv, "planning");
    ros::NodeHandle car_planning_NodeHandle;
    
    /*planning模块初始化*/
    string path = Common::convert_to_debugpath(PLANNING_CONF_DIR);

    YAML::Node yaml_conf = YAML::LoadFile(path);
    ObstacleList obstaclelist(yaml_conf["obstacle_list"]);
    obstaclelist.refresh(obstaclelist.conf.obstacle_path);

    ros::spin();

    return 0;
}