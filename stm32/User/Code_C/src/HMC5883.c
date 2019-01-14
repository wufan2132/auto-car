#include "HMC5883.h"

#define HMC5883ADDRESS 0x3C

void HMC5883_Init(void);
void HMC5883_Updata(void);

I2C_Soft_ I2C_HMC5883('C',GPIO_Pin_7,GPIO_Pin_6,4);
Filter_MidValue MAG_Filter;
struct HMC5883_Data_ HMC5883_Data = 
{
	Vector(0,0,0),
	Vector(0,0,0),
	Vector(5.815732650220095e+02,5.537799967613940e+02,5.799757108788048e+02),
	Vector(-35.164162661161970,-83.359733295493170,-35.139569568929420),
	0
};


struct HMC5883_ HMC5883 = 
{
	False,
	&HMC5883_Data,
	HMC5883_Init,
	HMC5883_Updata
};

void HMC5883_Init(void)
{
	I2C_HMC5883.Init();
	I2C_HMC5883.Single_Write(HMC5883ADDRESS,0X00,0X7C);// 8次平均 220HZ
	I2C_HMC5883.Single_Write(HMC5883ADDRESS,0X01,0X20);// +-1.3GA 0.92MG/LSB
	I2C_HMC5883.Single_Write(HMC5883ADDRESS,0X02,0X80);// 高速 连续
	SystemTime.WaitMS(10);
}

void HMC5883_Updata(void)
{
	u8 BUF[6];
	static u16 ErrorCnt = 0; // 100次中，错误多少次
	static u16 AllCnt = 0;   // 记录读取多少次，连续最大100次
	I2C_HMC5883.Start();
	I2C_HMC5883.SendByte(HMC5883ADDRESS);
	I2C_HMC5883.WaitAck();
	I2C_HMC5883.SendByte(0X03);
	I2C_HMC5883.WaitAck();
	I2C_HMC5883.Start();
	I2C_HMC5883.SendByte(HMC5883ADDRESS + 1);
	I2C_HMC5883.WaitAck();
	for(u8 i = 0;i < 5;i++)
	{
		BUF[i] = I2C_HMC5883.ReadByte();
		I2C_HMC5883.Ack();
	}
	
	BUF[5] = I2C_HMC5883.ReadByte();
	I2C_HMC5883.NoAck();
	I2C_HMC5883.Stop();
	
	HMC5883.Data->MAG_Original.x = -((int16_t)(BUF[0] << 8 | BUF[1]));
	HMC5883.Data->MAG_Original.z = -((int16_t)(BUF[2] << 8 | BUF[3]));
	HMC5883.Data->MAG_Original.y = ((int16_t)(BUF[4] << 8 | BUF[5]));

	HMC5883.Data->MAG_Original = MAG_Filter.MidValue(HMC5883.Data->MAG_Original);	
	
	Vector MAG_TMP;
	//椭球校正算法，校正结果为单位球
	MAG_TMP.x = (HMC5883.Data->MAG_Original.x - HMC5883.Data->Offset.x) / HMC5883.Data->Kp.x;
	MAG_TMP.y = (HMC5883.Data->MAG_Original.y - HMC5883.Data->Offset.y) / HMC5883.Data->Kp.y;
	MAG_TMP.z = (HMC5883.Data->MAG_Original.z - HMC5883.Data->Offset.z) / HMC5883.Data->Kp.z;
	HMC5883.Data->Length = MAG_TMP.x * MAG_TMP.x + MAG_TMP.y * MAG_TMP.y + MAG_TMP.z * MAG_TMP.z;

	//验证三轴平方和是否接近1 ，不接近于1，出错,该数据置零无效
	if(abs(HMC5883.Data->Length - 1) < 0.2f)
	{
		HMC5883.IsSensorError = False;
		HMC5883.Data->MAG_ADC = MAG_TMP;				
	}
	else	
	{ 
		HMC5883.IsSensorError = True;
		//ErrorCnt++;
		//错误则保持原磁场值
	}
	//出错百分百大于百分之10，认为传感器出错，停止使用,这里有问题
	//EEROR_LQ
//	if(AllCnt++ == 100)
//	{		
//		if(ErrorCnt > 10)
//		{
//			HMC5883.IsSensorError = True;
//		}
//		HMC5883.Data->ErrorCnt = ErrorCnt;//记录出错百分比
//		AllCnt = 0;
//		ErrorCnt = 0;
//	}		
}
