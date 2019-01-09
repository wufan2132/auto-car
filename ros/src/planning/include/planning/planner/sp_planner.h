#pragma once
/************单点规划*****************/

/**********************************/

#include "planning/planner/planner.h"
#include "planning/trajectory_cost.h"
#include "planning/dp_road_graph.h"
#include "planning/dp_st_cost.h"
#include "planning/dp_st_graph.h"

class SpPlanner_Conf{
public:
    double available_l;
    double aim_speed;
    double step_t;
    double planning_t;
    double planning_s;
    double keep_t;
    double speed_correction;
    double speed_min_limit;
    double speed_max_limit;
};


class SpPlanner: public Planner{
public:
    SpPlanner(YAML::Node yaml_conf);
    void process(const car_msgs::trajectory_point car_status, const Car_State_SL& status_sl,
             const Spline_Out* refrenceline_Sp,  const car_msgs::trajectory& reference_line,
             car_msgs::trajectory& trajectory_out);

private:
    Car_State_SL get_start_point(const car_msgs::trajectory_point car_status, const Car_State_SL& status_sl,
                            const car_msgs::trajectory& reference_line, car_msgs::trajectory& trajectory_now);
    void get_current_line(const car_msgs::trajectory_point car_status, const Car_State_SL& status_sl,
                             const Spline_Out* refrenceline_Sp,const car_msgs::trajectory& reference_line,
                                                 car_msgs::trajectory& trajectory_out);

void path_generate(const VectorXf& QPsl,const VectorXf& QPts,
                                const Spline_Out* refrenceline_Sp,
                                const Car_State_SL& start_sl,
                                car_msgs::trajectory& trajectory_now);
private:
    /******配置******/
    SpPlanner_Conf conf;
    /******模块******/
    DpRoadGraph* dpgraph;
    DpStGraph* stgraph;
    SamplerPoint* sampler;
    /*********车体参数************/
    VectorXf QPts; //速度规划
    VectorXf QPsl; //位置规划
    Car_State_SL car_last_sl;
    /*********其他数据的指针***************/
};