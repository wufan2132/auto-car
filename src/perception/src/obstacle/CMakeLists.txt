
# 生成链接库
add_library(obstacle_tool
    reader.cpp
    obstacle_set.cpp)
add_dependencies(obstacle_tool
    car_msgs_gencpp
)   