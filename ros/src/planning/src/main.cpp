#include "planning/planning.h"

#define PLANNING_CONF_DIR "/home/wf/my-code/auto-car/ros/src/planning/planning_conf.yaml"


int main(int argc, char **argv)
{
    /* code for main function */
    ros::init(argc, argv, "planning");
    ros::NodeHandle car_planning_NodeHandle;
    
    /*planning模块初始化*/
    Car_Planning planning(YAML::LoadFile(PLANNING_CONF_DIR));

    
    /*订阅*/
    if(planning.conf.mode == "write"){
    planning.localization_subscriber = 
        car_planning_NodeHandle.subscribe("localization_topic", 1, &Car_Planning::localization_callback,&planning);
    planning.chassis_subscriber = 
        car_planning_NodeHandle.subscribe("chassis_topic", 1, &Car_Planning::chassis_callback,&planning);
    }
    //发布
    planning.trajectory_publisher = 
        car_planning_NodeHandle.advertise<car_msgs::trajectory>("planning_topic", 1000);
    

    // 创建ros定时器
    ros::Timer cycle_timer;
    if(planning.conf.mode == "send"){
    cycle_timer = car_planning_NodeHandle.createTimer(ros::Duration(0.1),&Car_Planning::OnTimer, &planning);
    }
    ros::spin();

    return 0;
}

