#ifndef __MS5611_H__
#define __MS5611_H__
#include "stm32f4xx.h"
#include "I2C_Soft.h"
#include "Time.h"
#include "Common.h"
#include "arm_math.h"
#include "Filter.h"

#define MS5611_ALT_OFFECT (-65)
struct MS5611_Data_
{
	int64_t Temperature;
	int64_t Pressure;
	float Altitude;
	float Speed;
};

extern struct MS5611_
{
	struct MS5611_Data_* Data; 
	void (*Init)(void);
	void (*Updata)(void);
}MS5611;



#endif

