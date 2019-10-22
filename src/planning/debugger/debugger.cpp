#include "planning/debugger/debugger.h"

    Debugger* debugger;



void Debugger::set_NodeHandle(ros::NodeHandle* pNodeHandle){
    if(!isActive) return;
    car_planning_NodeHandle = pNodeHandle;
    sampler_points_publisher
    = car_planning_NodeHandle->advertise<car_msgs::trajectory>("samplers_topic", 1000);
}

void Debugger::init(Spline_Out* refrenceline_Sp){
    if(!isActive) return;
    this->refrenceline_Sp = refrenceline_Sp;
}

void Debugger::show_sampler_points(const vector<vector<Car_State_SL> >& SamplerPointsSL){
    if(!isActive) return;
    static int count = 0;
    int index = 0;
    
    sample_points.trajectory_path.resize(SamplerPointsSL.size()*SamplerPointsSL[0].size());

    for(auto vec:SamplerPointsSL){
        for(auto point_sl: vec){
            sample_points.trajectory_path[index].header.seq = index;
            Coordinate_converter::SL_to_POS(point_sl.s, point_sl.l,
                refrenceline_Sp->sx,refrenceline_Sp->sy,sample_points.trajectory_path[index++]);
        }
    }
    
    sample_points.total_path_length = index;
    sample_points.header.seq = count;
    count++;

    sampler_points_publisher.publish(sample_points);
}