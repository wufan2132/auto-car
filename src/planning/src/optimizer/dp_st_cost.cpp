#include "planning/dp_st_cost.h"


StCost::StCost(YAML::Node yaml_conf){}
void StCost::reset(int totallevel){
    total_level = totallevel;
}
double StCost::evaluate(const VectorXf& QP5,
                                const double start_s,
                                const double end_s,
                                int cur_level){
        // Cost CostValue;
        // CostValue.pathcost.smoothcost =  smoothcost(QP5, start_s, end_s);


        // //总计
        // CostValue.pathcost.sum += CostValue.pathcost.smoothcost;

        // CostValue.total_cost += CostValue.pathcost.sum;
        // return CostValue.total_cost;
        return smoothcost(QP5, start_s, end_s);
}


// /*****************曲线平滑性*************************/
//用二阶以上的导数
double StCost::smoothcost(const VectorXf& QP4,
                                  const double start_s,
                                  const double end_s){
    double s = end_s - start_s;
    double a0 = QP4(0);
    double a1 = QP4(1);
    double a2 = QP4(2);
    double a3 = QP4(3);
    double a4 = QP4(4);
    //二阶导数的平方
    double ddl2_cost = 
    s*(s*(12*a2*a3 + s*(16*a2*a4 
    + 12*a3*a3 + s*((144*s*a4*a4)/5 
    + 36*a3*a4))) + 4*a2*a2);
    //三阶导数的平方
    double dddl2_cost = 
    s*(36*a3*a3 + s*(192*s*a4*a4 
    + 144*a3*a4));

    //
    return ddl2_cost + dddl2_cost;
}

// /*****************曲线长度******************/
// double StCost::lengthcost(const VectorXf& QP5,
//                                   const double start_s,
//                                   const double end_s){

// }

// /*********曲线靠近referenceline*****************/
// double StCost::nearcost(const VectorXf& QP5,
//                                   const double start_s,
//                                   const double end_s){

// }
