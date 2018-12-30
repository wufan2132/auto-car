#include "planning/common.h"
#include "planning/car_model.h"
#include "planning/sampler.h"
#include "planning/Fitting.h"
#include "planning/trajectory_cost.h"

using namespace Eigen;
using namespace std;

class RoadGraphNode
    :public Car_State_SL
{
public:
    RoadGraphNode()
    :Car_State_SL(){};

    RoadGraphNode(double s_, double l_)
    :Car_State_SL(s_, l_){};

    RoadGraphNode(Car_State_SL sl_p)
    :Car_State_SL(sl_p){};

    void UpdateCost(const RoadGraphNode *pre_node,
                    VectorXf& QP5,
                    double cost){
        if(cost<minCost||min_pre == NULL){
            minCost = cost;
            min_pre = pre_node;
            minQP5 = QP5;
        }
                    }
    const RoadGraphNode* pre = NULL;
    const RoadGraphNode* next = NULL;
    const RoadGraphNode* min_pre = NULL;
    VectorXf minQP5;
    double minCost = INT_MAX;
};

class DpRoadGraph{
public:
    DpRoadGraph(YAML::Node yaml_conf);
    void reset(Car_State_SL init_SLpoint,Car_State_SL car_status, int total_level); //
    void process(const vector<Car_State_SL>& path_waypoints,
                    RoadGraphNode* min_cost_Node);
    void process(const vector<vector<Car_State_SL> >& path_waypoints,
                    vector<RoadGraphNode> *min_cost_path);
    void UpdateNode(const list<RoadGraphNode> &prev_nodes,
                        const int level, const int total_level,
                        RoadGraphNode *front,
                        RoadGraphNode *cur_node);
    list<list<RoadGraphNode> > graph_nodes;

    TrajectoryCost* trajectorycost;
    Car_State_SL status_sl;
    Car_State_SL init_SLpoint;
};