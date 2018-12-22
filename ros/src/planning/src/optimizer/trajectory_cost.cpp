#include "planning/trajectory_cost.h"


TrajectoryCost::TrajectoryCost(YAML::Node yaml_conf){}
void TrajectoryCost::reset(int totallevel){
    total_level = totallevel;
}
double TrajectoryCost::evaluate(const VectorXf& QP5,
                                const double start_s,
                                const double end_s,
                                int cur_level){
        Cost CostValue;
        CostValue.pathcost.smoothcost =  smoothcost(QP5, start_s, end_s);


        //总计
        CostValue.pathcost.sum += CostValue.pathcost.smoothcost;

        CostValue.total_cost += CostValue.pathcost.sum;
        return CostValue.total_cost;
}


/*****************曲线平滑性*************************/
//用二阶以上的导数
double TrajectoryCost::smoothcost(const VectorXf& QP5,
                                  const double start_s,
                                  const double end_s){
    // ((400*QP5(5)^2)/7)*(end_s^7 - end_s^7)+ 
    // (80*QP5(4)*QP5(5))*s^6 + 
    // ((144*QP5(4)^2)/5 + 48*QP5(3)*QP5(5))*s^5 + 
    // (20*QP5(2)*QP5(5) + 36*QP5(3)*QP5(4))*s^4 + 
    // (12*QP5(3)^2 + 16*QP5(2)*QP5(4))*s^3 + 
    // (12*QP5(2)*QP5(3))*s^2 + 
    // (4*QP5(2)^2)*s

}

/*****************曲线长度******************/
double TrajectoryCost::lengthcost(const VectorXf& QP5,
                                  const double start_s,
                                  const double end_s){

}

/*********曲线靠近referenceline*****************/
double TrajectoryCost::nearcost(const VectorXf& QP5,
                                  const double start_s,
                                  const double end_s){

}
