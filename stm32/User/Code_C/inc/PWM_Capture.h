#ifndef __PWM_CAPTURE_H__
#define __PWM_CAPTURE_H__
#include "stm32f4xx.h"

//原始通道输入
#define PWM_IN_MAX 4000.0
#define PWM_IN_MIN 2000.0
//转换后量度
#define PWM_RC_MAX 1000.0
#define PWM_RC_MIN 0.0
#define PWM_RC_RANGE 1000.0
#define PWM_RC_MID 500.0
#define PWM_RC_DEAD 100.0
//RH3模式切换阈值
#define PWM_RC_CH3_THR 3000
typedef enum
{
	PWM_In_Null,
	PWM_In_Down,
	PWM_In_Mid,
	PWM_In_Up,
}PWM_In_POS;

struct PWM_In_Data_
{
	u16 CH1;
	u16 CH2;
	u16 CH3;
	u16 CH4;
	u16 CH5;
	u16 CH6;
	PWM_In_Data_(){CH1 = 0;CH2 = 0;CH2 = 0;CH3 = 0;CH4 = 0;CH5 = 0;CH6 = 0;}
};

extern struct PWM_In_
{
	struct PWM_In_Data_* Data;
	void (*Init)(u16 RC_MIN_In,u16 RC_MAX_In);
	void (*Updata)(void);
	PWM_In_POS (*POS_Judge)(u16 AUXN);
	u8 Connect_Status;
}PWM_In;

#define PWM_RC_L_R     PWM_In.Data->CH1
#define PWM_RC_F_B     PWM_In.Data->CH2
#define PWM_RC_D_U     PWM_In.Data->CH3
#define PWM_RC_Lr_Rr   PWM_In.Data->CH4
#define PWM_RC_SW5     PWM_In.Data->CH5
#define PWM_RC_R6      PWM_In.Data->CH6

#endif


