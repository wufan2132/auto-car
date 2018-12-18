#include "planning/sampler.h"

SamplerPoint::SamplerPoint(YAML::Node yaml_conf){
    Lwidth = yaml_conf["Lwidth"].as<double>();
    Slength = yaml_conf["Slength"].as<double>();
    Tstep  = yaml_conf["Tstep"].as<double>();
    Lnum = yaml_conf["Lnum"].as<int>();
    Snum = yaml_conf["Snum"].as<int>();
    Tnum  = yaml_conf["Tnum"].as<int>();

    roadhalfwidth = 10;
    //resize
    points.resize(Snum);
    for(int i=0;i<points.size();i++)
        points[i].resize(Lnum);
}


void SamplerPoint::reset(Car_State_SL slpoint){
    init_SLpoint = slpoint;
}




void SamplerPoint::getpointsSL(){
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
            curL += Lwidth;
        }
    }
    
    //debug
    cout<<"sampler points:"<<endl;
    cout<<"s:"<<init_SLpoint.s<<" l:"<<init_SLpoint.l<<endl;
        for(int row = 0;row<Snum;row++){
        for(int col=0;col<Lnum;col++){
            cout<<"("<<points[row][col].s<<","<<points[row][col].l<<") ";
        }
        cout<<endl;
    }
}