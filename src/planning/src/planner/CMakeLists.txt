
# 生成链接库
add_library(planner
    planner.cpp
    og_planner.cpp
    sp_planner.cpp
    mp_planner.cpp
    test_planner.cpp)
add_dependencies(planner
    car_msgs_gencpp
)   