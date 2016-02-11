#pragma once
#include "planning/common.h"
#include "planning/car_model.h"


class TrajectoryCost_conf{
public:
    double k_smooth;
};




class TrajectoryCost{
public:
    TrajectoryCost(YAML::Node yaml_conf);
    void reset(int totallevel);
    double evaluate(const VectorXf& QP5,
                    const double start_s,
                    const double end_s,
                    int cur_level);
    TrajectoryCost_conf* conf;
private:
    double smoothcost(const VectorXf& QP5,
                    const double start_s,
                    const double end_s);
    double lengthcost(const VectorXf& QP5,
                    const double start_s,
                    const double end_s);
    double nearcost(const VectorXf& QP5,
                    const double start_s,
                    const double end_s);
    //临时变量
    int total_level;

    //cost类
    class Cost{
    public:
        struct pathcost_
        {
            /* data */
            double smoothcost=0;
            double lengthcost=0;
            double nearcost=0;
            double sum=0;
        };
        pathcost_ pathcost;
        double total_cost=0;
    };

};
