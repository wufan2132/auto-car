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
    double s = end_s - start_s;
    double a0 = QP5(0);
    double a1 = QP5(1);
    double a2 = QP5(2);
    double a3 = QP5(3);
    double a4 = QP5(4);
    double a5 = QP5(5);
    //二阶导数的平方
    double ddl2_cost = 
    s*(a0*a0 + s*(a0*a1 + s*(s*((a0*a3)/2 + (a1*a2)/2 
    + s*((2*a0*a4)/5 + (2*a1*a3)/5 + a2*a2/5 
    + s*((a0*a5)/3 + (a1*a4)/3 + (a2*a3)/3 
    + s*((2*a1*a5)/7 + (2*a2*a4)/7 + a3*a3/7 
    + s*((a2*a5)/4 + (a3*a4)/4 + s*((2*a3*a5)/9 
    + a4*a4/9 + s*((s*a5*a5)/11 + (a4*a5)/5))))))) 
    + (2*a0*a2)/3 + a1*a1/3)));
    //三阶导数的平方
    double dddl2_cost = 
    s*(s*(144*a3*a4 + s*(240*a3*a5 + 192*a4*a4 
    + s*(720*s*a5*a5 + 720*a4*a5))) + 36*a3*a3);

    //
    return ddl2_cost + dddl2_cost;
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

/****************曲线与障碍物********************/
//double TrajectoryCost::obstaclecost(const VectorXf& QP5,const vector<Obstacle>& ObstacleList)