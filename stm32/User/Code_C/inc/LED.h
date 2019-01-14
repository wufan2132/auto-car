#ifndef __LED_H__
#define __LED_H__
#include "stm32f4xx.h"
#include "Time.h"
#define LED1 GPIO_Pin_13

extern struct LED_
{
	u16* State;
	void (*Init)(void);
	void (*On)(u16 LEDX);
	void (*Off)(u16 LEDX);
	void (*Reverse)(u16 LEDX,u32 Time);

}Led;

#endif
