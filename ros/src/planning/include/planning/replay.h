#ifndef REPLAY_H
#define REPLAY_H

#include "ros/ros.h"
#include "car_msgs/chassis.h"
#include "car_msgs/trajectory.h"
#include "car_msgs/localization.h"
#include "car_msgs/trajectory_point.h"
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
        bool saveOnce(car_msgs::trajectory_point point);
        bool readOnce(car_msgs::trajectory_point &point);

        int mode;
        ifstream inFile;
        ofstream outFile;
        string save_path;
};

#endif

