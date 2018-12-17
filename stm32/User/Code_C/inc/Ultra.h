#ifndef __ULTRA_H__
#define __ULTRA_H__
#include "stm32f4xx.h"
#include "Common.h"
#include "Time.h"
#include "I2C_Soft.h"
#include "Filter.h"
extern struct Ultra_
{
	float Altitude;
	float Speed;
	void (*Init)(void);
	void (*Updata)(void);
}Ultra;


#endif

