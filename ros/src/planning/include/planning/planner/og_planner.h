#pragma once

#include "planning/planner/planner.h"

class OgPlanner_Conf{
public:
    double step_t;
    double planning_t;
    double keep_t;
    double available_l;
    double aim_speed;
    double speed_correction;
    double speed_min_limit;
    double speed_max_limit;
};

class OgPlanner:public Planner{
public:
    OgPlanner(YAML::Node yaml_conf);


    Car_State_SL get_start_point(const car_msgs::trajectory_point car_status,const Car_State_SL& status_sl,
                                                const car_msgs::trajectory& reference_line,
                                                car_msgs::trajectory& trajectory_now);

    void get_current_line(const car_msgs::trajectory_point car_status, const Car_State_SL& status_sl,
                             const Spline_Out* refrenceline_Sp, const car_msgs::trajectory& reference_line,
                             car_msgs::trajectory& trajectory_out);

    void process(const car_msgs::trajectory_point car_status, const Car_State_SL& status_sl,
             const Spline_Out* refrenceline_Sp,  const car_msgs::trajectory& reference_line,
             car_msgs::trajectory& trajectory_out);

    /******path_planning******/
    //指定两个SL坐标系中的点进行planning_t时间的规划
    //起点中的所有数据用到，终点的s，没有用到会被时间覆盖
    void path_planning(const Car_State_SL& start_sl,const Car_State_SL& end_sl,const float planning_t,
            const Spline_Out* refrenceline_Sp, car_msgs::trajectory& trajectory_out,int start_index=0);
    /*********车体参数************/
    VectorXf QP4; //速度规划
    VectorXf QP5; //位置规划
    Car_State_SL car_last_sl;
    /***************************/
    OgPlanner_Conf conf;
};