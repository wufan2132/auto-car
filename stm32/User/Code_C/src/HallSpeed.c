#include "HallSpeed.h"
void  speed_measure_init(void);
void speed_measure_get(u16 Time);


struct speed_measure_ speed_measure ={
	speed_measure_init,
	speed_measure_get,
	0,
	0,
};

void  speed_measure_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
//	/*********************************************
//	TIM1
//	**********************************************/
//  /* TIM1 clock enable */
//	/* GPIOC clock enable */
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//  
//  /* TIM1 CH1 (PA8), TIM1 CH2 (PA9)*/
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(GPIOA, &GPIO_InitStructure); 
//	
//  /* Time base configuration */
//  TIM_TimeBaseStructure.TIM_Period = MEASURE_RANGE;
//  TIM_TimeBaseStructure.TIM_Prescaler = 0;
//  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
//	
//	TIM_ICStructInit(&TIM_ICInitStructure);
//	//TIM_ICInitStructure.TIM_ICFilter = 10; 
//	TIM_ICInit(TIM1, &TIM_ICInitStructure);

// /* 编码器接口初始化*/
//	TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
//  /* TIM1 enable counter */
//	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
//  TIM_Cmd(TIM1, ENABLE);
//	/*********************************************
//	TIM2
//	**********************************************/	
//	  /* TIM2 clock enable */
//	/* GPIOC clock enable */
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//  
//  /* TIM2 CH1 (PA0), TIM3 CH2 (PA1)*/
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(GPIOA, &GPIO_InitStructure); 
//	
//  /* Time base configuration */
//  TIM_TimeBaseStructure.TIM_Period = MEASURE_RANGE;
//  TIM_TimeBaseStructure.TIM_Prescaler = 0;
//  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//	
//	TIM_ICStructInit(&TIM_ICInitStructure);
//	TIM_ICInit(TIM2, &TIM_ICInitStructure);

// /* 编码器接口初始化*/
//	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
//  /* TIM2 enable counter */
//	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
//  TIM_Cmd(TIM2, ENABLE);
	
	/*********************************************
	TIM3
	**********************************************/
  /* TIM3 clock enable */
	/* GPIOC clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  
  /* TIM3 CH1 (PA6), TIM3 CH2 (PA7)*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8); 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8); 
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = MEASURE_RANGE;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInit(TIM8, &TIM_ICInitStructure);

 /* 编码器接口初始化*/
	TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  /* TIM3 enable counter */
	TIM_ClearFlag(TIM8, TIM_FLAG_Update);
  TIM_Cmd(TIM8, ENABLE);
}
#include "Motor.h"
#define RATE (12.5f/10000.0)

#define FILTER_N 10
//float speed_temp[3][FILTER_N];
//Filter_Average speed1_Filter(FILTER_N,speed_temp[0]);
//Filter_Average speed2_Filter(FILTER_N,speed_temp[1]);
//Filter_Average speed3_Filter(FILTER_N,speed_temp[2]);



//****************************速度采集********************************
//描    述：采集三个编码器速度，数据存放在speed_value中
//入口参数 Time: 定时器时间
//出口参数：无
#define SPEED_K 0.00003419154101275344
void speed_measure_get(u16 Time)
{
	int32_t count = 0;
	int32_t speed = 0;
//	/***************TIM1******************/
//		speed =  TIM_GetCounter(TIM1);
//	if(speed ==0)
//		speed_value.speed1 = speed;
//	else if((TIM1->CR1 & 1<<4) == 0 && speed < SPEED_MAX)
//		speed_value.speed1 = -speed;//正转
//	else if(speed - MEASURE_RANGE -1 > -SPEED_MAX)
//		speed_value.speed1 = -(speed - MEASURE_RANGE -1 );//反转 
//	TIM_SetCounter(TIM1,0); 
//		/***************TIM2******************/
//		speed =  TIM_GetCounter(TIM2);
//	if(speed ==0)
//		speed_value.speed2 = speed;
//	else if((TIM2->CR1 & 1<<4) == 0 && speed < SPEED_MAX)
//		speed_value.speed2 = -speed;//正转
//	else if(speed - MEASURE_RANGE -1 > -SPEED_MAX)
//		speed_value.speed2 = -(speed - MEASURE_RANGE -1 );//反转
//	TIM_SetCounter(TIM2,0); 
		/***************TIM3******************/
	count =  TIM_GetCounter(TIM8);
	if(count ==0)
		speed = count;
	else if((TIM3->CR1 & 1<<4) == 0 && (MEASURE_RANGE - count +1 < SPEED_MAX))
		speed = MEASURE_RANGE - count +1;//正转
	else if(count < SPEED_MAX)
		speed = -count;//反转
	TIM_SetCounter(TIM8,0); 
	speed_measure.Value = speed * SPEED_K *1000.0 /(float)Time;
	speed_measure.distant += speed_measure.Value;
}



