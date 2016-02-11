
#include "perception/common.h"
#include "perception/perception.h"

#define PERCEPTION_CONF_DIR "../my-code/auto-car/ros/src/perception/perception_conf.yaml"

bool DEBUG=0;


int main(int argc, char **argv)
{
    //判断是否为debug模式
    Common::debug_check();

    /* code for main function */
    ros::init(argc, argv, "perception");
    ros::NodeHandle car_perception_NodeHandle;
    
    /*perception模块初始化*/
    string path = Common::convert_to_debugpath(PERCEPTION_CONF_DIR);
    Car_Perception perception(YAML::LoadFile(path));
    /*订阅*/
    /*发布*/
    perception.obstacle_publisher = 
        car_perception_NodeHandle.advertise<car_msgs::base_obstacle_list>("obstacle_topic", 1000);
    // 创建ros定时器
    ros::Timer cycle_timer;

    cycle_timer = car_perception_NodeHandle.createTimer(ros::Duration(perception.conf.period),&Car_Perception::OnTimer, &perception);
    ros::spin();

    return 0;
}

