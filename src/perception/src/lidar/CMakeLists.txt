
# 生成链接库
add_library(lidar_handle
    lidar_handle.cpp)
add_dependencies(lidar_handle
    car_msgs_gencpp
)   