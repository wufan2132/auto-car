#pragma once

#include <iostream>
#include <Eigen/Dense>
#include "planning/common.h"
#include "planning/Interpolating.h"
#include "planning/Fitting.h"
#include "planning/map/Image.h"
#include "planning/map/A_star.h"
#include "planning/map/road.h"
#include "planning/map/map_convert.h"
using namespace std;
using namespace Eigen;

class Refrenceline_provider_conf{
public:

    int start_point_x;
    int start_point_y;
    int end_point_x;
    int end_point_y;
    string origin_image_dir;
    string output_image_dir;
    int origin_road_width;
    double scale;
    
    double spacing;
    int smooth_order;

};


class Refrenceline_provider{
public:
    Refrenceline_provider(YAML::Node yaml_conf);
    void process(car_msgs::trajectory& origin_Trajectory);
    Refrenceline_provider_conf conf;
    /****************/
    Astar* astar;
    MapConvert* map_convert;
};
