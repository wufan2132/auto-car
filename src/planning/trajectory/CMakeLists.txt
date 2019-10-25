
# 生成链接库
add_library(trajectory 
    trajectory_start_point.cc
    trajectory_generation.cc
)
add_dependencies(trajectory
    car_msgs_gencpp
)  
