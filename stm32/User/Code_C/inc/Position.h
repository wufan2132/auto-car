#ifndef __POSITION_H__
#define __POSITION_H__
#include "MS5611.h"
#include "Math_User.h"
#include "Attitude.h"
#include "Time.h"
#include "Common.h"
#include "Ultra.h"
extern struct Position_
{
	Vector Position_xyz;
	Vector Speed;
	Vector Acc;
	void (*Init)(void);
	void (*Updata)(u16 Time_Ms);
}Position;

#endif
