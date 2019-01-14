#include "planning/trajectory_cost.h"
#define MAX_COST 9999.9

TrajectoryCost::TrajectoryCost(YAML::Node yaml_conf){
    conf.k_path = yaml_conf["k_path"].as<double>();
    conf.k_smooth_l = yaml_conf["k_smooth_l"].as<double>();
    conf.k_smooth_dl = yaml_conf["k_smooth_dl"].as<double>();
    conf.k_smooth_ddl = yaml_conf["k_smooth_ddl"].as<double>();
    conf.k_smooth_dddl = yaml_conf["k_smooth_dddl"].as<double>();

    conf.k_obstacle_l = yaml_conf["k_obstacle_l"].as<double>();
}


void TrajectoryCost::init(ObstacleList* obslist){
    obstaclelist = obslist;
}


void TrajectoryCost::reset(int totallevel){
    total_level = totallevel;
}
void TrajectoryCost::evaluate(const VectorXf& QP5,
                                const double start_s, 
                                const double end_s,
                                int cur_level,
                                ConCost& cost){
    cost.value("nearcost") = conf.k_smooth_l * nearcost(QP5, start_s, end_s);
    cost.value("smoothcostdl") = conf.k_smooth_dl * smoothcostdl(QP5, start_s, end_s);
    cost.value("smoothcostddl") = conf.k_smooth_ddl * smoothcostddl(QP5, start_s, end_s);
    cost.value("smoothcostdddl") = conf.k_smooth_dddl * smoothcostdddl(QP5, start_s, end_s);
    cost.value("obstaclecost") = conf.k_obstacle_l * obstaclecost(QP5, start_s, end_s);
    cost.auto_sum();
}

/*****************曲线平滑性*************************/
double TrajectoryCost::smoothcostdl(const VectorXf& QP5,
                                  const double start_s,
                                  const double end_s){
    double s = end_s - start_s;
    double a0 = QP5(0);
    double a1 = QP5(1);
    double a2 = QP5(2);
    double a3 = QP5(3);
    double a4 = QP5(4);
    double a5 = QP5(5);
    //一阶导数的平方的积分
    double dl2_cost = s*(s*(2*a1*a2 + s*(2*a1*a3 
    + (4*a2*a2)/3 + s*(2*a1*a4 + 3*a2*a3 + s*(2*a1*a5 
    + (16*a2*a4)/5 + (9*a3*a3)/5 + s*((10*a2*a5)/3 
    + 4*a3*a4 + s*((30*a3*a5)/7 + (16*a4*a4)/7 
    + s*((25*s*a5*a5)/9 + 5*a4*a5))))))) + a1*a1);
    return dl2_cost;
}
double TrajectoryCost::smoothcostddl(const VectorXf& QP5,
                                  const double start_s,
                                  const double end_s){
    double s = end_s - start_s;
    double a0 = QP5(0);
    double a1 = QP5(1);
    double a2 = QP5(2);
    double a3 = QP5(3);
    double a4 = QP5(4);
    double a5 = QP5(5);
    //二阶导数的平方的积分
    double ddl2_cost = 
    s*(s*(12*a2*a3 + s*(16*a2*a4 + 12*a3*a3 
    + s*(20*a2*a5 + 36*a3*a4 + s*(48*a3*a5 
    + (144*a4*a4)/5 + s*((400*s*a5*a5)/7 
    + 80*a4*a5))))) + 4*a2*a2);
    return ddl2_cost;
}
double TrajectoryCost::smoothcostdddl(const VectorXf& QP5,
                                  const double start_s,
                                  const double end_s){
    double s = end_s - start_s;
    double a0 = QP5(0);
    double a1 = QP5(1);
    double a2 = QP5(2);
    double a3 = QP5(3);
    double a4 = QP5(4);
    double a5 = QP5(5);
    //三阶导数的平方的积分
    double dddl2_cost = 
    s*(s*(144*a3*a4 + s*(240*a3*a5 + 192*a4*a4 
    + s*(720*s*a5*a5 + 720*a4*a5))) + 36*a3*a3);
    //
    return dddl2_cost;
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
    double s = end_s - start_s;
    double a0 = QP5(0);
    double a1 = QP5(1);
    double a2 = QP5(2);
    double a3 = QP5(3);
    double a4 = QP5(4);
    double a5 = QP5(5);
    //曲线平方的积分
    double l2_cost = 
    s*(a0*a0 + s*(a0*a1 + s*(s*((a0*a3)/2 + (a1*a2)/2 
    + s*((2*a0*a4)/5 + (2*a1*a3)/5 + a2*a2/5 
    + s*((a0*a5)/3 + (a1*a4)/3 + (a2*a3)/3 
    + s*((2*a1*a5)/7 + (2*a2*a4)/7 + a3*a3/7 
    + s*((a2*a5)/4 + (a3*a4)/4 + s*((2*a3*a5)/9 
    + a4*a4/9 + s*((s*a5*a5)/11 + (a4*a5)/5))))))) 
    + (2*a0*a2)/3 + a1*a1/3)));

    return l2_cost;
}

/*********曲线靠近referenceline*****************/
//sl曲线的曲率应该与referenceline曲率相反，这样生成的曲线在XY坐标下是直的


/****************曲线与障碍物********************/
#define CRITICAL_DISTANCE 0.5
#define IGNORE_DISTANCE 2.0
double TrajectoryCost::obstaclecost(const VectorXf& QP5,
                                    const double start_s,
                                    const double end_s){
    double cost = 0;
    double distance;
    for(int i=0;i<obstaclelist->list.size();i++){
        distance = ObstacleMethod::distance_Ob_QP(obstaclelist->list[i],QP5,start_s,end_s,0)
                    - obstaclelist->list[i].a;
        if(distance<CRITICAL_DISTANCE)
            cost += MAX_COST;
        else if(distance>IGNORE_DISTANCE)
            cost += 0;
        else 
            cost += 100*(IGNORE_DISTANCE - distance);
    }
    return cost;
}