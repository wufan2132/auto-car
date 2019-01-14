#include "MS5611.h"
#include "Communication.h"

#define MS5611_ADDRESS      0XEE
#define MS5611_RST          0X1E
#define MS5611_D1_OSR_256   0X40
#define MS5611_D1_OSR_512   0X42
#define MS5611_D1_OSR_1024  0X44
#define MS5611_D1_OSR_2048  0X46
#define MS5611_D1_OSR_4096  0X48
#define MS5611_D2_OSR_256   0X50
#define MS5611_D2_OSR_512   0X52
#define MS5611_D2_OSR_1024  0X54
#define MS5611_D2_OSR_2048  0X56
#define MS5611_D2_OSR_4096  0X58
#define MS5611_ADC_RD       0X00
#define MS5611_PROM_RD      0XA0
#define MS5611_PROM_CRC     0XAE

#define MS5611_IDEL         0X00
#define MS5611_TEMP_OK      0X01
#define MS5611_PRESS_OK     0X02
#define MS5611_DELAY        0X05  

I2C_Soft_ I2C_Soft_MS5611('C',GPIO_Pin_2,GPIO_Pin_1,1);
struct MS5611_Data_ MS5611_Data;

int64_t dT,SENS,OFF;
u16 PROM_C[7]; //用于存放PROM中的8组数据;
u32 Press_ORI;
u8 MS5611_State = MS5611_PRESS_OK;


/*
	气压计受温度影响极大，通电后需要一段时间稳定
	由于电路板发热，期间本身发热会导致温度升高
	读取频率保持固定，非常重要！！！

*/
void MS561101_Init(void);
void MS5611_Updata(void);


struct MS5611_ MS5611 = 
{
	&MS5611_Data,
	MS561101_Init,
	MS5611_Updata
};


u8 MS5611_Reset(void)
{
	if(!I2C_Soft_MS5611.Start()) return 0;
	
	I2C_Soft_MS5611.SendByte(MS5611_ADDRESS);
	I2C_Soft_MS5611.WaitAck();
	I2C_Soft_MS5611.SendByte(MS5611_RST);     
	I2C_Soft_MS5611.WaitAck();	 
	I2C_Soft_MS5611.Stop(); 
	
	return 1;
}

//从PROM读取出厂校准数据
void MS5611_PROM_Read(void)
{
	u16 Data1,Data2;
	u8 i;
	for(i = 0;i <= 6;i++)
	{
		I2C_Soft_MS5611.Start();
		I2C_Soft_MS5611.SendByte(MS5611_ADDRESS);
		I2C_Soft_MS5611.WaitAck();
		I2C_Soft_MS5611.SendByte((MS5611_PROM_RD + i * 2));
		I2C_Soft_MS5611.WaitAck();

		I2C_Soft_MS5611.Start();;
		I2C_Soft_MS5611.SendByte(MS5611_ADDRESS + 0x01);
		I2C_Soft_MS5611.WaitAck();
		Data1 = I2C_Soft_MS5611.ReadByte();
		I2C_Soft_MS5611.Ack();
		Data2 = I2C_Soft_MS5611.ReadByte();
		I2C_Soft_MS5611.NoAck();
		I2C_Soft_MS5611.Stop();

		PROM_C[i]=(Data1 << 8) | Data2;
	}
}

void MS5611_Send_Commond(u8 Commond)
{
	I2C_Soft_MS5611.Start();
	I2C_Soft_MS5611.SendByte(MS5611_ADDRESS);
	I2C_Soft_MS5611.WaitAck();
	I2C_Soft_MS5611.SendByte(Commond);	
	I2C_Soft_MS5611.WaitAck();
	I2C_Soft_MS5611.Stop();
}

u32 MS5611_Read_3Byte(void)
{
	u32 Buf1,Buf2,Buf3; 
	
	I2C_Soft_MS5611.Start();
	I2C_Soft_MS5611.SendByte(MS5611_ADDRESS);
	I2C_Soft_MS5611.WaitAck();
	I2C_Soft_MS5611.SendByte(MS5611_ADC_RD);
	I2C_Soft_MS5611.WaitAck();
	I2C_Soft_MS5611.Stop();

	I2C_Soft_MS5611.Start();
	I2C_Soft_MS5611.SendByte(MS5611_ADDRESS+1);
	I2C_Soft_MS5611.WaitAck();
	Buf1 = I2C_Soft_MS5611.ReadByte();
	I2C_Soft_MS5611.Ack();
	Buf2 = I2C_Soft_MS5611.ReadByte();
	I2C_Soft_MS5611.Ack();
	Buf3 = I2C_Soft_MS5611.ReadByte();
	I2C_Soft_MS5611.NoAck();
	I2C_Soft_MS5611.Stop();
	
	return (Buf1 << 16) + (Buf2 << 8) + Buf3;
}

//读取数字温度
BOOL MS5611_GetTemperature(void)
{
	static BOOL IsCommond = False;
	
	if(IsCommond == False) 
	{
		BOOL_REVERSE(IsCommond);
	
		MS5611_Send_Commond(MS5611_D2_OSR_1024);

		return False;
	}
	else
	{

		BOOL_REVERSE(IsCommond);		
		
		dT = MS5611_Read_3Byte();
		
		return True;
	}
}

//读取数字气压
BOOL MS5611_GetPressure(void)
{
	static BOOL IsCommond = False;
	
	if(IsCommond == False) 
	{
		BOOL_REVERSE(IsCommond);
	
		MS5611_Send_Commond(MS5611_D1_OSR_1024);	
		
		return False;
	}
	else
	{
		BOOL_REVERSE(IsCommond);
		
		Press_ORI = MS5611_Read_3Byte();
				
		return True;	
	}	

}

void Timer_Init(u16 MS)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

  TIM_TimeBaseStructure.TIM_Period = 1000 * MS - 1;
  TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t) (SystemCoreClock / 2 / 1000000) - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
  TIM_Cmd(TIM5, ENABLE);

}

void MS561101_Init(void)
{
	I2C_Soft_MS5611.Init();
	MS5611_Reset();
	SystemTime.WaitMS(50);
	MS5611_PROM_Read();
//	SystemTime.WaitMS(50);
//	Timer_Init(10);
	SystemTime.WaitMS(200);
	MS5611_Updata();
	
}
//采样频率25HZ 截止频率 2HZ 
Filter_2nd MS5611_Filter(0.046131802093312926,0.092263604186625852,0.046131802093312926, -1.3072850288493234,0.49181223722257528 );
Filter_2nd MS5611_Speed_Filter(0.046131802093312926,0.092263604186625852,0.046131802093312926, -1.3072850288493234,0.49181223722257528 );

void MS5611_Updata(void)
{
	static int64_t Time_Pre = 0;;
	int64_t T2 = 0;
	int64_t OFF2 = 0;
	int64_t SENS2 = 0;
	
	switch (MS5611_State)
	{
			case MS5611_IDEL:
				if(MS5611_GetTemperature() == True) MS5611_State = MS5611_TEMP_OK;
				break;
			case MS5611_TEMP_OK:
				if(MS5611_GetPressure() == True)  MS5611_State = MS5611_PRESS_OK;
				break;
			default:
				break;
	}
	
	if(MS5611_State != MS5611_PRESS_OK) return;
	
	dT -= ((u32)PROM_C[5] << 8);
	MS5611_Data.Temperature = 2000 + (int32_t)(((int64_t)dT * PROM_C[6]) >> 23);
	OFF  = ((u32)PROM_C[2] << 16) + (((int64_t)PROM_C[4] * dT) >> 7);
	SENS = ((u32)PROM_C[1] << 15) + (((int64_t)PROM_C[3] * dT) >> 8);	

	if(MS5611_Data.Temperature < 2000)
	{

		T2 = (dT * dT) >> 31;				
		int64_t TMP = 5 * powl((int64_t)MS5611_Data.Temperature - 2000,2);

		OFF2  = TMP >> 1;
		SENS2 = TMP >> 2;
		
		if(MS5611_Data.Temperature < -1500)
		{
			int64_t TMP = powl((int64_t)MS5611_Data.Temperature + 1500,2);;
			OFF2 += 7 * TMP;
			SENS2 += 11 * TMP >> 1;
		}
	}	
	MS5611_Data.Temperature -= T2;
	OFF = OFF - OFF2;
	SENS = SENS - SENS2;
	
	MS5611_Data.Pressure = (((Press_ORI * SENS) >> 21) - OFF) >> 15;	
	
	if(MS5611_Data.Pressure < 0) return;
	
	float ALT_TMP = (1 - powf(MS5611_Data.Pressure / 101325.0f, 1.0f / 5.255f)) * 44330.0f;
	ALT_TMP = MS5611_Filter.LPF2ndFilter(ALT_TMP);	
	
	float TimeNow = SystemTime.Now_MS();
	MS5611_Data.Speed = (ALT_TMP - MS5611_Data.Altitude) / (TimeNow - Time_Pre) * (double)1e3;  //m/s
	MS5611_Data.Speed = MS5611_Speed_Filter.LPF2ndFilter(MS5611_Data.Speed);
	MS5611_Data.Altitude = ALT_TMP - MS5611_ALT_OFFECT;//单位 m

	Time_Pre = TimeNow;
	MS5611_State = MS5611_IDEL;
}


//10MS进一次，4次后更新完一次数据  //停用 和MPU6050、HMC5883使用同一iic引脚，中断使数据错误  GYL
//更新频率25HZ
extern "C"{
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update) == SET)
	{
		switch (MS5611_State)
		{
			case MS5611_IDEL:
				if(MS5611_GetTemperature() == True) MS5611_State = MS5611_TEMP_OK;
				break;
			case MS5611_TEMP_OK:
				if(MS5611_GetPressure() == True)  MS5611_State = MS5611_PRESS_OK;
				break;
			default:
				break;
		}
	}
	
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
}
}

