#pragma once

#include "ros/ros.h"
#include "car_msgs/chassis.h"
#include "car_msgs/trajectory.h"
#include "car_msgs/localization.h"
#include "car_msgs/trajectory_point.h"
#include "common/base/log.h"
#include "stdlib.h"
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


class Replay{
public:
    Replay(std::string path, std::string io="");
    ~Replay();

    void ReadInit(std::string path);
    void WriteInit(std::string path);

    void Reset();
    void Close();
    //trajectory_point
    bool SaveOnce(const car_msgs::trajectory_point& point);
    bool ReadOnce(car_msgs::trajectory_point &point);
    //obstacle
    //bool ReadOnce(Obstacle& object);
    
    int mode = 0;
    std::ifstream inFile;
    std::ofstream outFile;
    std::string save_path;
};


