#include "planning/dp_road_graph.h"

DpRoadGraph::DpRoadGraph(YAML::Node yaml_conf){
    trajectorycost = new TrajectoryCost(yaml_conf);
}


void DpRoadGraph::reset(Car_State_SL init_SLpoint, int total_level){
    trajectorycost->reset();
}

void DpRoadGraph::process(const vector<vector<Car_State_SL> >& path_waypoints){
//生成图节点
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
//寻找最好路径

}
}
void DpRoadGraph::UpdateNode(const list<RoadGraphNode> &prev_nodes,
                            const int level, const int total_level,
                            RoadGraphNode *front,
                            RoadGraphNode *cur_node){
    for (const auto& pre_node : prev_nodes) {
        double init_dl = 0;
        double init_ddl = 0;
        if(level == 0){
            init_dl = status_sl.dl;
            init_ddl = status_sl.ddl;
        }
        VectorXf QP5 = Fitting::quintic5_polynomial(pre_node.l,init_dl,init_ddl,
                                            cur_node->l,0,0,
                                            cur_node->s - pre_node.s);
        //曲线评估
        //IsValidCurve(QP5);
        double cost = trajectorycost->evaluate();
        cur_node->UpdateCost(&pre_node, QP5, cost);
    }
    //尝试连接初始点
    if(level>=1){
        double init_dl = status_sl.dl;
        double init_ddl = status_sl.ddl;
        VectorXf QP5 = Fitting::quintic5_polynomial(front->l,init_dl,init_ddl,
                                            cur_node->l,0,0,
                                            cur_node->s - front->s);
        //曲线评估
        //IsValidCurve(QP5);
        double cost = trajectorycost->evaluate();
        cur_node->UpdateCost(front, QP5, cost);
    }
}