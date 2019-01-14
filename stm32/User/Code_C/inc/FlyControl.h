#ifndef __FLYCONTROL__H
#define __FLYCONTROL__H
#include "PID.h"
#include "Attitude.h"
#include "Common.h"
#include "SBUS.h"
#include "Motor.h"
#include "HMC5883.h"
#include "PWM_Capture.h"
enum Fly_Mode
{
	ATT,
	ALT,
	POS,
};
enum Head_Mode_
{
	HEAD,
	NO_HEAD,
};

struct Control_Para_
{
	PID ATT_Inner_PID_x;
	PID ATT_Inner_PID_y;
	PID ATT_Inner_PID_z;
	
	PID ATT_Outer_PID_x;
	PID ATT_Outer_PID_y;	
	PID ATT_Outer_PID_z;	
	
	PID POS_Acc_PID_x;
	PID POS_Acc_PID_y;
	PID POS_Acc_PID_z;
	
	PID POS_Inner_PID_x;
	PID POS_Inner_PID_y;
	PID POS_Inner_PID_z;
	
	PID POS_Outer_PID_x;
	PID POS_Outer_PID_y;
	PID POS_Outer_PID_z;
	int Throttle;
	
	float Home_Z_Angle;
	Vector Home;
	BOOL IsLock;
	BOOL IsLost;
	BOOL IsError;
	
	Head_Mode_ Head_Mode;
	Fly_Mode Mode;
};

extern struct FlyControl_
{
	struct Control_Para_* Para;

	void (*ATT_InnerLoop)(u32 Time);
	void (*ATT_OuterLoop)(u32 Time);
	
	void (*POS_AccLoop)(u32 Time);
	void (*POS_InnerLoop)(u32 Time);
	void (*POS_OuterLoop)(u32 Time);
	
}FlyControl;

#endif
