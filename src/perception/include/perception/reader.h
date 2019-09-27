#pragma once

#include "ros/ros.h"
#include "perception/common.h"
#include "stdlib.h"
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
class reader{
    public:
        reader(string path,string io="");
        ~reader();

        void readinit(string path);
        void writeinit(string path);

        void reset();
        void close();

        //obstacle
        bool readOnce(car_msgs::base_obstacle& object);

        int mode;
        ifstream inFile;
        ofstream outFile;
        string save_path;
};


