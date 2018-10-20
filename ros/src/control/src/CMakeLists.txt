# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)
# 添加子目录
add_subdirectory(controller)
add_subdirectory(common)
# 添加链接库
target_link_libraries(control 
${DIR_LIB_SRCS}
pid_controller
controller
)
