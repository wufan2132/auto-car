#include "NRF24L01.h"

#define CS1   GPIOA->BSRRL = GPIO_Pin_4
#define CS0   GPIOA->BSRRH = GPIO_Pin_4
#define CE1   GPIOC->BSRRL = GPIO_Pin_5
#define CE0   GPIOC->BSRRH = GPIO_Pin_5    

u8 TX_ADDRESS[5] = {0X12,0X34,0X56,0X78,0XA0};  // 定义一个静态发送地址
u8 RX_ADDRESS[5] = {0X12,0X34,0X56,0X78,0XA0};

struct NRF24L01_Data_ NRF24L01_Data;
NRF_State NRF_Mode;
BOOL Is_ACKBUF_IDEL = True;
BOOL Is_TXBUF_IDEL = True;
BOOL Is_RXBUF_IDEL = True;

BOOL NRF24L01_Init(NRF_State Mode);
void NRF24L01_SendData(void);
BOOL NRF24L01_GetData(void);
BOOL NRF24L01_Request_ACKBUF(u8 IsImmediate);
void NRF24L01_Free_RXBUF(void);
//结构体初始化
volatile struct NRF24L01_ NRF24L01 = 
{
	&NRF24L01_Data,
	NRF24L01_Init,
	NRF24L01_SendData,
	NRF24L01_GetData,
	NRF24L01_Request_ACKBUF,
	NRF24L01_Free_RXBUF
};

void NRF24L01_GPIO_Init(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOA, ENABLE);
	
	//CE 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//CS
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	CS1;
	//IRQ 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	//SPI	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  //引脚初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);  //重映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1);
}

void NRF24L01_IRQ_Init(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* IRQ引脚中断线配置 */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource4); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* IRQ引脚优先级配置 */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 15;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void NRF24L01_SPI_Init(void)
{
	SPI_InitTypeDef    SPI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE); 

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //全双工模式
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;   //作为主机使用
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;   //数据长度8
	SPI_InitStructure.SPI_CPOL  = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;   //软件设置NSS功能
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //10M
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1,&SPI_InitStructure);
	SPI_Cmd(SPI1,ENABLE);
}



u8 NRF24L01_SPI_RW(u8 Data)
{
  while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}; 
  SPI_I2S_SendData(SPI1, Data);		
  while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){};
  return SPI_I2S_ReceiveData(SPI1);
}

NRF_State NRF24L01_WriteReg(u8 Reg,u8 Data)
{
 	NRF_State Status;
	
  CS0;				
	Status = (NRF_State)NRF24L01_SPI_RW(Reg);	 
  NRF24L01_SPI_RW(Data);              
	CS1;			

  return(Status);
}

u8 NRF24L01_ReadReg(u8 Reg)
{
 	u8 Data;

 	CS0;				
	NRF24L01_SPI_RW(Reg); 
	Data = NRF24L01_SPI_RW(NOP);            
	CS1;		
 	
	return Data;

}

NRF_State NRF24L01_WriteBuf(u8 Reg,u8 Data[],u8 Length)
{
	NRF_State State;
	
	CS0;
	State = (NRF_State)NRF24L01_SPI_RW(Reg);
	for(u8 i = 0;i<Length;i++)
	{
		NRF24L01_SPI_RW(Data[i]);
	}
	CS1;

	return State;
}

NRF_State NRF24L01_ReadBuf(u8 Reg,u8 Data[],u8 Length)
{
	NRF_State Status;
	u8 i;

	CS0;
	Status = (NRF_State)NRF24L01_SPI_RW(Reg); 
	for(i=0;i<Length;i++)		 
	{	
		Data[i] = NRF24L01_SPI_RW(NOP); //从NRF24L01读取数据 
	}
	CS1;	

	return Status;		
}

BOOL NRF24L01_ConnectCheck(void)
{
	u8 BUF1[5] = {0XC2,0XC2,0XC2,0XC2,0XC2};
	u8 BUF2[5] = {0};
	u8 i = 0;
	
	NRF24L01_WriteBuf(NRF_WRITE_REG + TX_ADDR,BUF1,5);
	NRF24L01_ReadBuf (TX_ADDR,BUF2,5); 
	                
	for(i=0;i<5;i++)
	{
		if(BUF2[i]!=0xC2)
		break;
	} 
	       
	if(i==5)
		return True ;         //MCU与NRF成功连接 
	else
		return False ;        //MCU与NRF不正常连接
}

void NRF24L01_SetRXMode(void)
{
	CE0;	 
	NRF24L01_WriteReg(NRF_WRITE_REG+NRF_CONFIG, 0x0F);   //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
	NRF_Mode = RXMode;
	CE1;
}

void NRF24L01_SetTXMode(void)
{
	CE0;		  
	NRF24L01_WriteReg(NRF_WRITE_REG+NRF_CONFIG,0X0E);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
	NRF_Mode = TXMode;
	CE1;
}

BOOL NRF24L01_Init(NRF_State Mode)
{
	BOOL Mark = False;
	NRF24L01_GPIO_Init();
	NRF24L01_IRQ_Init();
	NRF24L01_SPI_Init();
	CE0;
	u8 State =NRF24L01_ReadReg(STATUS);		                                    //读取status寄存器的值
	NRF24L01_WriteReg(NRF_WRITE_REG+STATUS,State);                            //清除中断标志
	NRF24L01_WriteReg(FLUSH_TX,NOP);   												                //清除TX FIFO寄存器 
	NRF24L01_WriteReg(FLUSH_RX,NOP);                                          //清除RX FIFO寄存器                        
	
	NRF24L01_WriteBuf(NRF_WRITE_REG+TX_ADDR,TX_ADDRESS,5);			//写TX节点地址 
	NRF24L01_WriteBuf(NRF_WRITE_REG+RX_ADDR_P0,TX_ADDRESS,5);  //设置TX节点地址,主要为了使能ACK	 
	NRF24L01_WriteReg(NRF_WRITE_REG+SETUP_AW,0X03);            //设置数据宽度   
	NRF24L01_WriteReg(NRF_WRITE_REG+EN_AA,0X01);               //使能通道0的自动应答    
	NRF24L01_WriteReg(NRF_WRITE_REG+EN_RXADDR,0X01);           //使能通道0的接收地址 
	NRF24L01_WriteReg(NRF_WRITE_REG+NRF_FEATURE , 0X06);                    //使能动态负荷，使能应答反馈数据
	
	if(NRF24L01_ReadReg(NRF_FEATURE) == 0x00 && (NRF24L01_ReadReg(NRF_DYNPD) == 0x00)) 
		NRF24L01_WriteReg(NRF_ACTIVATE, 0x73);                                //避免重复读写
	
	NRF24L01_WriteReg(NRF_WRITE_REG+NRF_FEATURE , 0X06);                    //使能动态负荷，使能应答反馈数据
	NRF24L01_WriteReg(NRF_WRITE_REG+NRF_DYNPD, NRF_DPL_P0);
	NRF24L01_WriteReg(NRF_WRITE_REG+SETUP_RETR,NRF_ARD(4000) | NRF_ARC(2));  //设置自动重发间隔时间:4000us + 86us;最大自动重发次数:2次
	NRF24L01_WriteReg(NRF_WRITE_REG+RF_CH,50);                               //设置RF通道为50
	NRF24L01_WriteReg(NRF_WRITE_REG+RF_SETUP,NRF_PWR_0dBm | NRF_DR_2Mbps);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
	if(Mode == TXMode)
		NRF24L01_WriteReg(NRF_WRITE_REG+NRF_CONFIG,0x0E);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,发送模式,开启所有中断
	else
		NRF24L01_WriteReg(NRF_WRITE_REG+NRF_CONFIG,0x0F);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
	CE1;

	NRF_Mode = Mode;

	return Mark;
}
BOOL NRF24L01_Request_ACKBUF(u8 IsImmediate)
{
	if(IsImmediate == True)                        //立即获取ACK_BUF的使用权
	{
		return True;
	}
	else
	{
		if(Is_ACKBUF_IDEL == True)                  //ACK_BUF是被动发送，且存在中断，避免中断导致数据包混合，因此，必须保证在数据发送出去之前，缓存内容不变
		{
			return True;
		}
		else
			return False;
	}

}
void NRF24L01_SendData(void)
{
	if(NRF_Mode == TXMode)
	{
		if(Is_TXBUF_IDEL == True)           
		{
			CE0;	
			NRF24L01_WriteBuf(WR_TX_PLOAD,NRF24L01_Data.TX_BUF,32);
			CE1;
			Is_TXBUF_IDEL = False;                   //在成功发送出去这包数据之前不接受缓存向寄存器的数据写入
		}
	}
	else
		Is_ACKBUF_IDEL = False;                    //ACK_BUF是被动发送，且存在中断，避免中断导致数据包混合，因此，必须保证在数据发送出去之前，缓存内容不变

}
BOOL NRF24L01_GetData(void)
{
	if(Is_RXBUF_IDEL == False)
	{
		return True;
	}
	else
	{		
		return False;
	}
}

void NRF24L01_Free_RXBUF(void)
{
	Is_RXBUF_IDEL = True;
}

extern "C"{
void EXTI4_IRQHandler(void)
{

	if(EXTI_GetITStatus(EXTI_Line4) != RESET)
  {
		if(NRF_Mode == RXMode)
		{
			CE0;  	
			
			u8 State = NRF24L01_ReadReg(STATUS);		                            //读取status寄存器的值
			NRF24L01_WriteReg(NRF_WRITE_REG+STATUS,State);

			if(State & RX_DR)                                                   //接收到数据
			{
				u8 BUF_TMP[32];
				NRF24L01_ReadBuf(RD_RX_PLOAD,BUF_TMP,32);                         //读取数据   
				NRF24L01_WriteReg(FLUSH_RX,NOP);                                  //清除RX FIFO寄存器
			
				if(Is_RXBUF_IDEL == True)
				{
					for(u8 i = 0;i < 32;i++)
						NRF24L01.Data->RX_BUF[i] = BUF_TMP[i];
					Is_RXBUF_IDEL = False;
				}
				
				if(Is_ACKBUF_IDEL == False)
				{
					NRF24L01_WriteBuf(WR_ACK_PAYLOAD,NRF24L01_Data.ACK_BUF,32);
					Is_ACKBUF_IDEL = True;
				}			
			}                               
		
			CE1;
		}
	 else
		{
			CE0;  
			/*读取动态ACK返回值*/ 
			u8 BUF_TMP[32];
			NRF24L01_ReadBuf(RD_RX_PLOAD,BUF_TMP,32);                         //读取数据   
			NRF24L01_WriteReg(FLUSH_RX,NOP);                                  //清除RX FIFO寄存器	

			if(Is_RXBUF_IDEL == True)
			{
				for(u8 i = 0;i < 32;i++)
					NRF24L01.Data->RX_BUF[i] = BUF_TMP[i];
				Is_RXBUF_IDEL = False;
			}
			
			u8 State = NRF24L01_ReadReg(STATUS);       
			NRF24L01_WriteReg(NRF_WRITE_REG+STATUS,State); 	                  //读取status寄存器的值
			NRF24L01_WriteReg(FLUSH_TX,NOP);   												        //清除TX FIFO寄存器 
			Is_TXBUF_IDEL = True;
			CE1;
		}
	}

	EXTI_ClearITPendingBit(EXTI_Line4);

}

}
