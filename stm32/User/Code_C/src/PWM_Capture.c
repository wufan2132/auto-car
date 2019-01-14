#include "PWM_Capture.h"
#include "Filter.h"

struct PWM_In_Data_ PWM_In_Data;
struct PWM_In_Data_ RC_CPT_Data;
float PWM_RC_Kp = 0;
u16 Connect_Status_Cnt = 0;//状态计数滤波

void PWM_CPT_Init(u16 RC_MIN_In,u16 RC_MAX_In);
void PWM_CPT_Updata(void);
PWM_In_POS PWM_POS_Judge(u16 AUXN);
struct PWM_In_ PWM_In =
{
	&RC_CPT_Data,
	PWM_CPT_Init,
	PWM_CPT_Updata,
	PWM_POS_Judge,
	0							//连接状态  0连接断开 1连接正常
};

Filter_MidValue Filter_MidValue_CH3;
void PWM_CPT_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //下拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM4); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM4); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8); 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8); 
}

void PWM_CPT_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;     
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_CC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;     
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
}

void PWM_CPT_TIM_Init(void)
{
 
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;       
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_DeInit(TIM4); 
	
  TIM_TimeBaseStructure.TIM_Period = 0XFFFF;     								//自动重装值 
  TIM_TimeBaseStructure.TIM_Prescaler = 41;       							//预分频值, 使TIMx_CLK=1MHz   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  			//输入时钟不分频                     
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //向上计数   
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
                                                       
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //捕捉上升沿
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//捕捉中断
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;       	 //捕捉不分频
	TIM_ICInitStructure.TIM_ICFilter = 0x0;         							 //捕捉输入不滤波
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 ;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2 ;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_3 ;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_4 ;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
  TIM_Cmd(TIM4, ENABLE);
	TIM_ITConfig(TIM4,TIM_IT_CC1, ENABLE);
	TIM_ITConfig(TIM4,TIM_IT_CC2, ENABLE);
  TIM_ITConfig(TIM4,TIM_IT_CC3, ENABLE);
  TIM_ITConfig(TIM4,TIM_IT_CC4, ENABLE);
	
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
//	
//  TIM_DeInit(TIM8); 
//  TIM_TimeBaseStructure.TIM_Period = 0XFFFF;     								//自动重装值 
//  TIM_TimeBaseStructure.TIM_Prescaler = 83;       							//预分频值, 使TIMx_CLK=1MHz   
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  			//输入时钟不分频                     
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //向上计数   
//  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
//                                                       
//	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //捕捉上升沿
//	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//捕捉中断
//	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;       	 //捕捉不分频
//	TIM_ICInitStructure.TIM_ICFilter = 0x0;         							 //捕捉输入不滤波
//	
//  TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
//  TIM_ICInit(TIM8, &TIM_ICInitStructure);
//  TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;        
//  TIM_ICInit(TIM8, &TIM_ICInitStructure);
//	
//  TIM_Cmd(TIM8, ENABLE);
//  TIM_ITConfig(TIM8,TIM_IT_CC3, ENABLE);
//  TIM_ITConfig(TIM8,TIM_IT_CC4, ENABLE);
}

void PWM_CPT_Init(u16 RC_MIN_In,u16 RC_MAX_In)
{
	PWM_CPT_GPIO_Init();
	PWM_CPT_NVIC_Init();
	PWM_CPT_TIM_Init();
	
	PWM_RC_Kp = (float)(PWM_RC_MAX - PWM_RC_MIN)/(float)(PWM_IN_MAX - PWM_IN_MIN);
}

void PWM_CPT_Updata(void)
{
//	if(PWM_In_Data.CH1 >= PWM_IN_MIN)	RC_CPT_Data.CH1 = (PWM_In_Data.CH1 - PWM_IN_MIN) * PWM_RC_Kp + PWM_RC_MIN;
//	else RC_CPT_Data.CH1 = 0;
//	if(PWM_In_Data.CH2 >= PWM_IN_MIN)	RC_CPT_Data.CH2 = (PWM_In_Data.CH2 - PWM_IN_MIN) * PWM_RC_Kp + PWM_RC_MIN;
//	else RC_CPT_Data.CH2 = 0;		
//	if(PWM_In_Data.CH3 >= PWM_IN_MIN)	RC_CPT_Data.CH3 = (PWM_In_Data.CH3 - PWM_IN_MIN) * PWM_RC_Kp + PWM_RC_MIN;
//	else RC_CPT_Data.CH3 = 0;		
//	if(PWM_In_Data.CH4 >= PWM_IN_MIN)	RC_CPT_Data.CH4 = (PWM_In_Data.CH4 - PWM_IN_MIN) * PWM_RC_Kp + PWM_RC_MIN;
//	else RC_CPT_Data.CH4 = 0;		
//	if(PWM_In_Data.CH5 >= PWM_IN_MIN)	RC_CPT_Data.CH5 = (PWM_In_Data.CH5 - PWM_IN_MIN) * PWM_RC_Kp + PWM_RC_MIN;
//	else RC_CPT_Data.CH5 = 0;		
//	if(PWM_In_Data.CH6 >= PWM_IN_MIN)	RC_CPT_Data.CH6 = (PWM_In_Data.CH6 - PWM_IN_MIN) * PWM_RC_Kp + PWM_RC_MIN;
//	else RC_CPT_Data.CH6 = 0;		

//	RC_CPT_Data.CH2 = Filter_MidValue_CH3.MidValue(RC_CPT_Data.CH2);
	
	RC_CPT_Data.CH1 = PWM_In_Data.CH1;
	RC_CPT_Data.CH2 = PWM_In_Data.CH2;
	RC_CPT_Data.CH3 = PWM_In_Data.CH3;
	
	
	//连接状态监测1
	if(Connect_Status_Cnt > 10)
	{
			PWM_In.Connect_Status = 0;
	}
	else
	{
		Connect_Status_Cnt ++;
		PWM_In.Connect_Status = 1;
	}
}

PWM_In_POS PWM_POS_Judge(u16 AUXN)
{
	if(AUXN < PWM_RC_MIN  + 250) return PWM_In_Down;
	else if(AUXN > PWM_RC_MAX - 250) return PWM_In_Up;
	else if(AUXN < PWM_RC_MID + 100 && AUXN > PWM_RC_MID - 100) return PWM_In_Mid;
	else return PWM_In_Null;
}

extern "C"{
void TIM4_IRQHandler(void)
{																					 
	//频率缓冲区计数 
	static u16 CH1_Rising = 0; 
	static u16 CH2_Rising = 0;
	static u16 CH3_Rising = 0; 
	static u16 CH4_Rising = 0;

	if(TIM_GetITStatus(TIM4, TIM_IT_CC1) == SET) 
  {      
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);
		if((GPIOB->IDR & GPIO_Pin_6) == GPIO_Pin_6) 
		{
			CH1_Rising = TIM_GetCapture1(TIM4); 
			TIM4->CCER |=  TIM_CCER_CC1P;               //下降沿触发
		
		}
		else	
		{
			u16 TMP = TIM_GetCapture1(TIM4);
			if(TMP > CH1_Rising)
				PWM_In_Data.CH1 = TMP - CH1_Rising; 
			else
				PWM_In_Data.CH1 = 65535 + TMP - CH1_Rising;
			TIM4->CCER &=  (~TIM_CCER_CC1P);           //上升沿触发
		}
	}
	
	if(TIM_GetITStatus(TIM4, TIM_IT_CC2) == SET) 
  {      
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);
		if((GPIOB->IDR & GPIO_Pin_7) == GPIO_Pin_7) 
		{
			CH2_Rising = TIM_GetCapture2(TIM4); 
			TIM4->CCER |=  TIM_CCER_CC2P;               //下降沿触发
		}
		else	
		{
			u16 TMP = TIM_GetCapture2(TIM4);
			if(TMP > CH2_Rising)
				PWM_In_Data.CH2 = TMP - CH2_Rising; 
			else
				PWM_In_Data.CH2 = 65535 + TMP - CH2_Rising;
			TIM4->CCER &=  (~TIM_CCER_CC2P);           //上升沿触发
		}
	}
	
		if(TIM_GetITStatus(TIM4, TIM_IT_CC3) == SET) 
  {      
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);
		if((GPIOB->IDR & GPIO_Pin_8) == GPIO_Pin_8) 
		{
			CH3_Rising = TIM_GetCapture3(TIM4); 
			TIM4->CCER |=  TIM_CCER_CC3P;               //下降沿触发
			
 			//连接状态监测2
			Connect_Status_Cnt = 0;
		}
		else	
		{
			u16 TMP = TIM_GetCapture3(TIM4);
			if(TMP > CH3_Rising)
				PWM_In_Data.CH3 = TMP - CH3_Rising; 
			else
				PWM_In_Data.CH3 = 65535 + TMP - CH3_Rising;
			TIM4->CCER &=  (~TIM_CCER_CC3P);           //上升沿触发
		}
	}
	
		if(TIM_GetITStatus(TIM4, TIM_IT_CC4) == SET) 
  {      
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);
		if((GPIOB->IDR & GPIO_Pin_9) == GPIO_Pin_9) 
		{
			CH4_Rising = TIM_GetCapture4(TIM4); 
			TIM4->CCER |=  TIM_CCER_CC4P;               //下降沿触发
		}
		else	
		{
			u16 TMP = TIM_GetCapture4(TIM4);
			if(TMP > CH4_Rising)
				PWM_In_Data.CH4 = TMP - CH4_Rising; 
			else
				PWM_In_Data.CH4 = 65535 + TMP - CH4_Rising;
			TIM4->CCER &=  (~TIM_CCER_CC4P);           //上升沿触发
		}
	}
}	

//void TIM8_CC_IRQHandler(void)
//{																					 
//	//频率缓冲区计数 
//	static u16 CH3_Rising = 0; 
//	static u16 CH4_Rising = 0;

//	if(TIM_GetITStatus(TIM8, TIM_IT_CC3) == SET) 
//  {      
//		TIM_ClearITPendingBit(TIM8, TIM_IT_CC3);
//		if((GPIOC->IDR & GPIO_Pin_8) == GPIO_Pin_8) 
//		{
//			CH3_Rising = TIM_GetCapture3(TIM8); 
//			TIM8->CCER |=  TIM_CCER_CC3P;               //下降沿触发
//		}
//		else	
//		{
//			u16 TMP = TIM_GetCapture3(TIM8);
//			if(TMP > CH3_Rising)
//				PWM_In_Data.CH1 = TMP - CH3_Rising; 
//			else
//				PWM_In_Data.CH1 = 65535 + TMP - CH3_Rising;
//			
//			TIM8->CCER &=  (~TIM_CCER_CC3P);           //上升沿触发
//		}
//	}
//	
//		if(TIM_GetITStatus(TIM8, TIM_IT_CC4) == SET) 
//  {      
//		TIM_ClearITPendingBit(TIM8, TIM_IT_CC4);
//		if((GPIOC->IDR & GPIO_Pin_9) == GPIO_Pin_9) 
//		{
//			CH4_Rising = TIM_GetCapture4(TIM8); 
//			TIM8->CCER |=  TIM_CCER_CC4P;               //下降沿触发
//		}
//		else	
//		{
//			u16 TMP = TIM_GetCapture4(TIM8);
//			if(TMP > CH4_Rising)
//				PWM_In_Data.CH2 = TMP - CH4_Rising; 
//			else
//				PWM_In_Data.CH2 = 65535 + TMP - CH4_Rising;
//			
//			TIM8->CCER &=  (~TIM_CCER_CC4P);           //上升沿触发
//		}
//	}

//}

}



