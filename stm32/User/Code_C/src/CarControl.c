#include "CarControl.h"

#define SPEED_PWM_BASE 3000
#define DIR_PWM_BASE 3000

//void Speed_Loop(u32 Time);
//void Direction_Loop(u32 Time);
void PWM_check();
struct Car_Control_Para_ Car_Control_Para = 
{
	Manual,
	False,
	False,
	False,
	
};

struct CarControl_ CarControl = 
{	
	&Car_Control_Para,
	PWM_check,
	0,
	0,
	0
};


void PWM_check(){
		Motor.PWM->PWM1 = CarControl.brake - CarControl.throttlt + SPEED_PWM_BASE;
		Motor.PWM->PWM2 = CarControl.steer + DIR_PWM_BASE;
}
//void Speed_Loop(u32 Time)
//{
//	if(Car_Control_Para.IsLock == True)            //停机 复位
//	{
//		Car_Control_Para.Speed_PID.Rst_I();
//		Motor.Stop();
//		return;
//	}

//	//Rate_filter_Temp = Rate_Filter.LPF2ndFilter(*Attitude.Rate);
//	//陀螺仪读取到的数据直接用于内环控制
//	Car_Control_Para.Speed_PID.Feedback = Attitude.Rate->x;
//	
//	Motor.PWM->PWM1 = Car_Control_Para.Speed_PID.Cal_PID_POS(Time);
//}
///*
//	弧度制单位 
//*/
//void Direction_Loop(u32 Time)
//{
//	if(Car_Control_Para.IsLock == True)            //停机 复位
//	{
//		Car_Control_Para.Direction_PID.Rst_I();
//		Motor.Stop();
//		return;
//	}

//	Car_Control_Para.Direction_PID.Feedback = Attitude.Rate->x;
//	
//	Motor.PWM->PWM2 = Car_Control_Para.Direction_PID.Cal_PID_POS(Time);
//}
