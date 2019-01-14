#include "USART.h"


USART_::USART_(int USART,u32 Baud,u8* P_RXBUF,u8 *P_TXBUF,int RXBUF_L,int TXBUF_L)
{	
	USARTx = USART3;
	RX_BUF = P_RXBUF;
	TX_BUF = P_TXBUF;
	RX_BUF_Length = RXBUF_L;
	TX_BUF_Length = TXBUF_L;
	
}

void USART_ ::Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	
	
	switch (USARTx)
	{
		case 1:
			
			break;
		case 2:
			
			break;
		case 3:
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
			GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
			GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
			
			//USART3_TX   PB.10
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			//USART3_RX	  PB.11  
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
			GPIO_Init(GPIOB, &GPIO_InitStructure);

			//USART3 NVIC 
			NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;     
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		

			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
			NVIC_Init(&NVIC_InitStructure);	

			USART_InitStructure.USART_BaudRate = Baud;
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;
			USART_InitStructure.USART_StopBits = USART_StopBits_1;
			USART_InitStructure.USART_Parity = USART_Parity_No;
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

			USART_Init(USART3, &USART_InitStructure);

			USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

			USART_Cmd(USART3, ENABLE);  


			break;
		case 4:
			
			break;		
		default:
			break;
	}
	
	
	
	


}
