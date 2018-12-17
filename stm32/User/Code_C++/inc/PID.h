#ifndef __PID_H__
#define __PID_H__
#include "Filter.h"

class PID
{
	public:
		PID(void);
		PID(float Init_Kp,float Init_Ki,float Init_Kd,float Init_I_Limit);
		PID(float Init_Kp,float Init_Ki,float Init_Kd,float Init_I_Limit,Filter_2nd Init_Filter_2nd_D);
		double Cal_P(void);
		double Cal_I(int dt);
		void	Rst_I(void);
		double Cal_D(int dt);	
		double Cal_PI_POS(int dt);		
		double Cal_PID_POS(int dt);	
		double Cal_PID_POS_BT_LPF(int dt);

		double Setpoint;
		double Feedback;
		double Output;
		double Kp;
		double Ki;
		double Kd;
		double SumError;
	private:

		double LastError;
		
		double I_Limit;
		double ValueTmp;
		Filter_2nd Filter_2nd_D;
};

#endif
