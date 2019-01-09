#include "planning/sampler.h"

SamplerPoint::SamplerPoint(YAML::Node yaml_conf){
    Lwidth = yaml_conf["Lwidth"].as<double>();
    Slength = yaml_conf["Slength"].as<double>();
    Tlength  = yaml_conf["Tlength"].as<double>();
    Lnum = yaml_conf["Lnum"].as<int>();
    Snum = yaml_conf["Snum"].as<int>();
    Tnum  = yaml_conf["Tnum"].as<int>();

    roadhalfwidth = 10;
}


void SamplerPoint::reset(Car_State_SL slpoint){
    init_SLpoint = slpoint;
}


void SamplerPoint::getpointsL(double s, double t, vector<Car_State_SL>& points){
    points.resize(Lnum);
    double curL = -Lwidth*(Lnum/2);
    for(int i=0;i<Lnum;i++){
        if(curL<=-roadhalfwidth){
            curL += Lwidth;
            ROS_WARN("SamplerPoint::getpointsSL: samplePoints is out of Road!");
            continue;
        }
        else if(curL >= roadhalfwidth){
            ROS_WARN("SamplerPoint::getpointsSL: samplePoints is out of Road!");
            break;
        }
        points[i].s = s;
        points[i].l = curL;
        points[i].t = t;
        curL += Lwidth;
    }
    //     //debug
    // cout<<"sampler points:"<<endl;
    // cout<<"s:"<<init_SLpoint.s<<" l:"<<init_SLpoint.l<<endl;
    //     for(int row = 0;row<Lnum;row++)
    //         cout<<"("<<points[row].s<<","<<points[row].l<<") ";
    //     cout<<endl;
}

void SamplerPoint::getpointsS(double l, double t, vector<Car_State_SL>& points){
    //resize
    points.resize(Snum);
    double curS = init_SLpoint.s;
    //rows
    for(int i=0;i<Snum;i++){
        curS += Slength;
        points[i].s = curS;
        points[i].l = l;
        points[i].t = t;
    }
}

void SamplerPoint::getpointsT(double s, double l, vector<Car_State_SL>& points){
    //resize
    points.resize(Tnum);
    int krea = 1;
    krea = krea << (Tnum/2);
    double curT = Tlength/(double)krea;
    //rows
    for(int i=0;i<Tnum;i++){
        points[i].s = s;
        points[i].l = l;
        points[i].t = curT;
        curT *=2;
    }
}

void SamplerPoint::getpointsSL(double t, vector<vector<Car_State_SL> >& points){
    //resize
    points.resize(Snum);
    for(int i=0;i<points.size();i++)
        points[i].resize(Lnum);
    double curS = init_SLpoint.s;
    double curL = init_SLpoint.l;
    //rows
    for(int i=0;i<Snum;i++){
        curS += Slength;

        //纵向采样的个数最好为奇数
        double curL = -Lwidth*(Lnum/2);
        for(int j=0;j<Lnum;j++){
            if(curL<=-roadhalfwidth){
                curL += Lwidth;
                ROS_WARN("SamplerPoint::getpointsSL: samplePoints is out of Road!");
                continue;
            }
            else if(curL >= roadhalfwidth){
                ROS_WARN("SamplerPoint::getpointsSL: samplePoints is out of Road!");
                break;
            }
            points[i][j].s = curS;
            points[i][j].l = curL;
            points[i][j].t = t;
            curL += Lwidth;
        }
    }
    
    //debug
    // cout<<"sampler points:"<<endl;
    // cout<<"s:"<<init_SLpoint.s<<" l:"<<init_SLpoint.l<<endl;
    //     for(int row = 0;row<Snum;row++){
    //     for(int col=0;col<Lnum;col++){
    //         cout<<"("<<points[row][col].s<<","<<points[row][col].l<<") ";
    //     }
    //     cout<<endl;
    // }
}