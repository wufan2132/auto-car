#include "Position.h"

void Position_Updata(u16 Time_Ms);
void Position_Init(void);
Filter_Balance FIL_Speed(0.1,0);
Filter_Balance FIL_Position_xyz(1,0);
struct Position_ Position = 
{
	Vector(0,0,0),
	Vector(0,0,0),
	Vector(0,0,0),
	Position_Init,
	Position_Updata
};

//Time :MS
void Position_Init(void)
{
	MS5611.Init();
	GPS_UART.Init(115200);
}

/****气压计三阶互补滤波方案——参考开源飞控APM****/
#define TIME_CONTANST_ZER 2.5f
#define K_ACC_ZER 	    (1.0f / (TIME_CONTANST_ZER * TIME_CONTANST_ZER * TIME_CONTANST_ZER))
#define K_VEL_ZER	        (3.0f / (TIME_CONTANST_ZER * TIME_CONTANST_ZER))														
#define K_POS_ZER         (2.0f / TIME_CONTANST_ZER)
#define Delay_Cnt 60
void Altitude_Update(u16 Time_Ms,Vector ACC_Earth)
{
	float Origion_Acc_z;
	static float acc_correction = 0;
	static float vel_correction = 0;
	static float pos_correction = 0;
	static float Last_Acc_z = 0;
	static float Origion_Speed_z = 0;
	static float Origion_Position_z = 0;
	float SpeedDealt = 0;
	float Altitude_Dealt=0;
	float Altitude_Estimate=0;
	static float Altitude_History[Delay_Cnt+1];
	float Delta_T;
	u16 Cnt=0;
	
	static uint16_t Save_Cnt=0;
	Save_Cnt++;//数据存储周期
	
	Delta_T = Time_Ms/1000.0;//ms转s 单位 s
	Altitude_Estimate = MS5611.Data->Altitude*100.0;//高度观测量 m转cm 单位cm
	Origion_Acc_z = ACC_Earth.z;//加速度  单位cm/s2
	
	//由观测量（气压计）得到状态误差
	Altitude_Dealt = Altitude_Estimate -  Position.Position_xyz.z;//气压计(超声波)与SINS估计量的差，单位cm
	//三路积分反馈量修正惯导
	acc_correction +=Altitude_Dealt* K_ACC_ZER*Delta_T ;//加速度矫正量
	vel_correction +=Altitude_Dealt* K_VEL_ZER*Delta_T ;//速度矫正量
	pos_correction +=Altitude_Dealt* K_POS_ZER*Delta_T ;//位置矫正量
	//加速度计矫正后更新
	Last_Acc_z = Position.Acc.z;//上一次加速度量
	Position.Acc.z = Origion_Acc_z + acc_correction;// 加速度单位cm/s2
	//速度增量矫正后更新，用于更新位置,由于步长h=0.005,相对较长，
	//这里采用二阶龙格库塔法更新微分方程，不建议用更高阶段，因为加速度信号非平滑
	SpeedDealt = (Last_Acc_z + Position.Acc.z) * Delta_T/2.0;
	//原始位置更新
	Origion_Position_z += (Position.Speed.z + 0.5*SpeedDealt) * Delta_T;
	//位置矫正后更新
	Position.Position_xyz.z = Origion_Position_z + pos_correction;    
	//原始速度更新
	Origion_Speed_z += SpeedDealt;
	//速度矫正后更新
	Position.Speed.z = Origion_Speed_z + vel_correction;

	if(Save_Cnt>=1)
	{
		for(Cnt = Delay_Cnt;Cnt > 0;Cnt--)//滑动
		{
			Altitude_History[Cnt]=Altitude_History[Cnt-1];
		}
		Altitude_History[0] = Position.Position_xyz.z;
		Save_Cnt=0;
	}
}

/*********************************水平位置双观测卡尔曼融合 GPS+ACC *****************************************/
Filter_EKF_Double Filter_EKF_X(0.02,0.05,50,200);
Filter_EKF_Double Filter_EKF_Y(0.02,0.05,50,200);
void XY_Update(u16 Time_Ms,Vector ACC_Earth)
{
	if(GPS_Location.state != 0 && GPS_Location.SatNum > 5)
	{
		Filter_EKF_X.EKFFilter_Double(Position.Position_xyz.x,		//上次预估距离				cm
																	Position.Speed.x,						//上次预估速度				cm/s
																	GPS_Location.POS_X,					//当前GPS观测距离   	cm
																	GPS_Location.Speed.x,				//当前GPS观测速度   	cm/s
																	ACC_Earth.x,						//当前加速度计观测加速度 cm/s2
																	Position.Position_xyz.x,		//预估出距离        	cm
																	Position.Speed.x,						//预估出速度					cm/s
																	Time_Ms/1000);							//周期时间						s
		Position.Acc.x = ACC_Earth.x; //cm/s2
		Filter_EKF_Y.EKFFilter_Double(Position.Position_xyz.y,		//上次预估距离
																	Position.Speed.y,						//上次预估速度
																	GPS_Location.POS_Y,					//当前GPS观测距离
																	GPS_Location.Speed.y,				//当前GPS观测速度
																	ACC_Earth.y,						//当前加速度计观测加速度
																	Position.Position_xyz.y,		//预估出距离
																	Position.Speed.y,						//预估出速度
																	Time_Ms/1000);							//周期时间						s
		Position.Acc.y = ACC_Earth.y;	//cm/s2
	}
}

void Position_Updata(u16 Time_Ms)
{
	Vector ACC_Earth;
	ACC_Earth = Math.Body_To_Earth(MPU6050.Data->ACC_ADC,Attitude.Angle->z,Attitude.Angle->y,Attitude.Angle->x);
	
	ACC_Earth.x /= 4095;
	ACC_Earth.x *= 980.0f;//cm/s2
	
	ACC_Earth.y /= 4095;
	ACC_Earth.y *= 980.0f;//cm/s2
	
	ACC_Earth.z -= 4095;
	ACC_Earth.z /= 4095;
	ACC_Earth.z *= 980.0f;//cm/s2
	
//--------------高度融合--------------------------------------------------------------------//
	Altitude_Update(Time_Ms,ACC_Earth);
//--------------水平位置融合--------------------------------------------------------------------//
	XY_Update(Time_Ms,ACC_Earth);
	
}





