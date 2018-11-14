

FIND_LIBRARY(YAML_CPP_LIBRARIES yaml-cpp)
# 生成链接库
add_library(planning planning.cpp)

target_link_libraries(planning ${YAML_CPP_LIBRARIES})
