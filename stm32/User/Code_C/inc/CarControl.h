#ifndef __CARCONTROL__H
#define __CARCONTROL__H
#include "PID.h"
#include "Attitude.h"
#include "Common.h"
#include "SBUS.h"
#include "Motor.h"
#include "HMC5883.h"
#include "PWM_Capture.h"
enum Car_Mode
{
	Auto,
	Manual,
	Other
};

struct Car_Control_Para_
{
	Car_Mode Mode;
	
	BOOL IsLock;
	BOOL IsLost;
	BOOL IsError;
};

extern struct CarControl_
{
	struct Car_Control_Para_* Para;

	void (*PWM_output)();
	void (*stop)();
	int throttlt;
	int brake;
	int steer;
	int test;
}CarControl;

#endif
