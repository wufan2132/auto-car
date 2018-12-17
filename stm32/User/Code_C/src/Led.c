#include "LED.h"

#define LED_GPIOX GPIOC
#define LED1_RCCX RCC_AHB1Periph_GPIOC

#define LED_NULL_ON 0

uint16_t LED_State = LED_NULL_ON;

void LED_Init(void);
void LED_On(u16 LEDX);
void LED_Off(u16 LEDX);
void LED_Reverse(u16 LEDX,u32 Time);
//函数指针初始化
struct LED_ Led = 
{
	&LED_State,
	LED_Init,
	LED_On,
	LED_Off,
	LED_Reverse
};

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	RCC_AHB1PeriphClockCmd(LED1_RCCX, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = LED1;
	GPIO_Init(LED_GPIOX,&GPIO_InitStructure);

	
	LED_Off(LED1);	
	
}
void LED_On(u16 LEDX)
{
	if((LEDX & LED1) == LED1) 
	{
		GPIO_SetBits(LED_GPIOX,LED1);
		LED_State = LED_State | LED1;                //记录哪些LED 亮灭
	}	
}

void LED_Off(u16 LEDX)
{
	if((LEDX & LED1) == LED1)
	{
		GPIO_ResetBits(LED_GPIOX,LED1);
		LED_State = LED_State & (!LED1);                //记录哪些LED 亮灭
	}
}
void LED_Reverse(u16 LEDX,u32 Time)
{
	static u32 Time1 = 0;
	u32 Time_Now;
	
	Time_Now = SystemTime.Now_MS();
	
	if((LEDX & LED1) == LED1) 
	{
		if(Time_Now > Time1)
		{
			LED_GPIOX->ODR ^= LED1;
			Time1 = Time_Now + Time;
		}
	}
}
