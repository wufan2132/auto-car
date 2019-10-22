#pragma once
/************多点规划*****************/
//最大轨迹期望规划
/**********************************/
/*
1.先把路径sl用多点替代，st图暂时放一边吧 >_<
*/

#include "planning/planner/planner.h"
#include "planning/trajectory_cost.h"
#include "planning/dp_road_graph.h"
#include "planning/dp_st_cost.h"
#include "planning/dp_st_graph.h"

class TestPlanner_Conf{
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


class TestPlanner: public Planner{
public:
    TestPlanner(YAML::Node yaml_conf);
    void process(const car_msgs::trajectory_point car_status, const Car_State_SL& status_sl,
             const Spline_Out* refrenceline_Sp,  const car_msgs::trajectory& reference_line,
             car_msgs::trajectory& trajectory_out);

private:
    Car_State_SL get_start_point(const car_msgs::trajectory_point car_status, const Car_State_SL& status_sl,
                            const car_msgs::trajectory& reference_line, car_msgs::trajectory& trajectory_now);
    void get_current_line(const car_msgs::trajectory_point car_status, const Car_State_SL& status_sl,
                             const Spline_Out* refrenceline_Sp,const car_msgs::trajectory& reference_line,
                                                 car_msgs::trajectory& trajectory_out);

void path_generate(const MatrixXf& QPsl,const VectorXf& QPts,
                                const Spline_Out* refrenceline_Sp,
                                const Car_State_SL& start_sl,
                                car_msgs::trajectory& trajectory_now);
private:
    /******配置******/
    TestPlanner_Conf conf;
    /******模块******/
    DpRoadGraph* dpgraph;
    DpStGraph* stgraph;
    SamplerPoint* sampler;
    /*********车体参数************/
    MatrixXf QPsl; //位置规划
    VectorXf QPts; //速度规划
    Car_State_SL car_last_sl;
    /*********保存的中间数据***************/
    vector<Car_State_SL> trajectory_sl;
    vector<RoadGraphNode> min_cost_path;
    /*********其他数据的指针***************/
};