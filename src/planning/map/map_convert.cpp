#include "planning/map/map_convert.h"
#include <vector>

MapConvert::MapConvert(const common::base::ConfNode& yaml_conf) {
  resolution = yaml_conf["resolution"].as<double>();
  std::vector<double> origin = yaml_conf["origin"].as<std::vector<double> >();
  origin_x = origin[0];
  origin_y = origin[1];
}
car_msgs::trajectory_point MapConvert::MapToPos(const MapPoint& point) {
  static int count = 0;
  count++;
  car_msgs::trajectory_point t_point;
  t_point.header.seq = count;
  t_point.x = point.y * resolution + origin_x;
  t_point.y = -point.x * resolution - origin_y;
  t_point.z = 0;
  return t_point;
}
MapPoint MapConvert::PosToMap(const car_msgs::trajectory_point& point) {
  double x = (-point.y - origin_y) / resolution;
  double y = (point.x - origin_x) / resolution;
  return MapPoint(x, y);
}