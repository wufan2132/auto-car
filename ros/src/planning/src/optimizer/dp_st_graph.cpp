#include "planning/dp_st_graph.h"

DpStGraph::DpStGraph(YAML::Node yaml_conf){
    stcost = new StCost(yaml_conf);
}


void DpStGraph::reset(Car_State_SL init_sl, Car_State_SL car_status,
                        int total_level, double aim_v){
    init_SLpoint = init_sl;
    status_sl = car_status;
    aim_speed = aim_v;
    stcost->reset(total_level);
}

void DpStGraph::process(const vector<Car_State_SL>& path_waypoints,
                StGraphNode* min_cost_Node){
    vector<vector<Car_State_SL> > path_waypoints2d;
    vector<StGraphNode> min_cost_path;
    path_waypoints2d.emplace_back(path_waypoints);
    process(path_waypoints2d, &min_cost_path);
    *min_cost_Node = min_cost_path.back();
}


void DpStGraph::process(const vector<vector<Car_State_SL> >& path_waypoints,
                            vector<StGraphNode> *min_cost_path){
//生成图节点
graph_nodes.clear();
graph_nodes.emplace_back();
graph_nodes.back().emplace_back(init_SLpoint);//插入初始点
StGraphNode &front = graph_nodes.front().front();
size_t total_level = path_waypoints.size();
    for (std::size_t level = 0; level < path_waypoints.size(); ++level) {
        const list<StGraphNode> &prev_dp_nodes = graph_nodes.back();
        const vector<Car_State_SL> &level_points = path_waypoints[level];
        //list插入新的列
        graph_nodes.emplace_back();
        for(int i=0;i<level_points.size();i++){
            const Car_State_SL &cur_point = level_points[i];
            graph_nodes.back().emplace_back(cur_point);
            StGraphNode &cur_node = graph_nodes.back().back();
            //更新当前点的信息
            UpdateNode(prev_dp_nodes, level, total_level, &front, &cur_node);
    }
}
//寻找最好路径
StGraphNode fake_head;
for(auto &cur_dp_node : graph_nodes.back())
    fake_head.UpdateCost(&cur_dp_node, cur_dp_node.minQP4,cur_dp_node.minCost);
const auto *min_cost_node = &fake_head;
  while (min_cost_node->min_pre) {
    min_cost_node = min_cost_node->min_pre;
    min_cost_path->push_back(*min_cost_node);
  }
min_cost_path->push_back(init_SLpoint);
reverse(min_cost_path->begin(), min_cost_path->end());
}

void DpStGraph::UpdateNode(const list<StGraphNode> &prev_nodes,
                            const int level, const int total_level,
                            StGraphNode *front,
                            StGraphNode *cur_node){
    for (const auto& pre_node : prev_nodes) {
        double init_sv = 0;
        double init_sa = 0;
        double pre_node_t = pre_node.t;
        if(level == 0){
            init_sv = init_SLpoint.sv;
            init_sa = init_SLpoint.sa;
            pre_node_t = 0;
        }
        VectorXf QP4 = Fitting::quartic4_polynomial(pre_node.s - init_SLpoint.s ,init_sv,init_sa,
                                            aim_speed,0,cur_node->t - pre_node_t);
        //曲线评估
        //IsValidCurve(QP4);
        double cost = stcost->evaluate(QP4, pre_node.t, cur_node->t, level);
        // cout<<"UpdateNode:--------st-------------"<<endl;
        // cout<<"start.s:"<<pre_node.s - init_SLpoint.s<<endl;
        // cout<<"start.v:"<<init_sv<<endl;
        // cout<<"start.a:"<<init_sa<<endl;
        // cout<<"end.v:"<<aim_speed<<endl;
        // cout<<"dt:"<<cur_node->t - pre_node_t<<endl;
        // cout<<"cost:"<<cost<<endl;
        cur_node->UpdateCost(&pre_node, QP4, cost);
    }
    //尝试连接初始点
    if(level>=1){
        double init_sv = init_SLpoint.sv;
        double init_sa = init_SLpoint.sa;
        VectorXf QP4 = Fitting::quartic4_polynomial(0,init_sv,init_sa,
                                            5,0,cur_node->t);
        //曲线评估
        //IsValidCurve(QP4);
        double cost = stcost->evaluate(QP4, front->t, cur_node->t, level);
        cur_node->UpdateCost(front, QP4, cost);
    }
}