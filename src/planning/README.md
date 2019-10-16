## 这是planning模块：  
1.修改main.c中 yaml文件目录,默认是 my-code/auto-car  
2.修改参数只需修改yaml文件即可,包括planning目录下与conf目录下的yaml文件。  
3.相关说明参照doc目录下的文档。  




#### 发送topic:
refrenceline_topic：参考线  
trajectory_topic:当前轨迹规划  
#### 接收topic:
localization_topic: 车体全局位置信息  
chassis_topic： 底盘传感器信息  
obstacle_topic： 感知模块预测的障碍物信息  
