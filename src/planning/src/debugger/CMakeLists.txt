
# 生成链接库
add_library(debugger
            debugger.cpp)
add_dependencies(debugger
    car_msgs_gencpp
)   