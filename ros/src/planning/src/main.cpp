#include "planning/planning.h"




int main(int argc, char **argv)
{
    /* code for main function */
    ros::init(argc, argv, "planning");
    ros::NodeHandle car_planning_NodeHandle;
    Car_Planning planning();
    
    //ros::Subscriber chassis_msg_subscriber;

    ros::Publisher trajectory_publisher= car_planning_NodeHandle.advertise<car_msgs::trajectory>("trajectory_topic", 1000);
    

    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        car_msgs::trajectory car_trajectory;
  
        trajectory_publisher.publish(car_trajectory);

        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}

