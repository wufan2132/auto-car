#include "Battery.h"

void ADC_Init(void);
void ADC_Updata(void);
u16 ADC_Value[1];

struct Power_VOL_Data_ Power_VOL_Data;
struct Power_ Power = 
{
	&Power_VOL_Data,
	ADC_Init,
	ADC_Updata
};

void ADC_GOIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

}
void ADC_DMA_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC_Value;   //目标数据位
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_BASE+0x4C;  //ADC->DR地址
	DMA_InitStructure.DMA_PeripheralBurst =DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_Init(DMA2_Stream0,&DMA_InitStructure);
	DMA_Cmd(DMA2_Stream0,ENABLE);
}
void ADC_Init(void)
{

	ADC_InitTypeDef ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	ADC_GOIO_Init();
	ADC_DMA_Init();
	
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; 
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;     //独立采样
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;  //速度尽可能低
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	//ADC1配置
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_NbrOfConversion = 1;  //通道数
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_Init(ADC1,&ADC_InitStructure);
		
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,1,ADC_SampleTime_112Cycles);
	ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE); //源数据变化时开启DMA传输
	ADC_DMACmd(ADC1,ENABLE);//使能ADC的DMA传输
	ADC_Cmd(ADC1,ENABLE);
	ADC_SoftwareStartConv(ADC1);
}

void ADC_Updata(void)
{
	Power_VOL_Data.BAT_3S = ADC_Value[0] / 4095.0f * 3.3f * 4.0f;

//	switch (Mark % 3)
//	{
//		case 0:
//			BatValue = ADS1118.Updata(0);
//			if(BatValue != -1)
//			{
//				Power_VOL_Data.POW_5V = BatValue;
//				Mark++;
//			}
//			break;
//		case 1:
//			BatValue = ADS1118.Updata(1);
//			if(BatValue != -1)
//			{
//				Power_VOL_Data.POW_4V5 = BatValue;
//				Mark++;
//			}				
//			break;
//		case 2:
//			BatValue = ADS1118.Updata(2);
//			if(BatValue != -1)
//			{
//				Power_VOL_Data.BAT_12S = BatValue;
//				Mark++;
//			}	
//			break;
//		default:
//			break;
//	}
//		
//	if((GPIOE->IDR & GPIO_Pin_15) == GPIO_Pin_15) Power_VOL_Data.IsUPS_On = True;
//	else Power_VOL_Data.IsUPS_On = False;
}
