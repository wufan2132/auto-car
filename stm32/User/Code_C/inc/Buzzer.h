#ifndef __BUZZER_H__
#define __BUZZER_H__
#include "stm32f4xx.h"
#include "Time.h"

extern struct Buzzer_
{
	void (*Init)(void);
	void (*On)(u16 Time);
	void (*Off)(void);	
}Buzzer;

#endif
