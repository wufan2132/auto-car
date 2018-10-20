# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)
# 生成链接库
add_library(pid_controller ${DIR_LIB_SRCS})

