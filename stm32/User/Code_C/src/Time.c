#include "Time.h"

u32 usTicks;                    // 每US的Tick数
uint64_t TSTSTST;
volatile int64_t SystemTimeMS = 0;      // 滴答定时器,1MS

void Time_Init(void);
u32 TimeNow_MS(void);
int64_t TimeNow_US(void);
void Time_WaitMS(u32 Time);
void Time_WaitUS(u32 Time);

//函数指针初始化
struct SystemTime_ SystemTime = 
{
	Time_Init,
	TimeNow_MS,
	TimeNow_US,
	Time_WaitMS,
	Time_WaitUS,
};

void Time_Init(void)
{
	RCC_ClocksTypeDef clocks;
	RCC_GetClocksFreq(&clocks);
	usTicks = clocks.SYSCLK_Frequency / 1000000;
	SysTick_Config(clocks.SYSCLK_Frequency / 1000);	
}
extern "C"{
void SysTick_Handler(void)
{ 
	SystemTimeMS++;
}
}

u32 TimeNow_MS(void)
{
	return SystemTimeMS;
}

int64_t TimeNow_US(void) 
{
	register int64_t SysTick_Tmp;
	register int64_t SysTime_MS;
	SysTime_MS = SystemTimeMS;
	SysTick_Tmp = SysTick->VAL;
	if(SysTime_MS == SystemTimeMS)
	{
		return SysTime_MS * 1000 - SysTick_Tmp / usTicks + 1000;;
	}
	else
	{
		return SystemTimeMS * 1000 - SysTick->VAL / usTicks + 1000;;
	}
}

void Time_WaitMS(u32 Time)
{
	u32 Time_Now;

	Time_Now = TimeNow_MS();

	while(TimeNow_MS() < Time_Now + Time);
}

void Time_WaitUS(u32 Time)
{
	u32 Time_Now;

	Time_Now = TimeNow_US();

	while(TimeNow_US() < Time_Now + Time);
}

