#pragma once
#include "ros/ros.h"
#include <Eigen/Dense>
#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "yaml-cpp/yaml.h"
#include "planning/Interpolating.h"
#include "stdlib.h"
#include <iostream>
#include <string>
#include <vector>
using namespace Eigen;
using namespace std;
/*SL道路坐标系*/
class Car_State_SL{
public:
    Car_State_SL(){};
    Car_State_SL(double s_, double l_)
    :s(s_),l(l_){};
    Car_State_SL(int i,double s_, double sv_, double sa_, double l_, double dl_, double ddl_)
    :index(i),s(s_),sv(sv_),sa(sa_),l(l_),dl(dl_),ddl(ddl_){};
    //纵向
    double s=0;
    double sv=0;
    double sa=0;
    //横向
    double l=0;
    double dl=0;
    double ddl=0;
    //
    double t=0;
    double theta=0;
    //1.在POS转SL中表示refrenceline中对应点的序号
    int index=0;
    //2.在作为规划的起始点时，表示规划起始点在输出轨迹的序号
    int start_pos;
};

/*转换器*/
class Coordinate_converter{
public:
    //这个只计算x,y
    static pair<double, double> POS_to_SL(const car_msgs::trajectory& reference_line, double x, double y, int start, int end);
    static bool POS_to_SL(const car_msgs::trajectory& reference_line,car_msgs::trajectory_point& point, Car_State_SL& status_sl);
    static void SL_to_POS(const double s, const double l, const MatrixXf& sx, const MatrixXf& sy, car_msgs::trajectory_point& point, const int start_index=-1);
    
private:
    static int search_index(double st, VectorXf& s);
};