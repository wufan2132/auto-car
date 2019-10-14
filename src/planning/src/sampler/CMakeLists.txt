
# 生成链接库
add_library(sampler sampler.cpp)
add_dependencies(sampler
    car_msgs_gencpp
)   