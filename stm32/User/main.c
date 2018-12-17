#include "Board.h"

Target_ TG_50HZ(Scheduler.Loop_50Hz,20000);
Target_ TG_100HZ(Scheduler.Loop_100Hz,10000);
Target_ TG_200HZ(Scheduler.Loop_200Hz,5000);
Target_ TG_500HZ(Scheduler.Loop_500Hz,2000);
//-------Ê±¼ä²âÊÔº¯Êý------------------------//
float Test_Time = 0;
void Get_Time(void)
{
	uint64_t Time_Now = 0;
	static uint64_t Time_Pre = 0;
	
	Time_Now = SystemTime.Now_US();
	Test_Time = (Time_Now - Time_Pre);
	Time_Pre = Time_Now;
}
//extern void Get_Time(void);
//Get_Time();

//-------------------------------------------//
int main(void)
{//test6
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
	SystemTime.Init();
	Led.Init();
	Buzzer.Init();
	//SD_APP.init();
	usart1.init(115200);
	Attitude.Init();
  Position.Init();
	PWM_In.Init(2000,4000);
	Power.Init();
	Motor.Init();
	speed_measure.init();
	while(1)
	{		
		TG_50HZ.Run();
		TG_100HZ.Run();
		TG_200HZ.Run();
		TG_500HZ.Run();
	}
}





