#ifndef PLANNING_H
#define PLANNING_H

#include "ros/ros.h"
#include "car_msgs/chassis.h"
#include "car_msgs/path.h"
#include "car_msgs/path_point.h"

class Car_Planning{
    public:


        void Init(void);

        void RunOnce(void);

        void Get_path(const car_msgs::path& path);
    

    
    car_msgs::path origin_path;
    car_msgs::path this_path;

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
