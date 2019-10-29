#pragma once

#include "planning/map/map_point.h"
#include "common/base/file_tool/conf_node.h"
#include "car_msgs/trajectory_point.h"

class MapConvert{
public:
    MapConvert(const common::base::ConfNode& yaml_conf);
    car_msgs::trajectory_point MapToPos(const MapPoint& point);
    MapPoint PosToMap(const car_msgs::trajectory_point& point);
private:
    double resolution = 1;
    double origin_x = 0;
    double origin_y = 0;
};