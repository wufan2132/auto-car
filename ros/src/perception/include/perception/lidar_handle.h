#pragma once
#include "perception/common.h"
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl_ros/transforms.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

typedef pair<double, double> XY;




class LidarHandle_conf{

};




class LidarHandle{
public:
    LidarHandle(YAML::Node yaml_conf);

    void process(const sensor_msgs::PointCloud2& msg,
                        car_msgs::base_obstacle_list& obstacle_list);

    
    LidarHandle_conf conf;
private:
    bool readonce(const sensor_msgs::PointCloud2& msg, XY* pos); //读一个完整的坐标点
    bool creat_obstacle(XY start,XY end,
                    int point_count,
                    car_msgs::base_obstacle& obst);
};