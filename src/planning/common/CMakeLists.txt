



# 生成链接库
add_library(planning_gflags
    planning_gflags.cc
)

add_library(frame
    frame.cc
)

add_dependencies(frame
    car_msgs_gencpp
)
