1、预期：

搭建自动驾驶系统

至少具备规划&控制层

前期基于仿真，顺利的话后期移植实车

TODO

2、初步方案：

系统架构：ROS
 
规划&控制实现：先移植实现apollo代码规划&控制代码

仿真实现：
    
基于gazebo开源平台，gazebo功能多，适合后期多方面应用

基于carsim，非开源，有较老的破解版可以满足应用，功能专业，车辆仿真

轨迹规划发送->轨迹跟随控制->仿真模型


TODO

3、开源项目：

https://github.com/ApolloAuto/apollo     
https://github.com/CPFL/Autoware         
https://github.com/osrf/car_demo          //里面有gazebo模型
