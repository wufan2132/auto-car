#pragma once

#include "ros/ros.h"
#include "nav_msgs/Odometry.h" 
#include "car_msgs/chassis.h"
#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "yaml-cpp/yaml.h"
#include <string>
using namespace std;


extern bool DEBUG;

class Common{
public:
    static string convert_to_debugpath(string path){
        if(DEBUG){
            string str = "auto-car/ros/";
            int index = path.find(str);
            return path.substr(index+str.size());
        }
        return path;
    }
};