
FIND_LIBRARY(YAML_CPP_LIBRARIES yaml-cpp)

# 生成链接库
add_library(controller controller.cc lon_controller.cc)
target_link_libraries(controller pid_controller)
target_link_libraries(controller ${YAML_CPP_LIBRARIES})