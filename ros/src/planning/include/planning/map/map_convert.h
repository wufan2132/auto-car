#pragma once
#include "planning/common.h"
#include "planning/map/map_point.h"


class MapConvert{
public:
    MapConvert(YAML::Node);
    car_msgs::trajectory_point MapToPos(const MapPoint& point);
    MapPoint PosToMap(const car_msgs::trajectory_point& point);
private:
    double resolution = 1;
    double origin_x = 0;
    double origin_y = 0;
};