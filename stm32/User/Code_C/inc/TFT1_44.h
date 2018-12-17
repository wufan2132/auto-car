#ifndef __TFT1_44_H__
#define __TFT1_44_H__
#include "stm32f4xx.h"
#include "time.h"
#include "Common.h"
#include "ASCII_Code.h"
#include <math.h>


#define BLACK  0X0000
#define WHITE  0XFFFF
#define BLUE   0XFF00
#define YELLOW 0X80FF
#define RED    0X00F8
#define GREEN  0XE007

//单位是坐标
class Point
{
	public:
		Point(float X_Set,float Y_Set)
		{
			X = X_Set;
			Y = Y_Set;
		};
		Point()
		{
			X = 0;
			Y = 0;		
		}
		float X;
		float Y;
};
//单位像素
class Rectanle
{
	public:
		Rectanle(u16 X_LU_Set,u16 Y_LU_Set,u16 X_RD_Set,u16 Y_RD_Set)
		{
			X_LU = X_LU_Set;
			Y_LU = Y_LU_Set;
			X_RD = X_RD_Set;
			Y_RD = Y_RD_Set;
		}
		Rectanle()
		{
			X_LU = 0;
			Y_LU = 0;
			X_RD = 0;
			Y_RD = 0;
		}		
		u16 X_LU;
		u16 Y_LU;
		u16 X_RD;
		u16 Y_RD;
};
struct TFT_Data
{
	char HalfWord;
	Point POS;
	u16 Color;
};
extern struct TFT_
{
	void (*Init)(void);
	void (*FillString)(Point POS,const char* P,u16 Color,u16 BackGroundColor);
	void (*FillNumber)(Point POS,int Number   ,u16 Color,u16 BackGroundColor);
	void (*FillRectangle)(Rectanle RECT,BOOL IsHollow,u16 Color);
	void (*FillFloat)(Point POS,float Number ,u16 Color,u16 BackGroundColor);
	void (*ClearPixel)(Rectanle RECT);

}TFT;

#endif 

