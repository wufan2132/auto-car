
# 生成链接库
add_library(og_planner
    og_planner.cc
)
add_dependencies(og_planner
    car_msgs_gencpp
)  
target_link_libraries(og_planner
    coordinate
)