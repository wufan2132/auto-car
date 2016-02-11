#pragma once
#include "planning/common.h"
#include "planning/car_model.h"
#include "planning/sampler.h"
#include "planning/Fitting.h"
#include "planning/dp_st_cost.h"

using namespace Eigen;
using namespace std;

class StGraphNode
    :public Car_State_SL
{
public:
    StGraphNode()
    :Car_State_SL(),
    pre(NULL),next(NULL),min_pre(NULL),
    minCost(0){};

    StGraphNode(double s_, double l_)
    :Car_State_SL(s_, l_),
    pre(NULL),next(NULL),min_pre(NULL),
    minCost(0){};

    StGraphNode(Car_State_SL sl_p)
    :Car_State_SL(sl_p),
    pre(NULL),next(NULL),min_pre(NULL),
    minCost(0){};

    void UpdateCost(const StGraphNode *pre_node,
                    VectorXf& QP4,
                    double cost){
        if(cost<minCost||min_pre == NULL){
            minCost = cost;
            min_pre = pre_node;
            minQP4 = QP4;
        }
                    }
    const StGraphNode* pre;
    const StGraphNode* next;
    const StGraphNode* min_pre;
    VectorXf minQP4;
    double minCost;
};

class DpStGraph{
public:
    DpStGraph(YAML::Node yaml_conf);
    void reset(Car_State_SL init_SLpoint,
                Car_State_SL car_status,
                int total_level,
                double aim_speed); //

    void process(const vector<Car_State_SL>& path_waypoints,
                StGraphNode* min_cost_Node);
    void process(const vector<vector<Car_State_SL> >& path_waypoints,
                    vector<StGraphNode> *min_cost_path);
    void UpdateNode(const list<StGraphNode> &prev_nodes,
                        const int level, const int total_level,
                        StGraphNode *front,
                        StGraphNode *cur_node);
    list<list<StGraphNode> > graph_nodes;

    //
    double aim_speed = 0;

    StCost* stcost;
    Car_State_SL status_sl;
    Car_State_SL init_SLpoint;
};