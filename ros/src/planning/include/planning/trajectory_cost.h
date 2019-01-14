#pragma once
#include "planning/common.h"
#include "planning/car_model.h"
#include "planning/obstacle/obstacle_list.h"
#include "planning/ConCost.h"

class TrajectoryCost_conf{
public:
    double k_path=1.0; /*路径*/
    double k_smooth_l=1.0; //曲线偏差
    double k_smooth_dl=1.0; //一阶导
    double k_smooth_ddl=1.0; //二阶导
    double k_smooth_dddl=1.0; //三阶导

    double k_obstacle_l=1.0;//障碍距离
};




class TrajectoryCost{
public:
    TrajectoryCost(YAML::Node yaml_conf);
    void init(ObstacleList* obslist);
    void reset(int totallevel);
    void evaluate(const VectorXf& QP5,
                    const double start_s,
                    const double end_s,
                    int cur_level,
                    ConCost& cost);
    TrajectoryCost_conf conf;
private:

    double smoothcostdl(const VectorXf& QP5,
                    const double start_s,
                    const double end_s);
    double smoothcostddl(const VectorXf& QP5,
                    const double start_s,
                    const double end_s);
    double smoothcostdddl(const VectorXf& QP5,
                    const double start_s,
                    const double end_s);
    double lengthcost(const VectorXf& QP5,
                    const double start_s,
                    const double end_s);
    double nearcost(const VectorXf& QP5,
                    const double start_s,
                    const double end_s);
    double obstaclecost(const VectorXf& QP5,
                        const double start_s,
                        const double end_s);
    //临时变量
    int total_level;
    /**********引用模块*************/
    ObstacleList* obstaclelist;
};
