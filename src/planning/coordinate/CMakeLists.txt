
# 生成链接库
add_library(coordinate coordinate.cc)
add_dependencies(coordinate
    car_msgs_gencpp
)   