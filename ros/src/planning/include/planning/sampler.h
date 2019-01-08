#pragma once
#include "planning/common.h"
#include "planning/car_model.h"

using namespace Eigen;
using namespace std;



class SamplerPoint{
public:
    SamplerPoint(YAML::Node yaml_conf);
    void setSlength(double s){Slength = s;}
    void setLwidth(double l){Lwidth = l;}
    void setTlength(double t){Tlength = t;}

    void reset(Car_State_SL slpoint);
    //
    void getpointsL(double s, double t, vector<Car_State_SL>& points);
    void getpointsS(double l, double t, vector<Car_State_SL>& points);
    void getpointsT(double s, double l, vector<Car_State_SL>& points);
    //
    void getpointsSL(double t, vector<vector<Car_State_SL> >& points);


    //路宽
    double roadhalfwidth;  //路宽
    double roadlength;  //路剩下的长
    //采样起始点
    Car_State_SL init_SLpoint;
    //采样参数
    double Lwidth; //横向间隔
    double Slength; //纵向间隔
    double Tlength;  //时间间隔

    int Lnum;  //横向采样个数
    int Snum;  //纵向采样个数
    int Tnum;  //时间采样个数
};