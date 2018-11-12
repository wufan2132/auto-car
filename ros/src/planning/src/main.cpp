#include "planning/planning.h"





// void Get_path_callback(const car_msgs::trajectory &path){

// }



int main(int argc, char **argv)
{
    /* code for main function */
    ros::init(argc, argv, "planning");
    ros::NodeHandle car_planning_NodeHandle;
    Car_Planning planning;

    /*planning模块初始化*/
    planning.Init();

    
    /*订阅*/
    //ros::Subscriber chassis_subscriber= car_planning_NodeHandle.subscribe("localization_topic", 1, Get_path_callback);
    planning.localization_subscriber = 
        car_planning_NodeHandle.subscribe("localization_topic", 1, &Car_Planning::localization_callback,&planning);
    planning.chassis_subscriber = 
        car_planning_NodeHandle.subscribe("chassis_topic", 1, &Car_Planning::chassis_callback,&planning);
    //发布
    planning.trajectory_publisher = 
        car_planning_NodeHandle.advertise<car_msgs::trajectory>("planning_topic", 1000);
    

    // 创建ros定时器
    //ros::Timer cycle_timer = car_planning_NodeHandle.createTimer(ros::Duration(0.1),&Car_Planning::OnTimer, &planning);

    ros::spin();

    return 0;
}

