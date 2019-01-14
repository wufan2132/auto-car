#include "Communication.h"
#include <stdio.h>

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))


/***********************通信串口通道选择**********************/
#define usart_TX2 usart1
/**********************************************************/


BOOL Communicate(void);
#define BUF_SIZE 64
u8 Communicate_BUF[BUF_SIZE];

struct SYS_State_ SYS_State;
struct User_Data_ User_Data;

struct Communication_ Communication = 
{
	Communicate
};

void Send_Senser_TX2(void)
{
	vs16 Temp1 = 0;
	vs32 Temp2 = 0;
	float Temp3;
	u8 Cnt = 1;
	//标志位压缩发送
	u8 flag = 0;
	
	flag = (flag<<1 | (CarControl.Para->Mode));
	flag = (flag<<1 | (CarControl.Para->IsLock));
	flag = (flag<<1 | (CarControl.Para->IsLost));
	flag = (flag<<1 | (CarControl.Para->IsError));
	
	
	Communicate_BUF[Cnt++] = 0XAA;
	Communicate_BUF[Cnt++] = 0XAA;
	Communicate_BUF[Cnt++] = 0XA1;
	Communicate_BUF[Cnt++] = 0;
	
	//Communicate_BUF[Cnt++] = flag;
	
	Temp3 = speed_measure.Value;	
	Communicate_BUF[Cnt++] = BYTE0(Temp3);	
	Communicate_BUF[Cnt++] = BYTE1(Temp3);
	Communicate_BUF[Cnt++] = BYTE2(Temp3);	
	Communicate_BUF[Cnt++] = BYTE3(Temp3);
	
	Temp3 = Attitude.Angle->x;	
	Communicate_BUF[Cnt++] = BYTE0(Temp3);	
	Communicate_BUF[Cnt++] = BYTE1(Temp3);
	Communicate_BUF[Cnt++] = BYTE2(Temp3);	
	Communicate_BUF[Cnt++] = BYTE3(Temp3);		
	
	Temp3 = Attitude.Angle->y;	
	Communicate_BUF[Cnt++] = BYTE0(Temp3);	
	Communicate_BUF[Cnt++] = BYTE1(Temp3);
	Communicate_BUF[Cnt++] = BYTE2(Temp3);	
	Communicate_BUF[Cnt++] = BYTE3(Temp3);
	
	Temp3 = Attitude.Angle->z;	
	Communicate_BUF[Cnt++] = BYTE0(Temp3);	
	Communicate_BUF[Cnt++] = BYTE1(Temp3);
	Communicate_BUF[Cnt++] = BYTE2(Temp3);	
	Communicate_BUF[Cnt++] = BYTE3(Temp3);
	
	Temp3 = MPU6050.Data->ACC_ADC.x;
	Communicate_BUF[Cnt++] = BYTE0(Temp3);	
	Communicate_BUF[Cnt++] = BYTE1(Temp3);
	Communicate_BUF[Cnt++] = BYTE2(Temp3);	
	Communicate_BUF[Cnt++] = BYTE3(Temp3);		
	
	Temp3 = MPU6050.Data->ACC_ADC.y;	
	Communicate_BUF[Cnt++] = BYTE0(Temp3);	
	Communicate_BUF[Cnt++] = BYTE1(Temp3);
	Communicate_BUF[Cnt++] = BYTE2(Temp3);	
	Communicate_BUF[Cnt++] = BYTE3(Temp3);	
	
	Temp3 = MPU6050.Data->ACC_ADC.z;	
	Communicate_BUF[Cnt++] = BYTE0(Temp3);	
	Communicate_BUF[Cnt++] = BYTE1(Temp3);
	Communicate_BUF[Cnt++] = BYTE2(Temp3);	
	Communicate_BUF[Cnt++] = BYTE3(Temp3);	
	
	Temp3 = MPU6050.Data->GYR_ADC.x;
	Communicate_BUF[Cnt++] = BYTE0(Temp3);	
	Communicate_BUF[Cnt++] = BYTE1(Temp3);
	Communicate_BUF[Cnt++] = BYTE2(Temp3);	
	Communicate_BUF[Cnt++] = BYTE3(Temp3);	
	
	Temp3 = MPU6050.Data->GYR_ADC.y;
	Communicate_BUF[Cnt++] = BYTE0(Temp3);	
	Communicate_BUF[Cnt++] = BYTE1(Temp3);
	Communicate_BUF[Cnt++] = BYTE2(Temp3);	
	Communicate_BUF[Cnt++] = BYTE3(Temp3);	
		
	Temp3 = MPU6050.Data->GYR_ADC.z;
	Communicate_BUF[Cnt++] = BYTE0(Temp3);	
	Communicate_BUF[Cnt++] = BYTE1(Temp3);
	Communicate_BUF[Cnt++] = BYTE2(Temp3);	
	Communicate_BUF[Cnt++] = BYTE3(Temp3);	
	
	Communicate_BUF[4] = Cnt - 5;
	
	u8 Sum = 0;
	for(u8 i = 1;i < Cnt; i++)
		Sum += Communicate_BUF[i];
	
	Communicate_BUF[Cnt++] = Sum;
	Communicate_BUF[0] = Cnt - 1;   

	usart_TX2.send(Communicate_BUF,Cnt);
	
}
//void Send_Senser2_TX2(void)
//{
//	vs32 Temp2 = 0;
//	u8 Cnt = 1;
//	
//	Communicate_BUF[Cnt++] = 0XAA;
//	Communicate_BUF[Cnt++] = 0XAA;
//	Communicate_BUF[Cnt++] = 0X07;
//	Communicate_BUF[Cnt++] = 0;
//	
//	Temp2 = MS5611.Data->Altitude*10000;	
//	Communicate_BUF[Cnt++] = BYTE3(Temp2);	
//	Communicate_BUF[Cnt++] = BYTE2(Temp2);		
//	Communicate_BUF[Cnt++] = BYTE1(Temp2);	
//	Communicate_BUF[Cnt++] = BYTE0(Temp2);
//	
//	Temp2 = Power.Data->BAT_3S*1000000;
//	Communicate_BUF[Cnt++] = BYTE3(Temp2);	
//	Communicate_BUF[Cnt++] = BYTE2(Temp2);	
//	Communicate_BUF[Cnt++] = BYTE1(Temp2);	
//	Communicate_BUF[Cnt++] = BYTE0(Temp2);
//	
//	Communicate_BUF[4] = Cnt - 5;
//	
//	u8 Sum = 0;
//	for(u8 i = 1;i < Cnt; i++)
//		Sum += Communicate_BUF[i];
//	
//	Communicate_BUF[Cnt++] = Sum;
//	Communicate_BUF[0] = Cnt - 1;   

//	usart_TX2.send(Communicate_BUF,Cnt);
//	
//}
//void Send_Eular_TX2(void)
//{
//	u16 Temp1 = 0;
//	vs32 Temp2 = 0;
//	u8 Cnt = 1;

//	Communicate_BUF[Cnt++] = 0XAA;
//	Communicate_BUF[Cnt++] = 0XAA;
//	Communicate_BUF[Cnt++] = 0X01;
//	Communicate_BUF[Cnt++] = 0;
//	
//	Temp1 = (int)(Attitude.Angle->x * 100.0f);	
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);	
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);		
//	
//	Temp1 = (int)(Attitude.Angle->y * 100.0f);	
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);	
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);	
//	
//	Temp1 = (int)(Attitude.Angle->z * 100.0f);	
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);	
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);		
//	
//  Temp2 = (u32)(Position.Position_xyz.z* 100.0f);	
//	Communicate_BUF[Cnt++] = BYTE3(Temp2);	
//	Communicate_BUF[Cnt++] = BYTE2(Temp2);	
//	Communicate_BUF[Cnt++] = BYTE1(Temp2);	
//	Communicate_BUF[Cnt++] = BYTE0(Temp2);
//	
//	Communicate_BUF[Cnt++] = CarControl.Para->Mode;
//	Communicate_BUF[Cnt++] = CarControl.Para->IsLock;
//	
//	Communicate_BUF[4] = Cnt - 5;
//	
//	u8 Sum = 0;
//	for(u8 i = 1;i < Cnt; i++)
//		Sum += Communicate_BUF[i];
//	
//	Communicate_BUF[Cnt++] = Sum;
//	Communicate_BUF[0] = Cnt - 1; 
//	
//	usart_TX2.send(Communicate_BUF,Cnt);
//}

//void Send_RC_TX2(void)
//{
//	u16 Temp1 = 0;
//	u8 Cnt = 1;
//	
//	Communicate_BUF[Cnt++] = 0XAA;
//	Communicate_BUF[Cnt++] = 0XAA;
//	Communicate_BUF[Cnt++] = 0X03;
//	Communicate_BUF[Cnt++] = 0;
//	
//	Temp1 = 15 ;	
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);	
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);		
//	
//	Temp1 = 0;
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);	
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);	
//	
//	Temp1 = 0;	
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);	
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);		
//	
//	Temp1 = 0;
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);

//	Temp1 = PWM_In.Data->CH1;
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);

//	Temp1 = PWM_In.Data->CH2;
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);
//	
//	Temp1 = PWM_In.Data->CH3; 
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);	

//	Temp1 = PWM_In.Data->CH4;
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);
//	
//	Temp1 = PWM_In.Data->CH5;
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);

//	Temp1 = PWM_In.Data->CH6;
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);

//	Communicate_BUF[4] = Cnt - 5;
//	
//	u8 Sum = 0;
//	for(u8 i = 1;i < Cnt; i++)
//		Sum += Communicate_BUF[i];
//	
//	Communicate_BUF[Cnt++] = Sum;
//	Communicate_BUF[0] = Cnt - 1; 
//	
//	usart_TX2.send(Communicate_BUF,Cnt);
//}

//void Send_Motor_TX2(void)
//{
//	u16 Temp1 = 0;
//	u8 Cnt = 1;
//	
//	Communicate_BUF[Cnt++] = 0XAA;
//	Communicate_BUF[Cnt++] = 0XAA;
//	Communicate_BUF[Cnt++] = 0X06;
//	Communicate_BUF[Cnt++] = 0;
//	
//	Temp1 = Motor.PWM->PWM1;	
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);	
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);	
//	
//	Temp1 = Motor.PWM->PWM2;	
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);	
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);	
//	
//	Temp1 = Motor.PWM->PWM3;	
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);	
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);		

//	Temp1 = Motor.PWM->PWM4;	
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);	
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);	
//	
//	Temp1 = Power.Data->BAT_3S*100;		
//	Communicate_BUF[Cnt++] = BYTE1(Temp1);	
//	Communicate_BUF[Cnt++] = BYTE0(Temp1);	
//	
//	Communicate_BUF[4] = Cnt - 5;
//	
//	u8 Sum = 0;
//	for(u8 i = 1;i < Cnt; i++)
//		Sum += Communicate_BUF[i];
//	
//	Communicate_BUF[Cnt++] = Sum;
//	Communicate_BUF[0] = Cnt - 1; 
//	usart_TX2.send(Communicate_BUF,Cnt);
//}

//BOOL Send_PID_Para_TX2(u8 Group)
//{
//	u8 Cnt = 1;
//	vs16 Temp = 0;
//	PID Temp_PID[3];
//	
//	switch(Group)
//	{
//		case 1:
//		break;	
//		case 2:
//			break;
//		case 3:
//			break;
//		default:
//			break;
//	}
//	
//	Communicate_BUF[Cnt++] = 0xAA;
//	Communicate_BUF[Cnt++] = 0xAA;
//	Communicate_BUF[Cnt++] = 0x10 + Group - 1;
//	Communicate_BUF[Cnt++] = 0;
//	
//	Temp = Temp_PID[0].Kp ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	Temp = Temp_PID[0].Ki ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	Temp = Temp_PID[0].Kd ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	
//	Temp = Temp_PID[1].Kp;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	Temp = Temp_PID[1].Ki;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	Temp = Temp_PID[1].Kd ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	
//	Temp = Temp_PID[2].Kp;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	Temp = Temp_PID[2].Ki ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	Temp = Temp_PID[2].Kd ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	
//	Communicate_BUF[4] = Cnt - 5;
//	
//	u8 Sum = 0;
//	for(u8 i=1;i<Cnt;i++)
//		Sum += Communicate_BUF[i];
//	
//	Communicate_BUF[Cnt++]=Sum;

//	Communicate_BUF[0] = Cnt - 1;    //HID第一个字节 表示数据长度
//	
//	usart_TX2.send(Communicate_BUF,Cnt);
//	return True;
//}

//BOOL Send_UserData_TX2(void)
//{
//	u8 Cnt = 1;
//	vs16 Temp = 0;
//	
//	Communicate_BUF[Cnt++] = 0xAA;
//	Communicate_BUF[Cnt++] = 0xAA;
//	Communicate_BUF[Cnt++] = 0xF1;
//	Communicate_BUF[Cnt++] = 0;
//	
//	Temp = User_Data.Data1 ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	
//	Temp = User_Data.Data2 ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	
//	Temp = User_Data.Data3 ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	
//	Temp = User_Data.Data4 ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	
//	Temp = User_Data.Data5 ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	
//	Temp = User_Data.Data6 ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	
//	Temp = User_Data.Data7 ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	
//	Temp = User_Data.Data8 ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	
//	Temp = User_Data.Data9 ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	
//	Temp = User_Data.Data10 ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	
//	Temp = User_Data.Data11 ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	
//	Temp = User_Data.Data12 ;
//	Communicate_BUF[Cnt++] = BYTE1(Temp);
//	Communicate_BUF[Cnt++] = BYTE0(Temp);
//	
//	Communicate_BUF[4] = Cnt - 5;
//	
//	u8 Sum = 0;
//	for(u8 i=1;i<Cnt;i++)
//		Sum += Communicate_BUF[i];
//	
//	Communicate_BUF[Cnt++]=Sum;

//	Communicate_BUF[0] = Cnt - 1;    //HID第一个字节 表示数据长度
//	
//	usart_TX2.send(Communicate_BUF,Cnt);
//	return True;
//}

void Send_Reply_TX2(u16 Sum,u8 Head)
{
	Communicate_BUF[0] = 0X07;                      //帧长
	Communicate_BUF[1] = 0XAA;
	Communicate_BUF[2] = 0XAA;
	Communicate_BUF[3] = 0XEF;
	Communicate_BUF[4] = 2;
	Communicate_BUF[5] = Head;
	
	Communicate_BUF[6] = Sum;	
	
	u8 sum = 0;
	for(u8 i=1;i<7;i++)
		sum += Communicate_BUF[i];
	
	Communicate_BUF[7]=sum;	
	
	usart_TX2.send(Communicate_BUF,8);
}




void Data_Analysis_TX2(void)
{
	#define TX2_BUF_SIZE 32
	static u8 Rx_buf[TX2_BUF_SIZE];
	static int64_t rece_count  = 0;
	u8 Length = 0;
	u8 Funtion = 0;
	u8 Sum = 0;
	if(usart_TX2.readframe(Rx_buf, &Length, &Funtion) == True) 
	{	
		rece_count ++;
		Sum = Rx_buf[Length];
		 switch (Funtion) 																      //帧功能分析
			{
				case 0X01:
					MPU6050.IsCalibrating = 1;
					break;
				case 0X02:
					break;
				case 0X10:                                           //PID1 2用于描述外环参数
					Send_Reply_TX2(Sum,0X10);				
					break;
				case 0X30:
					if((int16_t)(Rx_buf[0] << 8 | Rx_buf[1])>0)
						CarControl.Para->IsLock = True;
					else
						CarControl.Para->IsLock = False;
				case 0X31:
					if((int16_t)(Rx_buf[0] << 8 | Rx_buf[1])>0)
						CarControl.Para->Mode = Auto;
					else if((int16_t)(Rx_buf[0] << 8 | Rx_buf[1])==0)
						CarControl.Para->Mode = Manual;
					else
						CarControl.Para->Mode = Other;
				case 0XA1:				
						CarControl.throttlt = (int16_t)(Rx_buf[0] << 8 | Rx_buf[1]);
						CarControl.brake = (int16_t)(Rx_buf[2] << 8 | Rx_buf[3]);
						CarControl.steer = (int16_t)(Rx_buf[4] << 8 | Rx_buf[5]);
						CarControl.test = (int16_t)(Rx_buf[6] << 8 | Rx_buf[7]) - rece_count;
					break;
				default:
					break;
		}
	}
}


//void Data_Analysis_TX2(void)
//{
//	#define TX2_BUF_SIZE 32
//	static u8 Rx_buf[TX2_BUF_SIZE];
//	
//	u8 i = 0;
//	u8 Start = 0;
//	u8 Length = 0;
//	
//	
//	u8 Sum = 0;
//	u8 Funtion = 0;

//	if(usart_TX2.receive(Rx_buf,TX2_BUF_SIZE) == True) 
//	{
//		for(i = 0;i < TX2_BUF_SIZE; i++)
//		{
//			if(i == 31) return;
//			if(Rx_buf[i] == 0XAA & Rx_buf[i+1] == 0XAF)
//				break;
//		}
//		Length = Rx_buf[i + 3] + 4;
//		Start = i;
//		Funtion = Rx_buf[i + 2];
//		
//		for(i = 0;i < Length;i++)
//			Sum += Rx_buf[Start + i];
//		
//		if(Sum == Rx_buf[Start + Length])
//		{ 
//		 switch (Funtion) 																      //帧功能分析
//			{
//				case 0X01:
//					MPU6050.IsCalibrating = 1;
//					break;
//				case 0X02:
//					break;
//				case 0X10:                                           //PID1 2用于描述外环参数
//					Send_Reply_TX2(Sum,0X10);				
//					break;
//				case 0X30:
//					if((int16_t)(Rx_buf[Start + 4] << 8 | Rx_buf[Start + 5])>0)
//						CarControl.Para->IsLock = True;
//					else
//						CarControl.Para->IsLock = False;
//				case 0X31:
//					if((int16_t)(Rx_buf[Start + 4] << 8 | Rx_buf[Start + 5])>0)
//						CarControl.Para->Mode = Auto;
//					else if((int16_t)(Rx_buf[Start + 4] << 8 | Rx_buf[Start + 5])==0)
//						CarControl.Para->Mode = Manual;
//					else
//						CarControl.Para->Mode = Other;
//				case 0XA1:				
//						CarControl.throttlt = (int16_t)(Rx_buf[Start + 4] << 8 | Rx_buf[Start + 5]);
//						CarControl.brake = (int16_t)(Rx_buf[Start + 6] << 8 | Rx_buf[Start + 7]);
//						CarControl.steer = (int16_t)(Rx_buf[Start + 8] << 8 | Rx_buf[Start + 9]);
//					break;
//				default:
//					break;
//			}
//		}
//	}
//}

void Send_Data_TX2(void)
{
		Send_Senser_TX2();
}

u32 Char_2_Int(u8 *str)
{
	u32 Float_Int_temp = 0;
	u8 * Str_Add_temp = str;
	u16 i = 0;

	for(i = 0;Str_Add_temp[i] != '}'; i++)
	{
		if( i > 10 )return 0;
		Float_Int_temp = (Float_Int_temp + (Str_Add_temp[i] - '0'))*10;
	}
	Float_Int_temp = Float_Int_temp*0.1;
	return Float_Int_temp;
}





BOOL Communicate(void)
{
//#if USE_GPS_PC// GPS未占用串口1进行调试，才可正常使用
//	GPS_UART.GPS_Cof();
//#endif	
//	
//#if USE_PHONE
//	Data_Analysis_Phone();
//	Send_Data_Phone();
//#endif	
//	
//#if USE_VCAN
//		Vcan_Send_Data_PC();
//#endif		
	

		Send_Data_TX2();
		Data_Analysis_TX2();


	return True;
}

