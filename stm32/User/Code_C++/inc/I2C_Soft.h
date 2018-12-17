#ifndef __I2C_SOFT_H__
#define __I2C_SOFT_H__
#include "stm32f4xx.h"
class I2C_Soft_
{
	public:
		I2C_Soft_(char I2C_GPIOX,u16 I2C_SCL,u16 I2C_SDA,u16 Delay)
		{
			
			SCL = I2C_SCL;
			SDA = I2C_SDA;
			Delays = Delay;
			switch (I2C_GPIOX)
			{
				case 'A':
					GPIOX = GPIOA;
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);
					break;
				case 'B':
					GPIOX = GPIOB;
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB , ENABLE);
					break;
				case 'C':
					GPIOX = GPIOC;
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC , ENABLE);
					break;
				case 'D':
					GPIOX = GPIOD;
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD , ENABLE);
					break;	
				case 'E':
					GPIOX = GPIOE;
					RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);
					break;
				default:
					break;
			}
		};
		void Init(void);
		int Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_Data);
		int Single_Read(u8 SlaveAddress,u8 REG_Address);
		void Delay(void);
		int Start(void);
		void Stop(void);	
		void Ack(void);
		void NoAck(void);
		int WaitAck(void);
		void SendByte(u8 SendByte);
		u8 ReadByte(void);
	private:
		u16 SCL;
		u16 SDA;
		u16 Delays;
		GPIO_TypeDef* GPIOX;

};

#endif
