
# 生成链接库
add_library(replay 
    replay.cc
)
add_dependencies(replay
    car_msgs_gencpp
)  

add_library(record_trajectory 
record_trajectory.cc)
target_link_libraries(record_trajectory
    replay
    conf_node
)   