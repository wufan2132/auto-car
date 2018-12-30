#include "CarControl.h"

#define SPEED_PWM_BASE 3000
#define DIR_PWM_BASE 3000
#define SPEED_LIMMIT_U 150
#define SPEED_LIMMIT_D -500
//void Speed_Loop(u32 Time);
//void Direction_Loop(u32 Time);
void PWM_output();
void Control_stop();

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
	PWM_output,
	Control_stop,
	0,
	0,
	0,
	0,
};


void Control_stop(){
	CarControl.throttlt = 0;
	CarControl.brake = 0;
	CarControl.steer = 0;
}


void PWM_output(){
		int Motor_speed = CarControl.throttlt - CarControl.brake;
		Motor_speed = Math.Constrain(Motor_speed, SPEED_LIMMIT_U, SPEED_LIMMIT_D);
		Motor.PWM->PWM1 = SPEED_PWM_BASE - Motor_speed;
		Motor.PWM->PWM2 = CarControl.steer + DIR_PWM_BASE;
		Motor.Output(False);
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
