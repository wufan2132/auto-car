#include "PID.h"
/*
		算法说明：
		PID计算
*/
PID::PID(void)
{
	Kp = 0;
	Ki = 0;
	Kd = 0;
	
	LastError = 0;
	SumError = 0;
	Setpoint = 0;
	Feedback = 0;
	
	I_Limit = 0;
}

PID::PID(float Init_Kp,float Init_Ki,float Init_Kd,float Init_I_Limit)
{
	
	Kp = Init_Kp;
	Ki = Init_Ki;
	Kd = Init_Kd;
	
	LastError = 0;
	SumError = 0;
	Setpoint = 0;
	Feedback = 0;
	
	I_Limit = Init_I_Limit;
}

PID::PID(float Init_Kp,float Init_Ki,float Init_Kd,float Init_I_Limit,Filter_2nd Init_Filter_2nd_D)
{
	
	Kp = Init_Kp;
	Ki = Init_Ki;
	Kd = Init_Kd;
	
	LastError = 0;
	SumError = 0;
	Setpoint = 0;
	Feedback = 0;
	
	I_Limit = Init_I_Limit;
	
	//Filter_2nd_D = Init_Filter_2nd_D;
}

void PID::Rst_I(void)
{	
	SumError = 0;
}

/*
		计算PID, 消耗时间最大约100US
*/
double PID::Cal_PID_POS(int dt)
{
	double pError = 0;
	double dError = 0;
	double Error = Setpoint - Feedback;

	if((Error != 0) & (Ki != 0))
	{
		SumError += Error * Ki * dt / 1000.f;
		if(SumError > I_Limit) 
			SumError = I_Limit;
		if(SumError < -I_Limit) 
			SumError = -I_Limit;
	}
	
	if((Kd != 0))
	{
		dError = (Error - LastError) * Kd / dt * 1000.f;
		LastError = Error;
	}
	
	if((Error != 0) & (Kp != 0))
		pError = Error * Kp;
	
	Output = pError + SumError + dError;
	ValueTmp = dError;
	return Output;
}


double PID::Cal_PID_POS_BT_LPF(int dt)
{
	double pError = 0;
	double dError = 0;
	double Error = Setpoint - Feedback;

	if((Error != 0) & (Ki != 0))
	{
		SumError += Error * Ki * dt / 1000.f;
		if(SumError > I_Limit) 
			SumError = I_Limit;
		if(SumError < -I_Limit) 
			SumError = -I_Limit;
	}
	
	if((Kd != 0))
	{
		dError = (Error - LastError) * Kd / dt * 1000.f;
		LastError = Error;
		
		dError = Filter_2nd_D.LPF2ndFilter((float)dError);
	}
	
	if((Error != 0) & (Kp != 0))
		pError = Error * Kp;
	
	Output = pError + SumError + dError;
	ValueTmp = dError;
	return Output;
}
