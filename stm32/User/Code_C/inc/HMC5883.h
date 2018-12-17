#ifndef __HMC5883_H__
#define __HMC5883_H__
#include "stm32f4xx.h"
#include "Common.h"
#include "I2C_Soft.h"
#include "Time.h"
#include "Filter.h"
#include "arm_math.h"
struct HMC5883_Data_
{
	Vector MAG_ADC;
	Vector MAG_Original;
	Vector Kp;
	Vector Offset;
	float Length;
	int ErrorCnt;
};

extern struct HMC5883_
{
	BOOL IsSensorError;
	struct HMC5883_Data_* Data;
	void (*Init)(void);
	void (*Updata)(void);
}HMC5883;


#endif
