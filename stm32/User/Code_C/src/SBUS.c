#include "SBUS.h"

#define SBUS_BUF_SIZE 25
#define CHANNEL_VALUE_MAX 1700
#define CHANNEL_VALUE_MIN 350

#define CHANNEL_VALUE_KP ((float)(SBUS_MAX - SBUS_MIN) / (CHANNEL_VALUE_MAX - CHANNEL_VALUE_MIN))

BOOL Is_SBUS_REC = False;
BOOL SBUS_REC_Mark = False;
u8 SBUS_RX_BUF1[SBUS_BUF_SIZE];
u8 SBUS_RX_BUF2[SBUS_BUF_SIZE];


void SBUS_Init(void);
void SBUS_Updata(void);
SW_POS SW_POS_Judge(u16 AUXN);
struct SBUS_Data_ SBUS_Data;

struct SBUS_ SBUS = 
{
	0,
	0,
	&SBUS_Data,
	SBUS_Init,
	SBUS_Updata,
	SW_POS_Judge
};


struct SBUS_BIT_Pick {
	uint8_t Byte;
	uint8_t R_Shift;
	uint8_t Mask;
	uint8_t L_Shift;
};

//查表进行通道划分

const struct SBUS_BIT_Pick SBUS_Decoder[16][3] = {
	/*  0 */ { { 0, 0, 0xff, 0}, { 1, 0, 0x07, 8}, { 0, 0, 0x00,  0} },
	/*  1 */ { { 1, 3, 0x1f, 0}, { 2, 0, 0x3f, 5}, { 0, 0, 0x00,  0} },
	/*  2 */ { { 2, 6, 0x03, 0}, { 3, 0, 0xff, 2}, { 4, 0, 0x01, 10} },
	/*  3 */ { { 4, 1, 0x7f, 0}, { 5, 0, 0x0f, 7}, { 0, 0, 0x00,  0} },
	/*  4 */ { { 5, 4, 0x0f, 0}, { 6, 0, 0x7f, 4}, { 0, 0, 0x00,  0} },
	/*  5 */ { { 6, 7, 0x01, 0}, { 7, 0, 0xff, 1}, { 8, 0, 0x03,  9} },
	/*  6 */ { { 8, 2, 0x3f, 0}, { 9, 0, 0x1f, 6}, { 0, 0, 0x00,  0} },
	/*  7 */ { { 9, 5, 0x07, 0}, {10, 0, 0xff, 3}, { 0, 0, 0x00,  0} },
	/*  8 */ { {11, 0, 0xff, 0}, {12, 0, 0x07, 8}, { 0, 0, 0x00,  0} },
	/*  9 */ { {12, 3, 0x1f, 0}, {13, 0, 0x3f, 5}, { 0, 0, 0x00,  0} },
	/* 10 */ { {13, 6, 0x03, 0}, {14, 0, 0xff, 2}, {15, 0, 0x01, 10} },
	/* 11 */ { {15, 1, 0x7f, 0}, {16, 0, 0x0f, 7}, { 0, 0, 0x00,  0} },
	/* 12 */ { {16, 4, 0x0f, 0}, {17, 0, 0x7f, 4}, { 0, 0, 0x00,  0} },
	/* 13 */ { {17, 7, 0x01, 0}, {18, 0, 0xff, 1}, {19, 0, 0x03,  9} },
	/* 14 */ { {19, 2, 0x3f, 0}, {20, 0, 0x1f, 6}, { 0, 0, 0x00,  0} },
	/* 15 */ { {20, 5, 0x07, 0}, {21, 0, 0xff, 3}, { 0, 0, 0x00,  0} }
};

void SBUS_Init(void)
{
  USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannel  = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
  USART_InitStructure.USART_BaudRate = 100000;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_2;
  USART_InitStructure.USART_Parity = USART_Parity_Even;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
  USART_Init(USART2,&USART_InitStructure);   
  USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);  
  USART_Cmd(USART2,ENABLE);
	
	for(u8 i = 0;i < CHANNEL_COUNT;i++)
		SBUS_Data.RX_Channel[i] = SBUS_MIN;

}

void SBUS_Receive(void)
{
	if(Is_SBUS_REC == True)
	{	
		u8 Data[SBUS_BUF_SIZE];
		if(SBUS_REC_Mark == True)
		{
			for(u8 i = 0;i < SBUS_BUF_SIZE;i++)
				Data[i] = SBUS_RX_BUF2[i];
		}
		else
		{
			for(u8 i = 0;i < SBUS_BUF_SIZE;i++)
				Data[i] = SBUS_RX_BUF1[i];
		}
		
		Is_SBUS_REC = False;
		
		for (u8 Channel = 0; Channel < CHANNEL_COUNT; Channel++) 
		{
			u32 Value = 0;

			for (u8 Pick = 0; Pick < 3; Pick++) 
			{
				const struct SBUS_BIT_Pick *Decode = &SBUS_Decoder[Channel][Pick];

				if(Decode->Mask != 0) 
				{
					unsigned Piece = Data[1 + Decode->Byte];
					Piece >>= Decode->R_Shift;
					Piece &= Decode->Mask;
					Piece <<= Decode->L_Shift;

					Value |= Piece;
				}
			}
			if(Value > CHANNEL_VALUE_MIN)
			{
				SBUS_Data.RX_Channel[Channel] = (Value - CHANNEL_VALUE_MIN) * CHANNEL_VALUE_KP + SBUS_MIN;
			}
			else
			{
				SBUS_Data.RX_Channel[Channel] = 0;
			}
		}
		
		SBUS.State = (Data[23] << 8) | Data[24];
	}
}

void SBUS_Updata(void)
{
	SBUS_Receive();
}

SW_POS SW_POS_Judge(u16 AUXN)
{
	if(AUXN < 1300) return Up;
	else
		if(AUXN > 1800) return Down;
		else return Mid;
}

extern "C"{
void USART2_IRQHandler(void)
{
	static u32 TimeStore = 0;
	static u8 USART_ReceiveCnt = 0;

	//字节丢失中断，这个中断在开启接收中断时自动开启
	if(USART_GetFlagStatus(USART2,USART_FLAG_ORE) != RESET)  
	{  
		USART_ReceiveData(USART2);   
	}
	
	if(USART_GetFlagStatus(USART2,USART_FLAG_RXNE)==SET)
	{
			u8 TMP = USART_ReceiveData(USART2);
		
			if(SystemTime.Now_MS() - TimeStore > 2)
			{
				USART_ReceiveCnt = 0;
				BOOL_REVERSE(SBUS_REC_Mark);
				Is_SBUS_REC = True;
			}
			if(SBUS_REC_Mark == True)
				SBUS_RX_BUF1[USART_ReceiveCnt++] = TMP;
			else
				SBUS_RX_BUF2[USART_ReceiveCnt++] = TMP;
			
			TimeStore = SystemTime.Now_MS();
			if(USART_ReceiveCnt == SBUS_BUF_SIZE)
			{		
				USART_ReceiveCnt--;
			}
	}
}
}
