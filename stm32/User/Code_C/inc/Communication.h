#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__
#include "stm32f4xx.h"
#include "Common.h"
#include "USART.h"
#include "Attitude.h"
#include "MPU6050.h"
#include "MS5611.h"
#include "Battery.h"
#include "Motor.h"
#include "GPS_UART.h"
#include "HMC5883.h"
#include "SBUS.h"
#include "Position.h"
#include "Ultra.h"
#include "PWM_Capture.h"
#include "GPS_Parse.h"
#include "CarControl.h"
#include "HallSpeed.h"

#define UNLOCK  	0X0001
#define LOST    	0X0002
#define SYS_ERROR 0X0004
#define POW_LOW 	0X0008
#define POW_LOS 	0X0010
#define MAG_ERROR 0X0020
#define UPS_ON    0X0040
struct SYS_State_
{
	u16 State1;
	u16 State2;
	u16 State3;
};

struct User_Data_
{
	float Data1;
	float Data2;
	float Data3;
	float Data4;
	float Data5;
	float Data6;
	float Data7;
	float Data8;
	float Data9;
	float Data10;
	float Data11;
	float Data12;
};
extern struct User_Data_ User_Data;
extern struct SYS_State_ SYS_State;
extern struct Communication_
{
	BOOL (*UpData)(void);

}Communication;

typedef struct
{
  u8 Head;
  float DataBuf[8];
  u8 End;
}Vcan_Buff_;

#endif
