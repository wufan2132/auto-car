#ifndef __HALLSPEED_H__
#define __HALLSPEED_H__
#include "stm32f4xx.h"
#include "stdint.h"
#include "Math_User.h"

#define MEASURE_FREQUENT 1000.0f
#define MEASURE_RANGE 1000
#define SPEED_MAX 50


extern struct speed_measure_{
	void (*init)(void);
	void (*speed_get)(u16 Time);
	float Value;
}speed_measure;
 

#endif



