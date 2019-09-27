#pragma once

#include "ros/ros.h"
#include "nav_msgs/Odometry.h" 
#include "car_msgs/chassis.h"
#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "car_msgs/base_obstacle.h"
#include "car_msgs/base_obstacle_list.h"
#include "yaml-cpp/yaml.h"
#include <string>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

#define DOUBLE_MAX 99999.9
#define PI 3.14159265354
extern bool DEBUG;

class Common{
public:
    static void debug_check(){
    //判断是否为debug模式
        char cwd[50];
        char *s = getcwd(cwd,sizeof(cwd));
        string runpath = cwd;
        if(runpath.find(".ros")==std::string::npos)
            DEBUG = 1;
    }

    static string convert_to_debugpath(string path){
        if(DEBUG){
            string str = "auto-car/ros/";
            int index = path.find(str);
            return path.substr(index+str.size());
        }
        return path;
    }
};