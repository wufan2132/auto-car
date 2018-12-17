#include "SDCard.h"


u8  SD_Type=0;
SPI_InitTypeDef  SPI_InitStructure;
void SPI_SD_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能 GPIOB 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);// 使能 SPI1 时钟
	
	//CS
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	
	//GPIOFB3,4,5 初始化设置: 复用功能输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//PB3~5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);// 初始化
	//配置引脚复用映射
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1); //PB3 复用为 SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1); //PB4 复用为 SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1); //PB5 复用为 SPI1
	//这里只针对 SPI 口初始化
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,ENABLE);//复位 SPI1
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);//停止复位 SPI1
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //设置 SPI 全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //设置 SPI 工作模式:主 SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;  //设置 SPI 的数据大小: 8 位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;//串行同步时钟的空闲状态为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //数据捕获于第二个时钟沿
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //NSS 信号由硬件管理
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;  //预分频 256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //数据传输从 MSB 位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;  //CRC 值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure); //根据指定的参数初始化外设 SPIx 寄存器
	
	SPI_Cmd(SPI1, ENABLE); //使能 SPI1

}

/*******************************************************************************
* Function Name  : SPI_ReadWriteByte
* Description    : SPI读写一个字节（发送完成后返回本次通讯读取的数据）
* Input          : u8 TxData 待发送的数
* Output         : None
* Return         : u8 RxData 收到的数
*******************************************************************************/
u8 SPI_ReadWriteByte(u8 TxData)
{
	while((SPI1->SR&SPI_I2S_FLAG_TXE)==RESET);		//等待发送区空	  
	SPI1->DR = TxData;	 	                        //发送一个byte   
	while((SPI1->SR&SPI_I2S_FLAG_RXNE)==RESET){};   //等待接收完一个byte  
	return SPI1->DR;          	                  //返回收到的数据			
} 


/*******************************************************************************
* Function Name  : SPI_SetSpeed
* Description    : SPI设置速度为高速
* Input          : u8 SpeedSet 
*                  如果速度设置输入0，则低速模式，非0则高速模式
*                  SPI_SPEED_HIGH   1
*                  SPI_SPEED_LOW    0
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_SetSpeed(u8 SpeedSet)
{
	if(SpeedSet == SPI_SPEED_LOW)
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;	
	else
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;	
	
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE); //使能SPI外设
}
/*******************************************************************************
* Function Name  : SD_WaitReady
* Description    : 等待SD卡Ready
* Input          : None
* Output         : None
* Return         : u8 
*                   0： 成功
*                   other：失败
*******************************************************************************/
u8 SD_WaitReady(void)
{
	u8 Ret;
	u16 Retry = 0;
	do
	{
		Ret = SPI_ReadWriteByte(0xFF);
		if(Retry++ == 0XFFFE) return 1;

	}while(Ret != 0xFF);

	return 0;
}



/*******************************************************************************
* Function Name  : SD_SendCommand
* Description    : 向SD卡发送一个命令
* Input          : u8 cmd   命令 
*                  u32 arg  命令参数
*                  u8 crc   crc校验值
* Output         : None
* Return         : u8 r1 SD卡返回的响应
*******************************************************************************/
u8 SD_SendCommand(u8 cmd, u32 arg, u8 crc)
{
	u8 Ret;
	u8 Retry = 0;

	SPI_ReadWriteByte(0xff);
	//片选端置低，选中SD卡
	SD_CS_ENABLE();

	SPI_ReadWriteByte(cmd | 0x40);                         
	SPI_ReadWriteByte(arg >> 24);
	SPI_ReadWriteByte(arg >> 16);
	SPI_ReadWriteByte(arg >> 8);
	SPI_ReadWriteByte(arg);
	SPI_ReadWriteByte(crc);
	
	//等待响应，或超时退出
	while((Ret = SPI_ReadWriteByte(0xFF)) == 0xFF)
	{
			Retry++;
			if(Retry > 200) break;
	}
 
	//关闭片选
	SD_CS_DISABLE();
	//在总线上额外增加8个时钟，让SD卡完成剩下的工作
	SPI_ReadWriteByte(0xFF);

	//返回状态值
	return Ret;
}


/*******************************************************************************
* Function Name  : SD_SendCommand_NoDeassert
* Description    : 向SD卡发送一个命令(结束是不失能片选，还有后续数据传来）
* Input          : u8 cmd   命令 
*                  u32 arg  命令参数
*                  u8 crc   crc校验值
* Output         : None
* Return         : u8 r1 SD卡返回的响应
*******************************************************************************/
u8 SD_SendCommand_NoDeassert(u8 cmd, u32 arg, u8 crc)
{
	u8 Ret;
	u8 Retry = 0;

	SPI_ReadWriteByte(0xff);
	//片选端置低，选中SD卡
	SD_CS_ENABLE();

	//发送
	SPI_ReadWriteByte(cmd | 0x40);                         //分别写入命令
	SPI_ReadWriteByte(arg >> 24);
	SPI_ReadWriteByte(arg >> 16);
	SPI_ReadWriteByte(arg >> 8);
	SPI_ReadWriteByte(arg);
	SPI_ReadWriteByte(crc);

	//等待响应，或超时退出
	while((Ret = SPI_ReadWriteByte(0xFF)) == 0xFF)
	{
			Retry++;
			if(Retry > 200) break;
	}
	//返回响应值
	return Ret;
}

/*******************************************************************************
* Function Name  : SD_Init
* Description    : 初始化SD卡
* Input          : None
* Output         : None
* Return         : u8 
*                  0：NO_ERR
*                  1：TIME_OUT
*                  99：NO_CARD
*******************************************************************************/
u8 SD_Init(void)
{
	u16 i;      
	u8 Ret;      
	u16 Retry;  
	u8 Buff[6];
	
	SPI_SD_Init();
	
	if(!SD_DET()) return STA_NODISK;  //FatFS错误标志：没有插入磁盘    
	SD_PWR_ON();                      //SD卡上电  
	for(i=0;i<0xf00;i++);             //延时，等待SD卡上电完成   
	for(i=0;i<10;i++)                 //先产生>74个脉冲，让SD卡自己初始化完成
	{
			SPI_ReadWriteByte(0xFF);
	}

	Retry = 0;
	do
	{      
			Ret = SD_SendCommand(CMD0, 0, 0x95); //发送CMD0，让SD卡进入IDLE状态
			Retry++;
	}while((Ret != 0x01) && (Retry < 200));

	Ret = SD_SendCommand_NoDeassert(8, 0x1aa, 0x87); //获取卡片的SD版本信息 
	if(Ret == 0x05)                                 //如果卡片版本信息是v1.0版本的
	{
			
		SD_Type = SD_TYPE_V1;                       //设置卡类型为SDV1.0，如果后面检测到为MMC卡，再修改为MMC  
		SD_CS_DISABLE();                            //如果是V1.0卡，CMD8指令后没有后续数据
		SPI_ReadWriteByte(0xFF);                    //多发8个CLK，让SD结束后续操作

		//-----------------SD卡、MMC卡初始化开始-----------------
		//发卡初始化指令CMD55+ACMD41
		//如果有应答，说明是SD卡，且初始化完成
		//没有回应，说明是MMC卡，额外进行相应初始化
		Retry = 0;
		do
		{       
				Ret = SD_SendCommand(CMD55, 0, 0);    //先发CMD55，应返回0x01；否则出错
				if(Ret != 0x01)  return Ret;           
				Ret = SD_SendCommand(ACMD41, 0, 0);   //得到正确响应后，发ACMD41，应得到返回值0x00，否则重试200次
				Retry++;
		}while((Ret!= 0x00) && (Retry < 400));
		if(Retry == 400)
		{
				Retry = 0;
				do
				{
						Ret = SD_SendCommand(1, 0, 0);
						Retry++;
				}while((Ret != 0x00)&&(Retry < 400)); //发送MMC卡初始化命令（没有测试）
				if(Retry == 400)  return 1;           //MMC卡初始化超时
				SD_Type = SD_TYPE_MMC;
		}
					 
		SPI_SetSpeed(SPI_SPEED_HIGH);                     
		SPI_ReadWriteByte(0xFF);
		
		Ret = SD_SendCommand(CMD16, 512, 0xff);   //设置Sector Size
		if(Ret != 0x00) return Ret;
	}
	//下面是V2.0卡的初始化
	//其中需要读取OCR数据，判断是SD2.0还是SD2.0HC卡
	else 
	{
		if(Ret == 0x01)
		{
			//V2.0的卡，CMD8命令后会传回4字节的数据，要跳过再结束本命令
			Buff[0] = SPI_ReadWriteByte(0xFF);  //should be 0x00
			Buff[1] = SPI_ReadWriteByte(0xFF);  //should be 0x00
			Buff[2] = SPI_ReadWriteByte(0xFF);  //should be 0x01
			Buff[3] = SPI_ReadWriteByte(0xFF);  //should be 0xAA
	 
			SD_CS_DISABLE();
			//the next 8 clocks
			SPI_ReadWriteByte(0xFF);
			
			//判断该卡是否支持2.7V-3.6V的电压范围
			if(Buff[2]==0x01 && Buff[3]==0xAA)
			{      
				Retry = 0;  //支持电压范围，可以操作
				do
				{
					Ret = SD_SendCommand(CMD55, 0, 0);
					if(Ret != 0x01) return Ret;
					Ret = SD_SendCommand(ACMD41, 0x40000000, 0);
					if(Retry++ > 200)  return Ret;  //超时则返回r1状态
				}while(Ret != 0);                 //发卡初始化指令CMD55+ACMD41
				
					//初始化指令发送完成，接下来获取OCR信息
					//-----------鉴别SD2.0卡版本开始-----------
					Ret = SD_SendCommand_NoDeassert(CMD58, 0, 0);
					if(Ret!=0x00)
					{
							return Ret;  //如果命令没有返回正确应答，直接退出，返回应答
					}
					//读OCR指令发出后，紧接着是4字节的OCR信息
					Buff[0] = SPI_ReadWriteByte(0xFF);
					Buff[1] = SPI_ReadWriteByte(0xFF); 
					Buff[2] = SPI_ReadWriteByte(0xFF);
					Buff[3] = SPI_ReadWriteByte(0xFF);

					//OCR接收完成，片选置高
					SD_CS_DISABLE();
					SPI_ReadWriteByte(0xFF);

					//检查接收到的OCR中的bit30位（CCS），确定其为SD2.0还是SDHC
					//如果CCS=1：SDHC   CCS=0：SD2.0
					if(Buff[0] & 0x40)    //检查CCS
					{
							SD_Type = SD_TYPE_V2HC;
					}
					else
					{
							SD_Type = SD_TYPE_V2;
					}      
					//设置SPI为高速模式
					SPI_SetSpeed(SPI_SPEED_HIGH);  
			}
    }
	}
  return Ret;
}



/*******************************************************************************
* Function Name  : SD_ReceiveData
* Description    : 从SD卡中读回指定长度的数据，放置在给定位置
* Input          : u8 *Data(存放读回数据的内存>len)
*                  u16 len(数据长度）
*                  u8 Release(传输完成后是否释放总线CS置高 0：不释放 1：释放）
* Output         : None
* Return         : u8 
*                  0：NO_ERR
*                  other：错误信息
*******************************************************************************/
u8 SD_ReceiveData(u8 *Data, u16 Len, u8 Release)
{
	u16 Retry;
	u8 Ret;

	// 启动一次传输
	SD_CS_ENABLE();
	//等待SD卡发回数据起始令牌0xFE
	Retry = 0;
	do
	{
		Ret = SPI_ReadWriteByte(0xFF);
		Retry++;
		if(Retry > 2000)  //2000次等待后没有应答，退出报错
		{
			SD_CS_DISABLE();
			return 1;
		}
	}while(Ret != 0xFE);
	//开始接收数据
	while(Len--)
	{
		*Data = SPI_ReadWriteByte(0xFF);
		Data++;
	}
	//下面是2个伪CRC（dummy CRC）
	SPI_ReadWriteByte(0xFF);
	SPI_ReadWriteByte(0xFF);
	//按需释放总线，将CS置高
	if(Release == RELEASE)
	{
		//传输结束
		SD_CS_DISABLE();
		SPI_ReadWriteByte(0xFF);
	}

	return 0;
}


/*******************************************************************************
* Function Name  : SD_GetCID
* Description    : 获取SD卡的CID信息，包括制造商信息
* Input          : u8 *cid_Data(存放CID的内存，至少16Byte）
* Output         : None
* Return         : u8 
*                  0：NO_ERR
*                  1：TIME_OUT
*                  other：错误信息
*******************************************************************************/
u8 SD_GetCID(u8 *Cid_Data)
{
	u8 Ret;

	//发CMD10命令，读CID
	Ret = SD_SendCommand(CMD10, 0, 0xFF);
	if(Ret != 0x00) return Ret;
	//接收16个字节的数据
	SD_ReceiveData(Cid_Data, 16, RELEASE);
	return 0;
}


/*******************************************************************************
* Function Name  : SD_GetCSD
* Description    : 获取SD卡的CSD信息，包括容量和速度信息
* Input          : u8 *cid_Data(存放CID的内存，至少16Byte）
* Output         : None
* Return         : u8 
*                  0：NO_ERR
*                  1：TIME_OUT
*                  other：错误信息
*******************************************************************************/
u8 SD_GetCSD(u8 *Csd_Data)
{
	u8 Ret;

	//发CMD9命令，读CSD
	Ret = SD_SendCommand(CMD9, 0, 0xFF);
	if(Ret != 0x00) return Ret;
	//接收16个字节的数据
	SD_ReceiveData(Csd_Data, 16, RELEASE);
	return 0;
}


/*******************************************************************************
* Function Name  : SD_GetCapacity
* Description    : 获取SD卡的容量
* Input          : None
* Output         : None
* Return         : u32 capacity 
*                   0： 取容量出错 
*******************************************************************************/
u32 SD_GetCapacity(void)
{
	u8 Csd[16];
	u32 Capacity;
	u8 Ret;
	u16 i;
	u16 Temp;

	//取CSD信息，如果期间出错，返回0
	if(SD_GetCSD(Csd) != 0) return 0;	 
	//如果为SDHC卡，按照下面方式计算
	if((Csd[0] & 0xC0) == 0x40)
	{
			Capacity =  (((u32)(Csd[8])<<8) + (u32)Csd[9] + 1) * (u32)1024;
	}
	else
	{

		i = Csd[6] & 0x03;
		i <<= 8;
		i += Csd[7];
		i <<= 2;
		i += ((Csd[8] & 0xc0) >> 6);
	
		//C_SIZE_MULT
		Ret = Csd[9]&0x03;
		Ret<<= 1;
		Ret += ((Csd[10] & 0x80) >> 7);
	
		//BLOCKNR
		Ret += 2;
		Temp = 1;
		while(Ret)
		{
			Temp *= 2;
			Ret--;
		}
		Capacity = ((u32)(i + 1)) * ((u32)Temp);
		// READ_BL_LEN
		i = Csd[5]&0x0f;
		Temp = 1;
		while(i)
		{
			Temp *= 2;
			i--;
		}
    //The final result
		Capacity *= (u32)Temp; 
	}
	return (u32)Capacity;
}


/*******************************************************************************
* Function Name  : SD_ReadSingleBlock
* Description    : 读SD卡的一个block
* Input          : u32 Sector 取地址（Sector值，非物理地址） 
*                  u8 *Buffer 数据存储地址（大小至少512byte） 
* Output         : None
* Return         : u8 r1 
*                   0： 成功
*                   other：失败
*******************************************************************************/
u8 SD_ReadSingleBlock(u32 Sector, u8 *Buffer)
{
	u8 Ret;
  //设置为高速模式
	SPI_SetSpeed(SPI_SPEED_HIGH);   
  //如果不是SDHC，将Sector地址转成byte地址
  Sector = Sector<<9;
	Ret = SD_SendCommand(CMD17, Sector, 0);//读命令
	if(Ret != 0x00) return Ret;  
  Ret = SD_ReceiveData(Buffer, 512, RELEASE);
	return Ret;  
}

/*******************************************************************************
* Function Name  : SD_WriteSingleBlock
* Description    : 写入SD卡的一个block
* Input          : u32 Sector 扇区地址（Sector值，非物理地址） 
*                  u8 *Buffer 数据存储地址（大小至少512byte） 
* Output         : None
* Return         : u8 r1 
*                   0： 成功
*                   other：失败
*******************************************************************************/
u8 SD_WriteSingleBlock(u32 Sector, const u8 *Data)
{
	u8 Ret;
	u16 i;
	u16 Retry;
	//设置为高速模式
	SPI_SetSpeed(SPI_SPEED_HIGH);

  //如果不是SDHC，给定的是Sector地址，将其转换成byte地址
  if(SD_Type!=SD_TYPE_V2HC)
  {
		Sector = Sector<<9;
  }

  Ret = SD_SendCommand(CMD24, Sector, 0x00);
  if(Ret != 0x00) return Ret;   
	//开始准备数据传输
	SD_CS_ENABLE();
	//先放3个空数据，等待SD卡准备好
	SPI_ReadWriteByte(0xff);
	SPI_ReadWriteByte(0xff);
	SPI_ReadWriteByte(0xff);
	//放起始令牌0xFE
	SPI_ReadWriteByte(0xFE);

	//放一个Sector的数据
	for(i=0;i<512;i++)
	{
			SPI_ReadWriteByte(*Data++);
	}
	//发2个Byte的dummy CRC
	SPI_ReadWriteByte(0xff);
	SPI_ReadWriteByte(0xff);  
  //等待SD卡应答
  Ret = SPI_ReadWriteByte(0xff);
	if((Ret & 0x1F) != 0x05)
	{
			SD_CS_DISABLE();
			return Ret;
	}   
	//等待操作完成
	Retry = 0;
	while(!SPI_ReadWriteByte(0xff))
	{
		Retry++;
		if(Retry>0xfffe)        //如果长时间写入没有完成，报错退出
		{
			SD_CS_DISABLE();
			return 1;            //写入超时返回1
		}
	}
	//写入完成，片选置1
	SD_CS_DISABLE();
	SPI_ReadWriteByte(0xff);

	return 0;
}


/*******************************************************************************
* Function Name  : SD_ReadMultiBlock
* Description    : 读SD卡的多个block
* Input          : u32 Sector 取地址（Sector值，非物理地址） 
*                  u8 *Buffer 数据存储地址（大小至少512byte）
*                  u8 Count 连续读Count个block
* Output         : None
* Return         : u8 r1 
*                  0： 成功
*                  other：失败
*******************************************************************************/
u8 SD_ReadMultiBlock(u32 Sector, u8 *Buffer, u8 Count)
{
	u8 Ret;
  //设置为高速模式
	SPI_SetSpeed(SPI_SPEED_HIGH);
  //如果不是SDHC，将Sector地址转成byte地址
	Sector = Sector<<9;
  //SD_WaitReady();
  //发读多块命令
	Ret = SD_SendCommand(CMD18, Sector, 0);//读命令
	if(Ret != 0x00) return Ret;
	do
	{
		if(SD_ReceiveData(Buffer, 512, NO_RELEASE) != 0x00) break;
		Buffer += 512;
	} while(--Count);

	SD_SendCommand(CMD12, 0, 0);  //全部传输完毕，发送停止命令
	SD_CS_DISABLE();              //释放总线
	SPI_ReadWriteByte(0xFF);
	
	return Count;                 //如果没有传完，返回剩余个数
}

/*******************************************************************************
* Function Name  : SD_WriteMultiBlock
* Description    : 写入SD卡的N个block
* Input          : u32 Sector 扇区地址（Sector值，非物理地址） 
*                  u8 *Buffer 数据存储地址（大小至少512byte）
*                  u8 Count 写入的block数目
* Output         : None
* Return         : u8 r1 
*                  0： 成功
*                  other：失败
*******************************************************************************/
u8 SD_WriteMultiBlock(u32 Sector, const u8 *Data, u8 Count)
{
	u8 Ret;
	u16 i;

	//设置为高速模式
	SPI_SetSpeed(SPI_SPEED_HIGH);
	//如果不是SDHC，给定的是Sector地址，将其转换成byte地址
	if(SD_Type != SD_TYPE_V2HC)
	{
		Sector = Sector << 9;
	}
	//如果目标卡不是MMC卡，启用ACMD23指令使能预擦除
	if(SD_Type != SD_TYPE_MMC)
	{
		Ret = SD_SendCommand(ACMD23, Count, 0x00);
	}
  //发多块写入指令
	Ret = SD_SendCommand(CMD25, Sector, 0x00);
	if(Ret != 0x00) return Ret;
    
  //开始准备数据传输
	SD_CS_ENABLE();
	//先放3个空数据，等待SD卡准备好
	SPI_ReadWriteByte(0xff);
	SPI_ReadWriteByte(0xff);

	//是N个Sector写入的循环部分
	do
	{
		//放起始令牌0xFC 表明是多块写入
		SPI_ReadWriteByte(0XFC);  
		//放一个Sector的数据
		for(i = 0;i < 512;i++)
		{
			SPI_ReadWriteByte(*Data++);
		}
		//发2个Byte的dummy CRC
		SPI_ReadWriteByte(0XFF);
		SPI_ReadWriteByte(0XFF);     
		//等待SD卡应答
		Ret = SPI_ReadWriteByte(0XFF);
		if((Ret & 0X1F) != 0X05) //如果应答为报错，则带错误代码直接退出
		{
			SD_CS_DISABLE();    
			return Ret;
		}
		//等待SD卡写入完成
		if(SD_WaitReady()==1)
		{
				SD_CS_DISABLE();   
				return 1;
		}
	}while(--Count);
    
	//发结束传输令牌0xFD
	Ret = SPI_ReadWriteByte(0XFD);
	if(Ret==0X00) Count =  0XFE; 
	//写入完成，片选置1
	SD_CS_DISABLE();
	SPI_ReadWriteByte(0XFF);
	return Count;         //返回Count值，如果写完则Count=0，否则Count=1
}
