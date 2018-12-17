#ifndef __NRF24L01_H__
#define __NRF24L01_H__
#include "stm32f4xx.h"
#include "Common.h"
#include "NRF24L01_Register.h"
#include "Time.h"

struct NRF24L01_Data_
{
	u8 TX_BUF[32];
	u8 RX_BUF[32];
	u8 ACK_BUF[32];
};

volatile extern struct NRF24L01_
{
	struct NRF24L01_Data_* Data;
	BOOL (*Init)(NRF_State Mode);
	void (*SendData)(void);
	BOOL (*GetData)(void);
	BOOL (*RequsetAckBuf)(u8);
	void (*Free_RXBUF)(void);
}NRF24L01;



#endif
