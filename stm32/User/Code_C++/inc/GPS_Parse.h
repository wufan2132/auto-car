#ifndef __GPS_PARSE_H__
#define __GPS_PARSE_H__
#include "stm32f4xx.h"
#include "Common.h"

class PVT_Data_
{
	public:
	u32 iTOW;
	u16 year;					//年 
	u8 month;					//月 
	u8 day;					  //日 
	u8 hour;					//时 
	u8 min;						//分 
	u8 sec;						//秒 
	u8 valid;					//有效标志位 
	u32 tAcc;					//时间精度估计
	s32 nano; 				//分数部分
	u8 fixType;				//定位类型
	u8 flags; 				//是否有效定位  差分模式是否开启(DGPS)  省电模式、未用  航向是否有效
	u8 reserved1; 		//保留
	u8 numSV;   			//参与定位卫星个数
	s32 lon;					//经度  deg
	s32 lat;					//纬度  deg
	s32 height;				//椭球高度  mm
	s32 hMSL;					//GPS获取海拔高度 	mm
	u32 hAcc;					//水平位置估计精度 mm
	u32 vAcc;					//垂直位置估计精度	mm
	s32 velN;					//GPS获取的沿导航系正北速度  		mm/s
	s32 velE;					//GPS获取的沿导航系正东向速度  	mm/s
	s32 velD;					//GPS获取的沿导航系'天'向速度  	mm/s
	s32 gSpeed;				//载体对地速度	mm/s
	s32 heading;			//载体运动航向角	deg
	u32 sAcc;					//速度估计精度 mm/s
	u32 headingAcc;		//载体运动航向角估计精度 deg
	u16 pDOP;					//位置精度因子
	u16 reserved2;
	u32 reserved3;
};
#define GPS_PVT_BUF_SIZE 110
class GPS_PVT
{
public:
	GPS_PVT()
	{}
	void GPS_PVT_Parse(void);	
	PVT_Data_ PVT_Data;
private:
	u8 Rx_buf[GPS_PVT_BUF_SIZE];

};

class GPS
{
	public:
		GPS(){
		Home_OffectX = 0;
		Home_OffectY = 0;
		Home_OffectZ = 0;
		};
			
	u8 state;
	u8 SatNum;
	float pDOP;
	double Home_OffectX;
	double Home_OffectY;
	double Home_OffectZ;
			
	double POS_X;
	double POS_Y;
	double POS_Z;
	Vector POS;	
	Vector Speed;
	void GPS_Update(void);
			
	private:
		void GPS_Unit_transform(void);
};

extern GPS GPS_Location;
#endif


