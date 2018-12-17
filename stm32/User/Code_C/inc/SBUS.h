#ifndef __SBUS_H__
#define __SBUS_H__
#include "stm32f4xx.h"
#include "Time.h"
#include "Common.h"
#include "Motor.h"
void SBUS_Init(void);
void TSTSTS(void);

#define CHANNEL_COUNT 12 
#define SBUS_MIN  PWM_LIMIT_D 
#define SBUS_MID (u16)((PWM_LIMIT_D + PWM_LIMIT_U) / 2)
#define SBUS_MAX   PWM_LIMIT_U

#define RC_YAW 		  SBUS.Data->RX_Channel[0]
#define RC_PITCH    SBUS.Data->RX_Channel[1]
#define RC_THROTTLE SBUS.Data->RX_Channel[2]
#define RC_ROLL     SBUS.Data->RX_Channel[3]
#define RC_AUX1     SBUS.Data->RX_Channel[4]
#define RC_AUX2     SBUS.Data->RX_Channel[5]
#define RC_AUX3     SBUS.Data->RX_Channel[6]
#define RC_AUX4     SBUS.Data->RX_Channel[7]
#define RC_AUX5     SBUS.Data->RX_Channel[8]
#define RC_AUX6     SBUS.Data->RX_Channel[10]
#define RC_AUX7     SBUS.Data->RX_Channel[9]
#define RC_AUX8     SBUS.Data->RX_Channel[11]
#define RC_MID      SBUS_MID
#define RC_RANGE    ((float)((SBUS_MAX - SBUS_MIN) / 2))

typedef enum
{
	Down,
	Mid,
	Up,

}SW_POS;

struct SBUS_Data_
{
	u16 TX_Channel[CHANNEL_COUNT];
	u16 RX_Channel[CHANNEL_COUNT];
};

extern struct SBUS_
{
	u16 State;
	uint32_t LostCnt;
	SBUS_Data_* Data;
	void (*Init)(void);
	void (*Updata)(void);
	SW_POS (*SW_POS_Judge)(u16 AUXN);
}SBUS;
#endif
