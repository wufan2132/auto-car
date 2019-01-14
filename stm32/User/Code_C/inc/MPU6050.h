#ifndef __MPU6050_H__
#define __MPU6050_H__
#include "stm32f4xx.h"
#include "I2C_Soft.h"
#include "MPU6050_Register.h"
#include "Time.h"
#include "Common.h"
#include "Filter.h"
#define PARA_SVAE_ERROR 2
#define PARA_SVAE_OK    1
#define MESSAGE_NULL    0

#define MPU6050_GYR_250DPS             ((float)0.0076335f)  // 0.0087500 dps/LSB
#define MPU6050_GYR_500DPS             ((float)0.0152671f)  // 0.0175000 dps/LSB
#define MPU6050_GYR_2000DPS            ((float)0.0609756f)  // 0.0700000 dps/LSB

struct MPU6050_Data_
{
	struct Vector ACC_ADC_Original;
	struct Vector GYR_ADC_Original;
	struct Vector ACC_ADC;
	struct Vector GYR_ADC;
	struct Vector ACC_Offset;
	struct Vector GYR_Offset;
};

extern struct MPU6050_
{
	u8 IsCalibrating;            //需要校正
	u8 IsCalibrated;         //是否校正过
	u8 State;
	struct MPU6050_Data_* Data;
	void (*Init)(void);
	void (*Updata)(void);
	
}MPU6050;

#endif
