
# 生成链接库
add_library(trajectory 
    trajectory_stitcher.cpp 
    trajectory_generation.cpp)
add_dependencies(trajectory
    car_msgs_gencpp
)   