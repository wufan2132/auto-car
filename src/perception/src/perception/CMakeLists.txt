
# 生成链接库
add_library(perception
    perception.cpp)
add_dependencies(perception
    car_msgs_gencpp
)   