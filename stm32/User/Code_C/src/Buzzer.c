#include "Buzzer.h"

#define Buzzer_GPIOX GPIOC
#define Buzzer_RCCX RCC_AHB1Periph_GPIOC
#define Buzzer_PORT GPIO_Pin_12
void Buzzer_Init(void);
void Buzzer_On(u16 Time);
void Buzzer_Off(void);
struct Buzzer_ Buzzer = 
{
	Buzzer_Init,
	Buzzer_On,
	Buzzer_Off
};

void Buzzer_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	RCC_AHB1PeriphClockCmd(Buzzer_RCCX, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = Buzzer_PORT;
	GPIO_Init(Buzzer_GPIOX,&GPIO_InitStructure);
	GPIO_ResetBits(Buzzer_GPIOX,Buzzer_PORT);

}

void Buzzer_On(u16 Time)
{
	static u32 Time1 = 0;
	u32 Time_Now;
	
	Time_Now = SystemTime.Now_MS();
	if(Time_Now > Time1)
	{
		Buzzer_GPIOX->ODR ^= Buzzer_PORT;
		Time1 = Time_Now + Time;
	}
}

void Buzzer_Off(void)
{
	GPIO_ResetBits(Buzzer_GPIOX,Buzzer_PORT);
}
