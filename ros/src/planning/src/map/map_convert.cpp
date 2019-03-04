#include "planning/map/map_convert.h"

    MapConvert::MapConvert(YAML::Node yaml_conf){
        resolution = yaml_conf["resolution"].as<double>();
        vector<double> origin = yaml_conf["origin"].as<vector<double> >();
        origin_x = origin[0];
        origin_y = origin[1];
    }
    car_msgs::trajectory_point MapConvert::MapToPos(const MapPoint& point){
        static int count = 0;
        count++;
        car_msgs::trajectory_point t_point;
        t_point.header.seq = count;
<<<<<<< HEAD
        t_point.x = point.y*resolution + origin_x;
        t_point.y =  - point.x*resolution - origin_y;
=======
        t_point.x = point.x*resolution - origin_x;
        t_point.y = point.y*resolution - origin_y;
>>>>>>> a217cdb67066cc4e2dd5e42b89653362f6d6c029
        t_point.z = 0;
        return t_point;
    }
    MapPoint MapConvert::PosToMap(const car_msgs::trajectory_point& point){
<<<<<<< HEAD
        double x = (-point.y - origin_y)/resolution;
        double y = (point.x - origin_x)/resolution;
=======
        double x = (point.x + origin_x)/resolution;
        double y = (point.y + origin_y)/resolution;
>>>>>>> a217cdb67066cc4e2dd5e42b89653362f6d6c029
        return MapPoint(x,y);
    }