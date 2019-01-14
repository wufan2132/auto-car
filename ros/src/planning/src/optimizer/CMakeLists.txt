
# 生成链接库
add_library(optimizer
    path_optimizer.cpp
    frenet_optimal.cpp
    dp_road_graph.cpp
    trajectory_cost.cpp
    dp_st_graph.cpp
    dp_st_cost.cpp
    ConCost.cpp)
