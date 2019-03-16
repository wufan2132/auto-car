这是planning模块：
1.修改main.c中 yaml文件目录,默认是 my-code/auto-car
2.修改参数只需修改yaml文件即可,包括planning目录下与conf目录下的yaml文件。
3.相关说明参照doc目录下的文档。




# 发送topic: 
refrenceline_topic：参考线
trajectory_topic:当前轨迹规划
# 接收topic:
localization_topic: 车体全局位置信息
chassis_topic： 底盘传感器信息
obstacle_topic： 感知模块预测的障碍物信息

　


更新说明：
# 12.6
1.添加启动判断，见planning::init
2.添加偏差过大时重新选择路径
# 1.3
1.重新优化代码结构，抽象出规划器对象
2.添加单点规划器（spplanner）
3.原规划器重命名为ogplanner
4.添加全局轨迹规划对象refrenceline
# 1.8
1.添加多点规划器(mpplanner)
2.添加测试规划器(testplanner)
3.添加障碍物接收