#pragma once

#include <iostream>
#include <Eigen/Dense>
#include "planning/common.h"
#include "planning/Interpolating.h"
#include "planning/Fitting.h"
#include "planning/map/Image.h"
#include "planning/map/A_star.h"
#include "planning/map/road.h"

using namespace std;
using namespace Eigen;

class Refrenceline_provider_conf{
public:
    string origin_image_dir;
    string output_image_dir;
    int origin_road_width;
    double scale;
};


class Refrenceline_provider{
public:
    Refrenceline_provider(YAML::Node yaml_conf);
    void process();
    Refrenceline_provider_conf conf;
};
