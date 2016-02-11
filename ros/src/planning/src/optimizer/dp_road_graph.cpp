#include "planning/dp_road_graph.h"

DpRoadGraph::DpRoadGraph(YAML::Node yaml_conf){
    trajectorycost = new TrajectoryCost(yaml_conf["TrajectoryCost_conf"]);
}

void DpRoadGraph::init(ObstacleList* obslist){
    obstaclelist = obslist;
    trajectorycost->init(obslist);
}

void DpRoadGraph::reset(Car_State_SL init_sl,Car_State_SL car_status, int total_level){
    init_SLpoint = init_sl;
    status_sl = car_status;
    trajectorycost->reset(total_level);
}


void DpRoadGraph::process(const vector<Car_State_SL>& path_waypoints,
                RoadGraphNode* min_cost_Node){
    vector<vector<Car_State_SL> > path_waypoints2d;
    vector<RoadGraphNode> min_cost_path;
    path_waypoints2d.emplace_back(path_waypoints);
    process(path_waypoints2d, &min_cost_path);
    *min_cost_Node = min_cost_path.back();
}



void DpRoadGraph::process(const vector<vector<Car_State_SL> >& path_waypoints,
                            vector<RoadGraphNode> *min_cost_path){
//生成图节点
graph_nodes.clear();
graph_nodes.emplace_back();
graph_nodes.back().emplace_back(init_SLpoint);//插入初始点
RoadGraphNode &front = graph_nodes.front().front();
size_t total_level = path_waypoints.size();
    for (std::size_t level = 0; level < path_waypoints.size(); ++level) {
        const list<RoadGraphNode> &prev_dp_nodes = graph_nodes.back();
        const vector<Car_State_SL> &level_points = path_waypoints[level];
        //list插入新的列
        graph_nodes.emplace_back();
        for(int i=0;i<level_points.size();i++){
            const Car_State_SL &cur_point = level_points[i];
            graph_nodes.back().emplace_back(cur_point);
            RoadGraphNode &cur_node = graph_nodes.back().back();
            //更新当前点的信息
            UpdateNode(prev_dp_nodes, level, total_level, &front, &cur_node);
    }
}
//寻找最好路径
//cout<<"---------BEST PATH--------"<<endl;
RoadGraphNode fake_head;
for(auto &cur_dp_node : graph_nodes.back())
    fake_head.UpdateCost(&cur_dp_node, cur_dp_node.minQP5,cur_dp_node.minCost);
const auto *min_cost_node = &fake_head;
min_cost_path->clear();
  while (min_cost_node->min_pre) {
    min_cost_node = min_cost_node->min_pre;
    min_cost_path->push_back(*min_cost_node);
    // cout<<"("<<min_cost_node->s<<","<<min_cost_node->l<<")"<<endl;
    // cout<<"qp5"<<endl;
    // cout<<min_cost_node->minQP5<<endl;
  }
reverse(min_cost_path->begin(), min_cost_path->end());
}

void DpRoadGraph::UpdateNode(const list<RoadGraphNode> &prev_nodes,
                            const int level, const int total_level,
                            RoadGraphNode *front,
                            RoadGraphNode *cur_node){
    for (const auto& pre_node : prev_nodes) {
        double init_dl = 0;
        double init_ddl = 0;
        if(level == 0){
            init_dl = init_SLpoint.dl;
            init_ddl = init_SLpoint.ddl;
        }
        VectorXf QP5 = Fitting::quintic5_polynomial(pre_node.l,init_dl,init_ddl,
                                            cur_node->l,0,0,
                                            cur_node->s - pre_node.s);
        //曲线评估
        //IsValidCurve(QP5);
        ConCost cost;
        trajectorycost->evaluate(QP5, pre_node.s, cur_node->s, level, cost);
        cost += pre_node.minCost;
        // cout<<"UpdateNode:---"<<"level:"<<level<<"-------------------"<<endl;
        // cout<<"cur_node->l:"<<cur_node->l<<endl;
        // cout<<"cur_node->s:"<<cur_node->s<<endl;
        // cout<<"pre_node.l:"<<pre_node.l<<endl;
        // cout<<"pre_node.s:"<<pre_node.s<<endl;
        // cout<<"init_dl:"<<init_dl<<endl;
        // cout<<"init_ddl"<<init_ddl<<endl;
        // cout<<"cost:"<<cost<<endl;
        cur_node->UpdateCost(&pre_node, QP5, cost);
    }
    //尝试连接初始点
    if(level>=1){
        double init_dl = init_SLpoint.dl;
        double init_ddl = init_SLpoint.ddl;
        VectorXf QP5 = Fitting::quintic5_polynomial(front->l,init_dl,init_ddl,
                                            cur_node->l,0,0,
                                            cur_node->s - front->s);
        //曲线评估
        //IsValidCurve(QP5);
        ConCost cost;
        trajectorycost->evaluate(QP5, front->s, cur_node->s, level, cost);
        cur_node->UpdateCost(front, QP5, cost);
    }
}