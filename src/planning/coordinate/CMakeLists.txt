
# 生成链接库
add_library(coordinate coordinate.cc)
add_dependencies(coordinate
    car_msgs_gencpp
)   

add_library(coordinate_task
    coordinate_task.cc
)
target_link_libraries(coordinate_task
    coordinate
    conf_node
)   