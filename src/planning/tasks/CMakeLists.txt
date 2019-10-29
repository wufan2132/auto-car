
# 生成链接库
add_library(task_factory 
    task_factory.cc
)
target_link_libraries(task_factory
    record_trajectory
    refrenceline_provider
    interpolating_refrenceline
    trajectory
    og_planner
    coordinate_task
)  