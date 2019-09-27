这是perception模块：
1.修改main.c中 yaml文件目录
2.修改参数只需修改yaml文件即可

发送topic: 
obstacle_topic：障碍物
########## base_obstacle说明
uint8 type # 0表示圆形 1表示方形

float64[] xa #3次多项式 x = a0 +a1*t+a2*t^2 +a3*t^3 
float64[] ya #3次多项式
float64[] theta_a #3次多项式 theta角 x轴与a边的夹角 顺时针为正 圆形这个就没有用了

float64 a #表示圆的直径或矩形的a边的长度
float64 b # b边的长度