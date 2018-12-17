#include "Scheduler.h"
void Loop_1000Hz(u16 Time);
void Loop_500Hz(u16 Time);
void Loop_200Hz(u16 Time);
void Loop_100Hz(u16 Time);
void Loop_50Hz(u16 Time);

struct Scheduler_ Scheduler = 
{
	Loop_1000Hz,
	Loop_500Hz,
	Loop_200Hz,
	Loop_100Hz,
	Loop_50Hz
};

void Loop_1000Hz(u16 Time_Ms)
{
	
}

void Loop_500Hz(u16 Time_Ms)
{
  MPU6050.Updata();											//mpu6050数据采集
	Attitude.Updata();										//姿态解算								-----姿态解算
	//FlyControl.ATT_InnerLoop(Time_Ms);		//姿态控制内环           -----------------------------------姿态 内环
	//FlyControl.POS_AccLoop(Time_Ms);			//位置控制加速度环				-------------------位置 加速度环
}
void Loop_200Hz(u16 Time_Ms)
{
	Position.Updata(Time_Ms);							//位置解算								-----位置解算
	HMC5883.Updata();											//磁力计数据采集
	//FlyControl.ATT_OuterLoop(Time_Ms);		//姿态控制外环						-----------------------------------姿态 外环
  //FlyControl.POS_InnerLoop(Time_Ms);		//位置控制速度内环				-------------------位置 速度环
}
void Loop_100Hz(u16 Time_Ms)
{
	MS5611.Updata();											//气压计数据采集		
	speed_measure.speed_get(Time_Ms);
}
void Loop_50Hz(u16 Time_Ms)
{
	//GPS_Location.GPS_Update();						//GPS数据采集
//	PWM_In.Updata();											//遥控数据采集 
  //FlyControl.POS_OuterLoop(Time_Ms);		//位置控制外环						-------------------位置 环
	Power.Updata();												//电压数据采集
	SystemState.Updata(Time_Ms);					//系统状态监控	
	Communication.UpData();								//调试通信	
	if(CarControl.Para->IsLock == True){
		Motor.Stop();
		return;
	}
	
	if(CarControl.Para->Mode == Auto){
		CarControl.PWMcheck();
		Motor.Output(False);
		//Motor.Stop();
	}
	else if(CarControl.Para->Mode == Manual){
		Motor.PWM->PWM1 = PWM_In.Data->CH1;
		Motor.PWM->PWM2 = PWM_In.Data->CH2;

		Motor.Output(False);

	}
	

}



