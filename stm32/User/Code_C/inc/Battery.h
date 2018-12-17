#ifndef __BATTERY_H__
#define __BATTERY_H__
#include "stm32f4xx.h"
#include "ADS1118.h"
#include "Common.h"
struct Power_VOL_Data_
{
	float BAT_3S;
	BOOL IsUPS_On; 
};

extern struct  Power_
{
	struct Power_VOL_Data_* Data;
	void (*Init)(void);
	void (*Updata)(void);
}Power;


void ADC_Init();
#endif
