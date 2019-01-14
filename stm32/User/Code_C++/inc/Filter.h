#ifndef _FILTER_H_
#define _FILTER_H_
#include "Common.h"

class Filter_1nd
{


};

class Filter_2nd
{
	public:
		Filter_2nd();
		Filter_2nd(float Init_b0,float Init_b1,float Init_b2,float Init_a1,float Init_a2);

		//b:分子多项式系数
		//a:分母多项式系数 ,a0默认为1
		float b0;
		float b1;
		float b2;
		float a1;
		float a2;
		Vector PreIn;
		Vector LastIn;
		Vector PreOut;
		Vector LastOut;
		
		
		Vector LPF2ndFilter(Vector Input);
		float LPF2ndFilter(float Input);
};
class Filter_MidValue
{
	public:
		Filter_MidValue(void)
		{
			Cnt = 0;
		};
		Vector MidValue(Vector Input);
		float MidValue(float Input);
	private:
		float Bubble(float Input[3]);
		Vector Data[3];
		float Data1[3];
		int Cnt;
};

class Filter_Fir
{
	public:
		Filter_Fir(int N_Input,float* Para_Input,float* Data_Input)
		{
			N = N_Input;
			Para = Para_Input;
			Data = Data_Input;
		};
		
		int N;
		int Cnt;
		float* Para;
		float* Data;
	
		float FirFilter(float Input);
};

class Filter_Balance
{
	public:
		Filter_Balance(float Kp_Input,float Ki_Input)
		{
			Kp = Kp_Input;
			Ki = Ki_Input;
			SumError = 0;
			Output = 0;
		};
		float Kp;
		float Ki;
		float Output;
		float SumError;
		float BalanceFilter(float Input,float Measurement,double dt);
};

class Filter_EKF_Single
{
	public:
		Filter_EKF_Single(float Q_Set,float R_Set)
		{
			X_k_k1 = 0;
			X_k_k = 0;
			P_k_k1 = 0;
			P_k_k = 0;
			Kg = 1;
			Q = Q_Set;
			R = R_Set;
		}
		
		float EKFFilter_Single(float Model,float Input);
		
		float X_k_k1;
		float X_k_k;
		float P_k_k1;
		float P_k_k;
		double Kg;
		double Q;
		double R;
	
};

class Filter_EKF_Double
{
	public:
		Filter_EKF_Double(float Q0_Set,float Q1_Set,float R0_Set,float R1_Set)
		{
			P[0] = 0;
			P[1] = 0;
			P[2] = 0;
			P[3] = 0;
			
			Pre_P[0] = 0;
			Pre_P[1] = 0;
			Pre_P[2] = 0;
			Pre_P[3] = 0;
			
			Kg[0] = 1;
			Kg[1] = 1;
			Kg[2] = 1;
			Kg[3] = 1;
			
			Q[0] = Q0_Set;
			Q[1] = Q1_Set;
			R[0] = R0_Set;
			R[1] = R1_Set;
		}
		
		void EKFFilter_Double(float Model,float Model_D ,float Input,float Input_D,float Input_DD,float &Out,float &Out_D,float Dt);
		
	private:
		float P[4];
		float Pre_P[4];
		double Kg[4];
		double Q[2];
		double R[2];
	
};

#endif
