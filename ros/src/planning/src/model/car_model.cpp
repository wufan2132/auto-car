#include "planning/car_model.h"

#define nums 270 //每次向后查找多少个点 假设采样间隔splice = 0.1m,车速100km/h (27m/s),1s 会经过270个点

bool Coordinate_converter::POS_to_SL(const car_msgs::trajectory& reference_line,const car_msgs::trajectory_point& point,Car_State_SL& status_sl){
    if(!point.header.seq>0){
        //debug
        ROS_INFO("trajectory_point is not received!");
        return 0;
    }
    //cout<<"status_sl.index:"<<status_sl.index<<endl;
    int end_index = min(status_sl.index+270,int(reference_line.total_path_length)-2);
    //cout<<"end_index:"<<end_index<<endl;
    for(int i=status_sl.index;i<end_index;i++){
        float distance0 = (point.x - reference_line.trajectory_path[i].x)*(point.x - reference_line.trajectory_path[i].x) +
        (point.y - reference_line.trajectory_path[i].y)* (point.y - reference_line.trajectory_path[i].y);
        float distance1 = (point.x - reference_line.trajectory_path[i+1].x)*(point.x - reference_line.trajectory_path[i+1].x) +   
        (point.y - reference_line.trajectory_path[i+1].y)* (point.y - reference_line.trajectory_path[i+1].y);  
        if(distance0>distance1)
            continue;
        else{
            status_sl.index = i;
            break;
        }          
    }
    //求点到直线的距离
    float A = reference_line.trajectory_path[status_sl.index].y - reference_line.trajectory_path[status_sl.index+1].y;
    float B = reference_line.trajectory_path[status_sl.index+1].x - reference_line.trajectory_path[status_sl.index].x;
    float C = reference_line.trajectory_path[status_sl.index+1].y*(reference_line.trajectory_path[status_sl.index].x - reference_line.trajectory_path[status_sl.index+1].x) -
            reference_line.trajectory_path[status_sl.index+1].x*(reference_line.trajectory_path[status_sl.index].y - reference_line.trajectory_path[status_sl.index+1].y);
    status_sl.h = (A*point.x+B*point.y+C)/sqrt(A*A+B*B);
    //cout<<"h:"<<status_sl.h<<endl;
    //求垂足
    float x_ = (B*B*point.x-A*B*point.y-A*C)/(A*A+B*B);
    float y_ = (-A*B*point.x+A*A*point.y-B*C)/(A*A+B*B);
    //根据垂足求s
    status_sl.s = reference_line.trajectory_path[status_sl.index].s + 
    (reference_line.trajectory_path[status_sl.index+1].s - reference_line.trajectory_path[status_sl.index].s)*
    (x_ - reference_line.trajectory_path[status_sl.index].x)/
    (reference_line.trajectory_path[status_sl.index+1].x - reference_line.trajectory_path[status_sl.index].x);
    //cout<<"s:"<<status_sl.s<<endl;
    //求夹角
    //cout<<"cal_theta"<<endl;
    float theta = point.theta - reference_line.trajectory_path[status_sl.index].theta;
    float tan_theta = tan(theta);
    float cos_theta = cos(theta);
    float sin_theta = sin(theta);
    float one_minus_kappa_r_d = 1 - reference_line.trajectory_path[status_sl.index].kappa * status_sl.h;
    //求sv
    status_sl.sv = point.speed*cos_theta/one_minus_kappa_r_d;
    //求sa
    status_sl.sa = point.accel * cos_theta / one_minus_kappa_r_d;
    //求dh/ds 
    status_sl.dh = one_minus_kappa_r_d*tan_theta;
    //求dh/d2s
    status_sl.ddh = -reference_line.trajectory_path[status_sl.index].kappa * status_sl.dh* tan_theta;
    //debug
    ROS_INFO("index:%d theta:%0.2f s:%.2f sv:%.2f sa:%.6f h:%.2f dh:%.2f ddh:%.6f",
    status_sl.index,theta,status_sl.s,status_sl.sv,status_sl.sa,status_sl.h,status_sl.dh,status_sl.ddh);
    return 0;
}