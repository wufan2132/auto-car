#include "Math_User.h"

double Constrain(double AimN, double Limit_Up,double Limit_Down);
float Dead_Zone(float AimN,float Limit);
Vector Body_To_Earth(Vector Body,float Yaw,float Roll,float Pitch);
Vector XY_Coordinate_Rotate(float X,float Y,float Angle);
struct Math_ Math =
{
	Constrain,
	Dead_Zone,
	Body_To_Earth,
	XY_Coordinate_Rotate
};


double Constrain(double AimN, double Limit_Up,double Limit_Down)
{
	if(AimN > Limit_Up) return Limit_Up;
	else
		if(AimN < Limit_Down) return Limit_Down;
		else return AimN;
}

float Dead_Zone(float AimN,float Limit)
{
	if(fabsf(AimN) < Limit) return 0;
	else return AimN;
}

/*
	坐标系关系说明：
	机体坐标系：机头-Y，机尾+Y,左+X,右-X/上北下南左西右东/机头指向正南为默认初始状态
							Yaw   ： 绕坐标系Z轴运动   z
	            Roll ： 绕坐标系Y轴运动		y
	            Pitc  ： 绕坐标系X轴运动		x
	参考坐标系：北东天坐标系  

	由Z-Y-X顺规有:
	载体坐标系到导航坐标系下旋转矩阵R(b2n)
	R(b2n) =R(Ψ)^T*R(θ)^T*R(Φ)^T
	R=
		 {cosΨ*cosθ     -cosΦ*sinΨ+sinΦ*sinθ*cosΨ        sinΨ*sinΦ+cosΦ*sinθ*cosΨ}
		 {cosθ*sinΨ     cosΦ*cosΨ +sinΦ*sinθ*sinΨ       -cosΨ*sinΦ+cosΦ*sinθ*sinΨ}
		 {-sinθ          cosθsin Φ                          cosθcosΦ    								}

PSI     Ψ
Theta  	θ
Phi			Φ
*/

Vector Body_To_Earth(Vector Body,float Yaw,float Roll,float Pitch)
{
	Vector Earth;
	Yaw  *= DEG_TO_RAD;
	Roll *= DEG_TO_RAD;
	Pitch*= DEG_TO_RAD;
	
	float COS_PSI   = arm_cos_f32(Yaw);
	float COS_Theta = arm_cos_f32(Roll);
	float COS_Phi   = arm_cos_f32(Pitch);
	float SIN_PSI   = arm_sin_f32(Yaw);	
	float SIN_Theta = arm_sin_f32(Roll);
	float SIN_Phi	  = arm_sin_f32(Pitch);
	
	Earth.x =  COS_PSI * COS_Theta * Body.x + (-COS_Phi * SIN_PSI + SIN_Phi * SIN_Theta * COS_PSI) * Body.y + ( SIN_PSI * SIN_Phi + COS_Phi * SIN_Theta * COS_PSI) * Body.z;
	Earth.y =  COS_Theta * SIN_PSI * Body.x + ( COS_Phi * COS_PSI + SIN_Phi * SIN_Theta * SIN_PSI) * Body.y + (-COS_PSI * SIN_Phi + COS_Phi * SIN_Theta * SIN_PSI) * Body.z;
	Earth.z = -SIN_Theta 					 * Body.x + 																 COS_Theta * SIN_Phi * Body.y + 																 COS_Theta * COS_Phi * Body.z;
	return Earth;
};

//Vector Body_To_Earth(Vector Body,float Pitch,float Roll)
//{
//	Vector Earth;
//	Pitch *= DEG_TO_RAD;
//	Roll *= DEG_TO_RAD;
//	float COS_Phi   = arm_cos_f32(Roll);
//	float COS_Theta = arm_cos_f32(Pitch);
//	float SIN_Phi   = arm_sin_f32(Roll);
//	float SIN_Theta = arm_sin_f32(Pitch);
//	
//	Earth.x =  COS_Theta * Body.x + SIN_Phi * SIN_Theta * Body.y + COS_Phi * SIN_Theta * Body.z;
//	Earth.y =                                 COS_Phi   * Body.y -             SIN_Phi * Body.z;
//	Earth.z = -SIN_Theta * Body.x + SIN_Phi * COS_Theta * Body.y + COS_Phi * COS_Theta * Body.z;
//	return Earth;
//};

Vector XY_Coordinate_Rotate(float X,float Y,float Angle)
{
	Vector Earth;
	Angle *= DEG_TO_RAD;
	float COS = arm_cos_f32(Angle);
	float SIN = arm_sin_f32(Angle);
	
	Earth.x =  COS * X +  SIN * Y;
	Earth.y = -SIN * X +  COS * Y;
	Earth.z = 0;
	
	return Earth;
};

float To_180_degrees(float x)
{
	return (x>180?(x-360):(x<-180?(x+360):x));
}

//保证输入值是有效的
float Safe_Asin(float v)
{
    if (isnan(v)) {
        return 0.0f;
    }
    if (v >= 1.0f) {
        return M_PI/2;
    }
    if (v <= -1.0f) {
        return -M_PI/2;
    }
    return asinf(v);
}
//角度转弧度
float Radians(float deg) 
	{
	return deg * DEG_TO_RAD;
}

//弧度转角度
float Degrees(float rad) 
	{
	return rad * RAD_TO_DEG;
}

