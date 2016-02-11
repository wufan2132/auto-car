#include "MPU6050.h"
#include "Communication.h"

#define CALIBRATE_CYCLE 3000
#define ACC_1G 4095
#define EARTH_ACC_SCALER 0.00239316239316
#define Address_Base 0x080E0000
#define Address_ACC  (0*3)
#define Address_GYRO (4*3)
#define Address_Init_Flag (8*3)



void MPU6050_Init(void);
void MPU6050_Updata(void);
void MPU6050_Para_Read(void);
void MPU6050_Para_Save(void);

I2C_Soft_ I2C_Soft_MPU6050('C',GPIO_Pin_2,GPIO_Pin_1,1);
Filter_2nd ACC_Filter(0.1883633f,0,0,-1.023694f,0.2120577f);
Filter_MidValue GYR_Filter;
struct MPU6050_Data_ MPU6050_Data;

struct MPU6050_ MPU6050 = 
{
	False,False,
	PARA_SVAE_ERROR,
	&MPU6050_Data,
	MPU6050_Init,
	MPU6050_Updata,
};


void MPU6050_Init(void)
{
	I2C_Soft_MPU6050.Init();
	//设备复位
	SystemTime.WaitMS(50);
	I2C_Soft_MPU6050.Single_Write(MPU6050_ADDRESS,MPU_RA_PWR_MGMT_1, 0x80);	
	
	SystemTime.WaitMS(5);
	
	//陀螺仪采样率，0x00(1000Hz)   采样率 = 陀螺仪的输出率 / (1 + SMPLRT_DIV)
	I2C_Soft_MPU6050.Single_Write(MPU6050_ADDRESS,MPU_RA_SMPLRT_DIV, 0X00);	
	//设置设备时钟源，8M
	I2C_Soft_MPU6050.Single_Write(MPU6050_ADDRESS, MPU_RA_PWR_MGMT_1, 0x00);
	//关闭所有中断,开启bypass
	I2C_Soft_MPU6050.Single_Write(MPU6050_ADDRESS, MPU_RA_INT_PIN_CFG, 0X00);
	//低通滤波频率，0x03(42Hz)
	I2C_Soft_MPU6050.Single_Write(MPU6050_ADDRESS,MPU_RA_CONFIG, 0X06);
	 //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
	I2C_Soft_MPU6050.Single_Write(MPU6050_ADDRESS, MPU_RA_GYRO_CONFIG, 0x18);
	//加速计自检、测量范围(不自检，+-8G)			
	I2C_Soft_MPU6050.Single_Write(MPU6050_ADDRESS,MPU_RA_ACCEL_CONFIG, 0X10);
	//读取偏置
	MPU6050_Para_Read();
	
}

void MPU6050_Read_ACC(void)
{
	u8 Buffer[6];
	int16_t ACC_Temp[3];
	
	Buffer[0] = I2C_Soft_MPU6050.Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_XOUT_L); 
	Buffer[1] = I2C_Soft_MPU6050.Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_XOUT_H);
	ACC_Temp[0] = ((((int16_t)Buffer[1]) << 8) | Buffer[0]);  //加速度X轴

	Buffer[2] = I2C_Soft_MPU6050.Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_YOUT_L);
	Buffer[3] = I2C_Soft_MPU6050.Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_YOUT_H);
	ACC_Temp[1] = ((((int16_t)Buffer[3]) << 8) | Buffer[2]);  //加速度Y轴

	Buffer[4] = I2C_Soft_MPU6050.Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_ZOUT_L);
	Buffer[5] = I2C_Soft_MPU6050.Single_Read(MPU6050_ADDRESS,MPU_RA_ACCEL_ZOUT_H);
	ACC_Temp[2] = ((((int16_t)Buffer[5]) << 8) | Buffer[4]);  //加速度Z轴

	MPU6050_Data.ACC_ADC_Original.x = (float)ACC_Temp[0];
	MPU6050_Data.ACC_ADC_Original.y = (float)ACC_Temp[1];
	MPU6050_Data.ACC_ADC_Original.z = (float)ACC_Temp[2];	
	
	MPU6050_Data.ACC_ADC.x = -(MPU6050_Data.ACC_ADC_Original.x - MPU6050_Data.ACC_Offset.x)*EARTH_ACC_SCALER;
	MPU6050_Data.ACC_ADC.y = (MPU6050_Data.ACC_ADC_Original.y - MPU6050_Data.ACC_Offset.y)*EARTH_ACC_SCALER;
	MPU6050_Data.ACC_ADC.z = (MPU6050_Data.ACC_ADC_Original.z - MPU6050_Data.ACC_Offset.z)*EARTH_ACC_SCALER;
	
	MPU6050_Data.ACC_ADC = ACC_Filter.LPF2ndFilter(MPU6050_Data.ACC_ADC);
}


void MPU6050_Read_GYR(void)
{
	u8 Buffer[6];
	int16_t GYR_Temp[3];
	
	Buffer[0] = I2C_Soft_MPU6050.Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_XOUT_L); 
	Buffer[1] = I2C_Soft_MPU6050.Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_XOUT_H);
	GYR_Temp[0] = ((((int16_t)Buffer[1]) << 8) | Buffer[0]);  //角速度X轴

	Buffer[2] = I2C_Soft_MPU6050.Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_YOUT_L);
	Buffer[3] = I2C_Soft_MPU6050.Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_YOUT_H);
	GYR_Temp[1] = ((((int16_t)Buffer[3]) << 8) | Buffer[2]);  //角速度Y轴

	Buffer[4] = I2C_Soft_MPU6050.Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_ZOUT_L);
	Buffer[5] = I2C_Soft_MPU6050.Single_Read(MPU6050_ADDRESS,MPU_RA_GYRO_ZOUT_H);
	GYR_Temp[2] = ((((int16_t)Buffer[5]) << 8) | Buffer[4]);  //角速度Z轴
	
	MPU6050_Data.GYR_ADC_Original.x = (float)GYR_Temp[0];
	MPU6050_Data.GYR_ADC_Original.y = (float)GYR_Temp[1];
	MPU6050_Data.GYR_ADC_Original.z = (float)GYR_Temp[2];
	
	MPU6050_Data.GYR_ADC.x = MPU6050_Data.GYR_ADC_Original.x - MPU6050_Data.GYR_Offset.x;
	MPU6050_Data.GYR_ADC.y = MPU6050_Data.GYR_ADC_Original.y - MPU6050_Data.GYR_Offset.y;
	MPU6050_Data.GYR_ADC.z = MPU6050_Data.GYR_ADC_Original.z - MPU6050_Data.GYR_Offset.z;
	
	
	MPU6050_Data.GYR_ADC = GYR_Filter.MidValue(MPU6050_Data.GYR_ADC);

}

void MPU6050_Calibrate(void)
{
	static int Cnt = 0;
	static Vector Buff_ACC;
	static Vector Buff_GYR;
	if(MPU6050.IsCalibrating == True)
	{
		if(Cnt == 0)
		{
			MPU6050_Data.ACC_Offset.x = 0;
			MPU6050_Data.ACC_Offset.y = 0;
			MPU6050_Data.ACC_Offset.z = 0;
			
			MPU6050_Data.GYR_Offset.x = 0;
			MPU6050_Data.GYR_Offset.y = 0;
			MPU6050_Data.GYR_Offset.z = 0;
			Cnt = 1;
			return;
		}
		
		if(Cnt <= CALIBRATE_CYCLE)
		{
			Cnt++;
			Buff_ACC.x = (Buff_ACC.x + MPU6050_Data.ACC_ADC_Original.x);
			Buff_ACC.y = (Buff_ACC.y + MPU6050_Data.ACC_ADC_Original.y);
			Buff_ACC.z = (Buff_ACC.z + MPU6050_Data.ACC_ADC_Original.z);
			
			Buff_GYR.x = (Buff_GYR.x + MPU6050_Data.GYR_ADC_Original.x);
			Buff_GYR.y = (Buff_GYR.y + MPU6050_Data.GYR_ADC_Original.y);
			Buff_GYR.z = (Buff_GYR.z + MPU6050_Data.GYR_ADC_Original.z);
		}
		else
		{
			Cnt = 0;
			MPU6050.IsCalibrating = False;

			MPU6050_Data.ACC_Offset.x = Buff_ACC.x / CALIBRATE_CYCLE;
			MPU6050_Data.ACC_Offset.y = Buff_ACC.y / CALIBRATE_CYCLE;
			MPU6050_Data.ACC_Offset.z = Buff_ACC.z / CALIBRATE_CYCLE - ACC_1G;
			
			MPU6050_Data.GYR_Offset.x = Buff_GYR.x / CALIBRATE_CYCLE;
			MPU6050_Data.GYR_Offset.y = Buff_GYR.y / CALIBRATE_CYCLE;
			MPU6050_Data.GYR_Offset.z = Buff_GYR.z / CALIBRATE_CYCLE;
			
			Buff_ACC.x = 0;
			Buff_ACC.y = 0;
			Buff_ACC.z = 0;
			
			Buff_GYR.x = 0;
			Buff_GYR.y = 0;
			Buff_GYR.z = 0;
			
			MPU6050_Para_Save();
		}
		
	}

}

void MPU6050_Updata(void)
{
	MPU6050_Read_ACC();
	MPU6050_Read_GYR();
	MPU6050_Calibrate();
}
//存储Offset的时候保留小数点2位
BOOL Write_Flash()
{
	BOOL Mark = True;
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
	FLASH_EraseSector(FLASH_Sector_11, VoltageRange_3);

	if(FLASH_ProgramWord((Address_Base + Address_ACC + 0),(int)(MPU6050_Data.ACC_Offset.x * 100.0f)) != FLASH_COMPLETE) Mark = False;  
	if(FLASH_ProgramWord((Address_Base + Address_ACC + 4),(int)(MPU6050_Data.ACC_Offset.y * 100.0f)) != FLASH_COMPLETE) Mark = False;  
	if(FLASH_ProgramWord((Address_Base + Address_ACC + 8),(int)(MPU6050_Data.ACC_Offset.z * 100.0f)) != FLASH_COMPLETE) Mark = False;  
	if(FLASH_ProgramWord((Address_Base + Address_GYRO + 0),(int)(MPU6050_Data.GYR_Offset.x * 100.0f)) != FLASH_COMPLETE) Mark = False;  
	if(FLASH_ProgramWord((Address_Base + Address_GYRO + 4),(int)(MPU6050_Data.GYR_Offset.y * 100.0f)) != FLASH_COMPLETE) Mark = False;  
	if(FLASH_ProgramWord((Address_Base + Address_GYRO + 8),(int)(MPU6050_Data.GYR_Offset.z * 100.0f)) != FLASH_COMPLETE) Mark = False;  
	if(FLASH_ProgramWord((Address_Base + Address_Init_Flag),(int)100) != FLASH_COMPLETE) Mark = False;
	FLASH_Lock();
	
	return Mark;
}

float Read_Flash(u16 Address)
{
	int Buff = 0;
	
	Buff = *(int32_t*)(Address_Base + Address);
	
	return (float)Buff / 100.0f;
}
void MPU6050_Para_Save(void)
{
	if(Write_Flash() == False) MPU6050.State = PARA_SVAE_ERROR;
}

void MPU6050_Para_Read(void)
{
	//RCC_HSICmd(ENABLE);  这里应该是没有用的
	MPU6050.IsCalibrated = Read_Flash(Address_Init_Flag);

	if(MPU6050.IsCalibrated == True)  
	{
		MPU6050_Data.ACC_Offset.x = Read_Flash(Address_ACC + 0);
		MPU6050_Data.ACC_Offset.y = Read_Flash(Address_ACC + 4);
		MPU6050_Data.ACC_Offset.z = Read_Flash(Address_ACC + 8);
		
		MPU6050_Data.GYR_Offset.x = Read_Flash(Address_GYRO + 0);
		MPU6050_Data.GYR_Offset.y = Read_Flash(Address_GYRO + 4);
		MPU6050_Data.GYR_Offset.z = Read_Flash(Address_GYRO + 8);
	}
	else                        //从未初始化，需要MPU6050校准
	{
		MPU6050.IsCalibrating = True;
	}
}
