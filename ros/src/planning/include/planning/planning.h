#ifndef PLANNING_H
#define PLANNING_H

#include "ros/ros.h"
#include "nav_msgs/Odometry.h" 
#include "car_msgs/chassis.h"
#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "replay.h"
#include "planning/Interpolating.h"
#include <Eigen/Dense>
#include "stdlib.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


class Car_Planning{
    public:


        void Init(void);

        void RunOnce(void);

        void Get_path(const car_msgs::trajectory& trajectory_path);

        void OnTimer(const ros::TimerEvent&);

        void load_trajectory_from_replay(replay& replayer);


        void localization_callback(const car_msgs::localization& localization);

        void chassis_callback(const car_msgs::chassis& chassis);

        car_msgs::trajectory_point generate_trajectory_point(const car_msgs::localization& localization,const car_msgs::chassis& chassis);
    
    car_msgs::localization car_localization;
    car_msgs::chassis car_chassis;

    car_msgs::trajectory origin_Trajectory;
    car_msgs::trajectory now_Trajectory;

    //
    ros::Subscriber localization_subscriber;
    ros::Subscriber chassis_subscriber;
    ros::Publisher trajectory_publisher;

};
#endif
/*path_point*/
// Header header
// geometry_msgs/Point position
// float64 speed
// float64 accel
// float64 yaw
// float64 curva
// float64 s
// float64 time
/*position*/
// float64 x
// float64 y
// float64 z
