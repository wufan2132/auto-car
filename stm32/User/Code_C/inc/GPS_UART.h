#ifndef __GPS_UART_H__
#define __GPS_UART_H__
#include "stm32f4xx.h"
#include "Queue.h"
#include "Common.h"
#define GPS_UART_BUF_SIZE 255

#define USE_GPS_PC 0  //GPS占用串口1进行调试  需要统一波特率为GPS波特率 9600


extern struct GPS_UART_
{
	void (*Init)(u32 Bound);
	BOOL (*send)(u8 *data, u16 num);
	u8 (*receive)(u8 *data, u16 num);
	void (*GPS_Cof)(void);
}GPS_UART;
struct GPS_UART_RX_
{
	u8 Data[GPS_UART_BUF_SIZE];	
	u8 Data_Siz;
	u32 Time_Now;
	u32 Time_Old;
};

#endif


