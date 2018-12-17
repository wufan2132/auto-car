#include "I2C_Soft.h"
//#define GPIOX	
//#define SCL		GPIO_Pin_6
//#define SDA		GPIO_Pin_5
//#define I2C_RCCX  RCC_AHB1Periph_GPIOE

#define SCL_H         GPIOX->BSRRL = SCL
#define SCL_L         GPIOX->BSRRH = SCL
#define SDA_H         GPIOX->BSRRL = SDA
#define SDA_L         GPIOX->BSRRH = SDA
#define SDA_Read      GPIOX->IDR  & SDA

void I2C_Soft_:: Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin =  SCL;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
  GPIO_Init(GPIOX, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  SDA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOX, &GPIO_InitStructure);	

}

void I2C_Soft_:: Delay(void)
{
	for(u16 i = 0;i < Delays;i++);
}

int I2C_Soft_:: Start(void)
{
	SDA_H;
	SCL_H;
	Delay();
	if(!SDA_Read)return 0;	//SDA线为低电平则总线忙,退出
	SDA_L;
	Delay();
	if(SDA_Read) return 0;	//SDA线为高电平则总线出错,退出
	SDA_L;
	Delay();
	return 1;	
} 

void I2C_Soft_:: Stop(void)
{
	SCL_L;
	Delay();
	SDA_L;
	Delay();
	SCL_H;
	Delay();
	SDA_H;
	Delay();
} 

void I2C_Soft_:: Ack(void)
{	
	SCL_L;
	Delay();
	SDA_L;
	Delay();
	SCL_H;
	Delay();
	SCL_L;
	Delay();
}   

void I2C_Soft_:: NoAck(void)
{	
	SCL_L;
	Delay();
	SDA_H;
	Delay();
	SCL_H;
	Delay();
	SCL_L;
	Delay();
} 

int I2C_Soft_:: WaitAck(void) 	 //返回为:=1有ACK,=0无ACK
{
	SCL_L;
	Delay();
	SDA_H;			
	Delay();
	SCL_H;
	Delay();
	if(SDA_Read)
	{
      SCL_L;
			Delay();
      return 0;
	}
	SCL_L;
	Delay();
	return 1;
}

void I2C_Soft_:: SendByte(u8 SendByte) //数据从高位到低位//
{
	u8 i=8;
	while(i--)
	{
			SCL_L;
			Delay();
		if(SendByte&0x80)
			SDA_H;  
		else 
			SDA_L;   
			SendByte<<=1;
			Delay();
			SCL_H;
			Delay();
	}
	SCL_L;
}

u8 I2C_Soft_:: ReadByte(void)  //数据从高位到低位//
{ 
	u8 i=8;
	u8 ReceiveByte=0;

	SDA_H;				
	while(i--)
	{
		ReceiveByte<<=1;      
		SCL_L;
		Delay();
		SCL_H;
		Delay();	
		if(SDA_Read)
		{
			ReceiveByte|=0x01;
		}
	}
	SCL_L;
	return ReceiveByte;
} 

//单字节写入
int I2C_Soft_:: Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_Data)		
{
	if(!Start())return 0;
	SendByte(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
	if(!WaitAck())
	{
		Stop(); 
		return 0;
	}
	SendByte(REG_Address );   //设置低起始地址      
	WaitAck();	
	SendByte(REG_Data);
	WaitAck();   
	Stop(); 
	return 1;
}

//单字节读取
int I2C_Soft_:: Single_Read(u8 SlaveAddress,u8 REG_Address)
{   
	unsigned char REG_Data;     	
	if(!Start())return 0;
	SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
	if(!WaitAck())
	{
		Stop();
		return 0;
	}
	SendByte((u8) REG_Address);   //设置低起始地址      
	WaitAck();
	Start();
	SendByte(SlaveAddress+1);
	WaitAck();

	REG_Data= ReadByte();
	NoAck();
	Stop();

	return REG_Data;

}	
