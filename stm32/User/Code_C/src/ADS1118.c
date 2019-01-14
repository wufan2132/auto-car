#include "ADS1118.h"


#define CS1   GPIOB->BSRRL = GPIO_Pin_3
#define CS0   GPIOB->BSRRH = GPIO_Pin_3

ADS_InitTypeDef ADS_InitStructure;

void ADS1118_Init(void);
float ADS1118_Updata(u8 Channel);

struct ADS1118_ ADS1118 = 
{
	ADS1118_Init,
	ADS1118_Updata
};


void ADS1118_GPIO_Init(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOB, ENABLE);
	
	//CS
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	CS1;
	//SPI3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  //引脚初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_SPI3);  //重映射
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_SPI3);
}


void ADS1118_SPI_Init(void)
{
	SPI_InitTypeDef    SPI_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3,ENABLE); 

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //全双工模式
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;   //作为主机使用
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;   //数据长度8
	SPI_InitStructure.SPI_CPOL  = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;   //软件设置NSS功能
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; //10M
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI3,&SPI_InitStructure);
	SPI_Cmd(SPI3,ENABLE);
}

u8 ADS1118_SPI_RW(u8 Data)
{
  while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET){}; 
  SPI_I2S_SendData(SPI3, Data);		
  while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET){};
  return SPI_I2S_ReceiveData(SPI3);
}

u32 ADS1118_RW_REG(u16 CofigReg)
{
	u32 Data[4];
	CS0;
	Data[0] = ADS1118_SPI_RW((u8)(CofigReg >> 8));
	Data[1] = ADS1118_SPI_RW((u8)CofigReg);	
	Data[2] = ADS1118_SPI_RW((u8)(CofigReg >> 8));
	Data[3] = ADS1118_SPI_RW((u8)CofigReg);	
	CS1;
	return Data[3] | (Data[2] << 8) | (Data[2] << 16) | (Data[0] << 24);
}

u32 ADS1118_Read_Data(u16 CofigReg)
{
	u16 Data[4];
	CS0;
	Data[0] = ADS1118_SPI_RW((u8)(CofigReg >> 8));
	Data[1] = ADS1118_SPI_RW((u8)CofigReg);	
	CS1;
	return Data[1] | (Data[0] << 8);
}
void ADS1118_Init(void)
{
	ADS1118_GPIO_Init();
	ADS1118_SPI_Init();
	
	ADS_InitStructure.stru.OS = SINGLE_CONVER;
	ADS_InitStructure.stru.MUX= AINPN_0_GND;
	ADS_InitStructure.stru.PGA= PGA_2048;
	ADS_InitStructure.stru.MODE = CONTIOUS;
	ADS_InitStructure.stru.DR = DR_128_SPS;
	ADS_InitStructure.stru.TS = ADC_MODE; //ad mode
	ADS_InitStructure.stru.PULLUP = PULL_UP_DIS;
	ADS_InitStructure.stru.NOP_ = DATA_VALID;
	ADS_InitStructure.stru.RDY = DATA_NREADY;
	ADS1118_RW_REG(ADS_InitStructure.word); 
}
float ADS1118_Updata(u8 Channel)
{
	float Value = 0;
	static u8 Cnt = 0;
	if(Cnt++ %5 != 0) return -1;
	switch (Channel)
	{
		case 0:
			if(ADS_InitStructure.stru.MUX != AINPN_0_GND)
			{
				ADS_InitStructure.stru.MUX= AINPN_0_GND;
				ADS1118_Read_Data(ADS_InitStructure.word);
				return -1;
			}
			Value = (float)ADS1118_Read_Data(ADS_InitStructure.word) / 32768 * 2.048f * 4.3f;
			break;
		case 1:
			if(ADS_InitStructure.stru.MUX != AINPN_1_GND)
			{
				ADS_InitStructure.stru.MUX= AINPN_1_GND;
				ADS1118_Read_Data(ADS_InitStructure.word);
				return -1;
			}
			Value = (float)ADS1118_Read_Data(ADS_InitStructure.word) / 32768 * 2.048f * 4.3f;
			break;
		case 2:
			if(ADS_InitStructure.stru.MUX != AINPN_2_GND)
			{
				ADS_InitStructure.stru.MUX= AINPN_2_GND;
				ADS1118_Read_Data(ADS_InitStructure.word);
				return -1;
			}
			Value = (float)ADS1118_Read_Data(ADS_InitStructure.word) / 32768 * 2.048f * 28;	
			break;
		default:
			break;
	}
	return Value;		
}
