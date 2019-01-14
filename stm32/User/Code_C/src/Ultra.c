#include "Ultra.h"

#define ULTRA_ADDRESS 0xE8
#define ULTRA_REG0 0x00
#define ULTRA_REG1 0x01
#define ULTRA_REG2 0x02
#define ULTRA_REG3 0x03

#define ULTRA_MEASURE_NT_MM 0xB0
#define ULTRA_MEASURE_NT_US 0xB2
#define ULTRA_MEASURE_T_MM  0xB4
#define ULTRA_MEASURE_T_MM_10 0xBC

#define READ_TIME 1000
#define READ_SCL GPIOB->IDR & GPIO_Pin_13


void Ultra_Init(void);
void Ultra_Updata(void);

I2C_Soft_ I2C_Soft_Ultra('B',GPIO_Pin_13,GPIO_Pin_12,1000);//delays值影响测量数据

Filter_MidValue Ultra_Filter;

struct Ultra_ Ultra = 
{
	0,
	0,
	Ultra_Init,
	Ultra_Updata
};

void Ultra_Init(void)
{
		I2C_Soft_Ultra.Init();             
}

void Ultra_Updata(void)
{
	static char Detect_Flag = 0;
	static uint64_t Time_Detect1 = 0;
	static uint64_t Time_Detect2 = 0;
	uint64_t Time_Enter = 0;
	u8 RX_BUF[2];
	Time_Enter= SystemTime.Now_US();
	
	if(Detect_Flag == 0)
	{
		I2C_Soft_Ultra.Single_Write(ULTRA_ADDRESS,ULTRA_REG2,ULTRA_MEASURE_NT_MM);
		Time_Detect1 = Time_Enter;
		Detect_Flag = 1;
	}
	
	if((Time_Enter - Time_Detect1) > READ_TIME && READ_SCL)
	{
			RX_BUF[0] = I2C_Soft_Ultra.Single_Read(ULTRA_ADDRESS,ULTRA_REG2);
			RX_BUF[1] = I2C_Soft_Ultra.Single_Read(ULTRA_ADDRESS,ULTRA_REG3);
			Ultra.Altitude = (((int)RX_BUF[0] << 8) + RX_BUF[1]) / 1000.0f;
			Detect_Flag = 0;
		
			float ALT_TMP = Ultra_Filter.MidValue(Ultra.Altitude);
			
			Ultra.Speed = (Ultra.Altitude - ALT_TMP) / (Time_Enter - Time_Detect2) * (double)1e6;
			Ultra.Altitude = ALT_TMP;
			
			Time_Detect2 = Time_Enter;
	}
}


