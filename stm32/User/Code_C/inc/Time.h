#ifndef __TIME_H__
#define __TIME_H__
#include "stm32f4xx.h"

extern struct SystemTime_
{
	void (*Init)(void);
	u32  (*Now_MS)(void);
	int64_t  (*Now_US)(void);
	void (*WaitMS)(u32 Time);
	void (*WaitUS)(u32 Time);

}SystemTime;

#endif
