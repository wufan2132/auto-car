#include "planning/planning.h"

Car_Planning planning;



void Get_path_callback(const car_msgs::path &path){
    planning.Get_path(path);
}


int main(int argc, char **argv)
{
    /* code for main function */
    ros::init(argc, argv, "planning");
    ros::NodeHandle car_planning_NodeHandle;
    //订阅
    ros::Subscriber path_subscriber= car_planning_NodeHandle.subscribe("chassis_topic", 1, Get_path_callback);
    //发布
    ros::Publisher path_publisher= car_planning_NodeHandle.advertise<car_msgs::path>("path_topic", 1000);
    planning.Init();
    ros::Rate loop_rate(10);
    while(ros::ok())
    {   
        planning.RunOnce();
        car_msgs::path car_path;
  
        path_publisher.publish(car_path);

        ros::spinOnce();
        loop_rate.sleep();

    }
    return 0;
}

