#pragma once

#include "ros/ros.h"
#include "car_msgs/chassis.h"
#include "car_msgs/trajectory.h"
#include "car_msgs/localization.h"
#include "car_msgs/trajectory_point.h"
#include "planning/common.h"
#include "planning/obstacle/obstacle.h"
#include "stdlib.h"
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
class replay{
public:
    replay(string path,string io="");
    ~replay();

    void readinit(string path);
    void writeinit(string path);

    void reset();
    void close();
    //trajectory_point
    bool saveOnce(car_msgs::trajectory_point point, int period=100);
    bool readOnce(car_msgs::trajectory_point &point);
    //obstacle
    bool readOnce(Obstacle& object);

    static void load_trajectory_from_replay(replay& replayer, car_msgs::trajectory& refrence_line);
    int mode;
    ifstream inFile;
    ofstream outFile;
    string save_path;
};


