# auto-car

docs:   学习、教程、系统配置等文档资料

ros：   源代码（ros\gazebo)


caktin_make编译说明：

    配置说明： ENABLE_MPC lqr和mpc控制器的选择 ； ENABLE_SIMULATE 是否使用gazebo仿真的选择

        pc，for example ：caktin_make -DENABLE_MPC=OFF -DENABLE_SIMULATE=ON

        tx2,for example ：caktin_make -DENABLE_MPC=OFF -DENABLE_SIMULATE=OFF

        如需更改编译配置，只需第一次显示更改即可

    编译特定包：catkin_make -DCATKIN_WHITELIST_PACKAGES="<package_name>"，如package_name为空则全部编译

    清除编译生成文件：catkin_make clean
    
