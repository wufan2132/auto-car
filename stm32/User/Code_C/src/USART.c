#include "USART.h"

#define USART1_BUF_SIZE 255
u8 USART1_TX_BUF[USART1_BUF_SIZE];
u8 USART1_RX_BUF[USART1_BUF_SIZE];

Queue_ USART1_QueueSend;
Queue_ USART1_QueueRecv;

void usart1_init(u32 bound);
BOOL usart1_send(u8 *data, u16 num);
BOOL usart1_receive(u8 *data, u16 num);
struct usart_ usart1= {  
	usart1_init,                                                                                                                                         
	usart1_send,
	usart1_receive,
};


void usart1_init(u32 Bound)
{
	//GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	//USART1_TX   PA.9
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	//USART1_RX	  PA.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	//USART1 NVIC 
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;     
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	

	USART_InitStructure.USART_BaudRate = Bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);
 
	USART1_QueueSend = Queue_OPS.Init(USART1_BUF_SIZE,USART1_TX_BUF);
	USART1_QueueRecv = Queue_OPS.Init(USART1_BUF_SIZE,USART1_RX_BUF);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);      
	USART_Cmd(USART1, ENABLE);

}
/**************************************************************
	串口1中断
**************************************************************/
extern "C"{
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 temp;
  //send 
  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET){   
		if(True == Queue_OPS.Dequeue(&temp,&USART1_QueueSend))
			USART_SendData(USART1, temp); 
		else
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);   
  }
	
		//receive 缓冲满不接受数据
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){    
		
		temp = USART_ReceiveData(USART1);
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		
		if(False == Queue_OPS.Enqueue(temp,&USART1_QueueRecv))
		{}
  }
} 
}

/**************************************************************
	串口1发送
**************************************************************/
BOOL usart1_send(u8 *data, u16 num)
{
	u16 i = 0;
	if(num > USART1_QueueSend.Size - USART1_QueueSend.Length)
		return False;
	for(i = 0;i < num;i++){
		if(False == Queue_OPS.Enqueue(data[i],&USART1_QueueSend)){
			return False;
		}		
	}
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	return  True;
}
/**************************************************************
	串口1接收
**************************************************************/
BOOL usart1_receive(u8 *data, u16 num)
{
	u16 i = 0;
	if(num > USART1_QueueRecv.Length)
		return False;
	for(i = 0;i < num;i++){
		if(False == Queue_OPS.Dequeue(&data[i],&USART1_QueueRecv)){
			return False;
		}
	}
	return True;	
}

	

