#ifndef __ATTITUDE_H
#define __ATTITUDE_H
#include "stm32f4xx.h"
#include "MPU6050.h"
#include "Filter.h"
#include "Math_User.h"
#include "Time.h"
#include "HMC5883.h"
#include "Common.h"
#include "Communication.h"
#include "Math_User.h"

extern struct Attitude_
{
	struct Vector* Rate; //原始多陀螺仪数据
	struct Vector* Angle;
	void (*Init)(void);
	void (*Updata)(void);
}Attitude;
#endif
