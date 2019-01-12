# auto-car

docs:   学习、教程、系统配置等文档资料

ros：   源代码（ros\gazebo)


一、caktin_make编译说明：

    配置说明： ENABLE_MPC lqr和mpc控制器的选择 ； ENABLE_SIMULATE 是否使用gazebo仿真的选择

        pc，for example ：caktin_make -DENABLE_MPC=OFF -DENABLE_SIMULATE=ON

        tx2,for example ：caktin_make -DENABLE_MPC=OFF -DENABLE_SIMULATE=OFF

        如需更改编译配置，只需第一次显示更改即可

    编译特定包：catkin_make -DCATKIN_WHITELIST_PACKAGES="<package_name>"，如package_name为空则全部编译

    清除编译生成文件：catkin_make clean

二、运行说明：
    1、先host 配置

        根据当前使用IP修改/etc/hosts：

            192.168.1.132 pc 

            192.168.1.110 tx2

        重启网络： sudo /etc/init.d/networking restart
        
    2、编译成功后，进入auto-car/ros目录

    运行: ./run.bash <$1> <$2>

    参数说明：$1:本地机器名  $2:作为ros master 的机器名

    机器名选项：pc和tx2

    for example:

        在电脑中调试：./run.bash pc pc

        在tx2中运行：./run.bash tx2 tx2  本地远程电脑运行：./run.bash pc tx2



