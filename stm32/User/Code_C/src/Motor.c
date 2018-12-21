#include "Motor.h"



#define PWM_FREQUENT 62.5f
#define PWM_RANGE   32000 //(uint16_t)((1.0f / PWM_FREQUENT) * 1000 * 1000)  //4000


void Motor_Init(void);
void Motor_Output(BOOL IsHold);
void Motor_Stop(void);
void Motor_Hold(void);
struct PWM_ PWM_Data;

struct Motor_ Motor =
{
	&PWM_Data,
	Motor_Init,
	Motor_Output,
	Motor_Stop,
	Motor_Hold,
};
void Motor_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM2); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_TIM2);  
}

void Motor_TIM_Init(void)
{
 
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;       
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_DeInit(TIM2); 
/* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_RANGE;
  TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t) ((SystemCoreClock /2) / PWM_FREQUENT / PWM_RANGE) - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_LIMIT_D;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC3Init(TIM2, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* TIM2 enable counter */
  TIM_ARRPreloadConfig(TIM2, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_DeInit(TIM3); 
/* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = PWM_RANGE;
  TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t) ((SystemCoreClock /2) / PWM_FREQUENT / PWM_RANGE) - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = PWM_LIMIT_D;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM3, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* TIM3 enable counter */
  TIM_ARRPreloadConfig(TIM3, ENABLE);
  TIM_Cmd(TIM3, ENABLE);
	
	
}
void Motor_Init(void)
{
	Motor_GPIO_Init();
  Motor_TIM_Init();
	Motor_Stop();
}

void Motor_Output(BOOL IsHold)
{
	PWM_ PWM_TMP;

	if(IsHold == True)
	{
		PWM_TMP.PWM1 = Math.Constrain(PWM_Data.PWM1 + PWM_LIMIT_D,PWM_LIMIT_U,PWM_LIMIT_D + THROTTLE_HOLD);
		PWM_TMP.PWM2 = Math.Constrain(PWM_Data.PWM2 + PWM_LIMIT_D,PWM_LIMIT_U,PWM_LIMIT_D + THROTTLE_HOLD);
		PWM_TMP.PWM3 = Math.Constrain(PWM_Data.PWM3 + PWM_LIMIT_D,PWM_LIMIT_U,PWM_LIMIT_D + THROTTLE_HOLD);
		PWM_TMP.PWM4 = Math.Constrain(PWM_Data.PWM4 + PWM_LIMIT_D,PWM_LIMIT_U,PWM_LIMIT_D + THROTTLE_HOLD);
		PWM_TMP.PWM5 = Math.Constrain(PWM_Data.PWM5 + PWM_LIMIT_D,PWM_LIMIT_U,PWM_LIMIT_D + THROTTLE_HOLD);
		PWM_TMP.PWM6 = Math.Constrain(PWM_Data.PWM6 + PWM_LIMIT_D,PWM_LIMIT_U,PWM_LIMIT_D + THROTTLE_HOLD);
	}
	else
	{
		PWM_TMP.PWM1 = Math.Constrain(PWM_Data.PWM1, PWM_LIMIT_U,PWM_LIMIT_D);
		PWM_TMP.PWM2 = Math.Constrain(PWM_Data.PWM2, PWM_LIMIT_U,PWM_LIMIT_D);
		PWM_TMP.PWM3 = Math.Constrain(PWM_Data.PWM3, PWM_LIMIT_U,PWM_LIMIT_D);
		PWM_TMP.PWM4 = Math.Constrain(PWM_Data.PWM4, PWM_LIMIT_U,PWM_LIMIT_D);
		PWM_TMP.PWM5 = Math.Constrain(PWM_Data.PWM5, PWM_LIMIT_U,PWM_LIMIT_D);
		PWM_TMP.PWM6 = Math.Constrain(PWM_Data.PWM6, PWM_LIMIT_U,PWM_LIMIT_D);
	}
	
	TIM_SetCompare3(TIM2,PWM_TMP.PWM1);
	TIM_SetCompare4(TIM3,PWM_TMP.PWM2);
	TIM_SetCompare3(TIM3,PWM_TMP.PWM3);
	TIM_SetCompare2(TIM3,PWM_TMP.PWM4);
	TIM_SetCompare1(TIM3,PWM_TMP.PWM5);
	TIM_SetCompare4(TIM2,PWM_TMP.PWM6);
}

void Motor_Hold(void)
{
	
	TIM_SetCompare3(TIM2,PWM_LIMIT_D + THROTTLE_HOLD);
	TIM_SetCompare4(TIM3,PWM_LIMIT_D + THROTTLE_HOLD);
	TIM_SetCompare3(TIM3,PWM_LIMIT_D + THROTTLE_HOLD);
	TIM_SetCompare2(TIM3,PWM_LIMIT_D + THROTTLE_HOLD);
	TIM_SetCompare1(TIM3,PWM_LIMIT_D + THROTTLE_HOLD);
	TIM_SetCompare4(TIM2,PWM_LIMIT_D + THROTTLE_HOLD);
}

void Motor_Stop(void)
{
	PWM_Data.PWM1 = PWM_LIMIT_M;
	PWM_Data.PWM2 = PWM_LIMIT_M;
	PWM_Data.PWM3 = PWM_LIMIT_M;
	PWM_Data.PWM4 = PWM_LIMIT_M;
	PWM_Data.PWM5 = PWM_LIMIT_M;
	PWM_Data.PWM6 = PWM_LIMIT_M;
	
	TIM_SetCompare3(TIM2,PWM_Data.PWM1);
	TIM_SetCompare4(TIM3,PWM_Data.PWM2);
	TIM_SetCompare3(TIM3,PWM_Data.PWM3);
	TIM_SetCompare2(TIM3,PWM_Data.PWM4);
	TIM_SetCompare1(TIM3,PWM_Data.PWM5);
	TIM_SetCompare4(TIM2,PWM_Data.PWM6);
}

