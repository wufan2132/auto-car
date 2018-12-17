#ifndef __USART_H__
#define __USART_H__
#include "stm32f4xx.h"
#include "Common.h"
#include "Queue.h"

extern struct usart_
{
	void (*init)(u32 bound);
	BOOL (*send)(u8 *data, u16 num);
	BOOL (*receive)(u8 *data, u16 num);
}usart1;


#endif
