#include "FlyControl.h"

#define ATT_ANGLE_SPEED_RC_Z_MAX  	20    						 		//遥控Z最大转角速度
#define ATT_ANGLE_SPEED      				(45.0f * DEG_TO_RAD)  //最大转角速度
#define ATT_ANGLE_MAX        				20.0f                 //最大倾角

#define ATT_FILTER_ANGLE   	 				0.1f                  //角度环前置滤波器系数
#define ATT_FILTER_SPEED     				0.1f                  //角速度环前置滤波系数

#define POS_POS_SET_MAX_XY       		1000.0f              //XY最大距离 cm
#define POS_SPEED_SET_MAX_XY      	100.0f               //XY最大速度 cm/s
#define POS_ACC_SET_MAX_XY        	100.0f               //XY最大加速度 cm/s
#define POS_OUT_MAX_XY        			3.0f               //XY最大输出  角度值

#define POS_POS_FEEBACK_MAX_XY      (1.5*POS_POS_SET_MAX_XY) //XY最大反馈距离 cm
#define POS_SPEED_FEEBACK_MAX_XY    100.0f                    //XY最大反馈速度 cm/s
#define POS_ACC_FEEBACK_MAX_XY      100.0f                   //XY最大反馈加速度 cm/s

#define POS_POS_SET_MAX_Z        		500.0f                   //Z最大高度 cm
#define POS_SPEED_SET_MAX_Z      		40.0f                    //Z最大速度 cm/s
#define POS_ACC_SET_MAX_Z        		60.0f                    //Z最大加速度 cm/s
#define POS_OUT_MAX_Z        				THROTTLE_60_PERCENT         //Z最大输出

#define POS_POS_FEEBACK_MAX_Z       (1.5*POS_POS_SET_MAX_Z)  //Z最大反馈高度 cm
#define POS_SPEED_FEEBACK_MAX_Z     40.0f                    //Z最大反馈速度 cm/s
#define POS_ACC_FEEBACK_MAX_Z       100.0f                   //Z最大反馈加速度 cm/s

#define POS_FILTER_POS   	  				0.1f                    //位置前置滤波器系数
#define POS_FILTER_SPEED     				0.1f                    //速度环前置滤波系数
#define POS_FILTER_ACC       				0.8f                    //加速度环前置滤波系数

#define THROTTLE_MIN PWM_RC_MIN
#define THROTTLE_MAX PWM_RC_MAX
#define THROTTLE_MID ((PWM_RC_MAX + PWM_RC_MIN) / 2)
#define THROTTLE_60_PERCENT ((THROTTLE_MAX - THROTTLE_MIN) * 0.6f)

void ATT_Inner_Loop(u32 Time);
void ATT_Outer_Loop(u32 Time);
void POS_Acc_Loop(u32 Time);
void POS_Inner_Loop(u32 Time);
void POS_Outer_Loop(u32 Time);

/*
	PID ATT_Inner_PID_x;
	PID ATT_Inner_PID_y;
	PID ATT_Inner_PID_z;
	
	PID ATT_Outer_PID_x;
	PID ATT_Outer_PID_y;	
	PID ATT_Outer_PID_z;	
	
	PID POS_Inner_PID_x;
	PID POS_Inner_PID_y;
	PID POS_Inner_PID_z;
	
	PID POS_Outer_PID_x;
	PID POS_Outer_PID_y;
	PID POS_Outer_PID_z;
	int Throttle;

	float ALT_Onland;
	BOOL IsLock;
	BOOL IsLost;
	BOOL IsError;
	Fly_Mode Mode;  
*/
struct Control_Para_ Control_Para = 
{
//	PID(160,20,10,100),
//	PID(160,20,10,100),
//	PID(400,0,0,0),
//	
//	PID(15,0,0,0),
//	PID(15,0,0,0),
//	PID(1,0,0,0),
//	
//	PID(0,0,0,0),
//	PID(0,0,0,0),
//	PID(1,0,0,0,Filter_2nd(0.0009446918438402,0.00188938368768,0.0009446918438402,-1.911197067426,0.9149758348014)),	//采样频率200HZ 截止频率 2HZ 
//	
//	PID(0,0,0,0),
//	PID(0,0,0,0),
//	PID(1,0,0,0,Filter_2nd(0.0009446918438402,0.00188938368768,0.0009446918438402,-1.911197067426,0.9149758348014)),	//采样频率200HZ 截止频率 2HZ 
//	
//	PID(0,0,0,0),
//	PID(0,0,0,0),
//	PID(1,0,0,0),


	PID(95,40,6,100),
	PID(90,40,5,100),
	PID(400,0,0,0),
	
	PID(10,0,0,0),
	PID(10,0,0,0),
	PID(1,0,0,0),
	
	PID(0.003,0.01,0,10,Filter_2nd(0.00015514842347569903,0.00031029684695139806,0.00015514842347569903,-1.964460580205232,0.96508117389913495)),	//采样频率500HZ 截止2HZ 
	PID(0.003,0.01,0,10,Filter_2nd(0.00015514842347569903,0.00031029684695139806,0.00015514842347569903,-1.964460580205232,0.96508117389913495)),	//采样频率500HZ 截止2HZ 
	PID(0.8,1.5,0,600,Filter_2nd(0.00015514842347569903,0.00031029684695139806,0.00015514842347569903,-1.964460580205232,0.96508117389913495)),	//采样频率500HZ 截止2HZ 

	PID(0.2,0,0.0008,0,Filter_2nd(0.06745527388907,0.1349105477781,0.06745527388907,-1.14298050254,0.4128015980962)),	//采样频率200HZ 截止频率 20HZ 
	PID(0.2,0,0.0008,0,Filter_2nd(0.06745527388907,0.1349105477781,0.06745527388907,-1.14298050254,0.4128015980962)),	//采样频率200HZ 截止频率 20HZ 
	PID(2,0,0.1,0,Filter_2nd(0.06745527388907,0.1349105477781,0.06745527388907,-1.14298050254,0.4128015980962)),	//采样频率200HZ 截止频率 20HZ 

	PID(1,0,0,0),
	PID(1,0,0,0),
	PID(1,0,0,0),

	THROTTLE_MIN,
	
	0,
	
	Vector(0,0,0),
	True,
	False,
	False,
	NO_HEAD,
	ALT
};

struct FlyControl_ FlyControl = 
{	
	&Control_Para,
	
	ATT_Inner_Loop,
	ATT_Outer_Loop,
	
	POS_Acc_Loop,
	POS_Inner_Loop,
	POS_Outer_Loop,	
};

/*
	弧度制单位 
*/
Filter_2nd Rate_Filter(0.0036216815149286421f,0.0072433630298572842f,0.0036216815149286421f,-1.8226949251963083f,0.83718165125602262f);
void ATT_Inner_Loop(u32 Time)
{
	Vector Rate_filter_Temp;
	Vector Inner_Output;
	if(Control_Para.IsLock == True)            //停机 复位
	{
		Control_Para.ATT_Inner_PID_x.Rst_I();
		Control_Para.ATT_Inner_PID_y.Rst_I();
		Control_Para.ATT_Inner_PID_z.Rst_I();
		Motor.Stop();
		return;
	}

	//Rate_filter_Temp = Rate_Filter.LPF2ndFilter(*Attitude.Rate);
	//陀螺仪读取到的数据直接用于内环控制
	Control_Para.ATT_Inner_PID_x.Feedback = Attitude.Rate->x;
	Control_Para.ATT_Inner_PID_y.Feedback = Attitude.Rate->y;
	Control_Para.ATT_Inner_PID_z.Feedback = Attitude.Rate->z;
		
	Inner_Output.x = Control_Para.ATT_Inner_PID_x.Cal_PID_POS(Time);
	Inner_Output.y = Control_Para.ATT_Inner_PID_y.Cal_PID_POS(Time);
 	Inner_Output.z = Control_Para.ATT_Inner_PID_z.Cal_PID_POS(Time);
		
	//四轴输出
	Motor.PWM->PWM1 = - Inner_Output.x -  Inner_Output.y + Inner_Output.z + Control_Para.Throttle;	
	Motor.PWM->PWM2 = - Inner_Output.x +  Inner_Output.y - Inner_Output.z + Control_Para.Throttle;
	Motor.PWM->PWM3 = + Inner_Output.x +  Inner_Output.y + Inner_Output.z + Control_Para.Throttle; 
	Motor.PWM->PWM4 = + Inner_Output.x -  Inner_Output.y - Inner_Output.z + Control_Para.Throttle;
	
	Motor.Output(True);
}
/*
	弧度制单位 
*/
void ATT_Outer_Loop(u32 Time)
{
	double ATT_Outer_PID_z_Feedback_2_Setpoint = 0;
	Vector ATT_XY_RC;
	Vector Outer_Output;
	float Z_Angle_Change;
	
	if(Control_Para.IsLock == True) 
	{
		Control_Para.ATT_Outer_PID_x.Rst_I();
		Control_Para.ATT_Outer_PID_y.Rst_I();
		Control_Para.ATT_Outer_PID_z.Rst_I();
		Control_Para.Home_Z_Angle = Attitude.Angle->z;
		Control_Para.ATT_Outer_PID_z.Setpoint = Radians(Control_Para.Home_Z_Angle);	 //启动时偏航角保持
		return;
	}
	//-----------XY姿态控制-----------------------------------------------------//	
	if(Control_Para.Mode == ATT || Control_Para.Mode == ALT)  //姿态模式和定高模式 
	{
		ATT_XY_RC.x = Radians(Math.Dead_Zone(PWM_RC_F_B - PWM_RC_MID,10) / PWM_RC_RANGE * ATT_ANGLE_MAX);
		ATT_XY_RC.y = Radians(Math.Dead_Zone(PWM_RC_L_R - PWM_RC_MID,10) / PWM_RC_RANGE * ATT_ANGLE_MAX);
		//X前后旋转 Y左右旋转 无头模式遥控量转换	
		if(Control_Para.Head_Mode == NO_HEAD)  //无头模式下进行XY姿态控制量转换
		{	//控制量从机体原始坐标系转到当前机体坐标系
			Z_Angle_Change = Attitude.Angle->z - Control_Para.Home_Z_Angle;
		}
		else if(Control_Para.Head_Mode == HEAD) 
		{//控制量保持当前机体坐标系
			Z_Angle_Change = 0;
		}
	}
	else if(Control_Para.Mode == POS)	//定点模式  
	{
		ATT_XY_RC.x = Control_Para.POS_Acc_PID_x.Output;
		ATT_XY_RC.y = Control_Para.POS_Acc_PID_y.Output;
		//X前后旋转 Y左右旋转
		//控制量从地理坐标系转到机体坐标系
		Z_Angle_Change = Attitude.Angle->z;
	}
	
	if(Z_Angle_Change > 180 )	//180角度相减处理
		Z_Angle_Change = Z_Angle_Change - 360;
	else if(Z_Angle_Change < -180 )
		Z_Angle_Change = Z_Angle_Change + 360;
	else if(abs(Z_Angle_Change) < 180 )
		Z_Angle_Change = Z_Angle_Change;
	
	ATT_XY_RC = Math.XY_Coordinate_Rotate(ATT_XY_RC.x,ATT_XY_RC.y,Z_Angle_Change);//控制量坐标系转换		

	Control_Para.ATT_Outer_PID_x.Setpoint = (1 - ATT_FILTER_ANGLE) * Control_Para.ATT_Outer_PID_x.Setpoint + ATT_FILTER_ANGLE * ATT_XY_RC.x;
	Control_Para.ATT_Outer_PID_y.Setpoint = (1 - ATT_FILTER_ANGLE) * Control_Para.ATT_Outer_PID_y.Setpoint + ATT_FILTER_ANGLE * ATT_XY_RC.y;

	Control_Para.ATT_Outer_PID_x.Feedback = Radians(Attitude.Angle->x);
	Control_Para.ATT_Outer_PID_y.Feedback = Radians(Attitude.Angle->y);
	// PID计算及限幅
	Outer_Output.x = Math.Constrain(Control_Para.ATT_Outer_PID_x.Cal_PID_POS(Time),ATT_ANGLE_SPEED,-ATT_ANGLE_SPEED);
	Outer_Output.y = Math.Constrain(Control_Para.ATT_Outer_PID_y.Cal_PID_POS(Time),ATT_ANGLE_SPEED,-ATT_ANGLE_SPEED);
	// 输出平滑
	Control_Para.ATT_Inner_PID_x.Setpoint = (1 - ATT_FILTER_SPEED) * Control_Para.ATT_Inner_PID_x.Setpoint + ATT_FILTER_SPEED * Outer_Output.x;
	Control_Para.ATT_Inner_PID_y.Setpoint = (1 - ATT_FILTER_SPEED) * Control_Para.ATT_Inner_PID_y.Setpoint + ATT_FILTER_SPEED * Outer_Output.y;	


	//------------Z姿态控制-----------------------------------------------------//	
	Control_Para.ATT_Outer_PID_z.Feedback = Radians(Attitude.Angle->z);		
	ATT_Outer_PID_z_Feedback_2_Setpoint = Control_Para.ATT_Outer_PID_z.Feedback; //+-180度处理前取值，保证目标值为+-180范围
	
	//偏航角跨越+-180度处理
	if((Control_Para.ATT_Outer_PID_z.Setpoint - Control_Para.ATT_Outer_PID_z.Feedback) > M_PI)
	{
		Control_Para.ATT_Outer_PID_z.Feedback = Control_Para.ATT_Outer_PID_z.Feedback + 2*M_PI;
	}
	else if((Control_Para.ATT_Outer_PID_z.Setpoint - Control_Para.ATT_Outer_PID_z.Feedback) < -M_PI)
	{
		Control_Para.ATT_Outer_PID_z.Feedback = Control_Para.ATT_Outer_PID_z.Feedback - 2*M_PI;
	}
	
	Outer_Output.z = Math.Constrain(Control_Para.ATT_Outer_PID_z.Cal_PID_POS(Time),ATT_ANGLE_SPEED,-ATT_ANGLE_SPEED);

	//根据打舵量控制偏航角
	PWM_In_POS Yaw_Control_Choose = PWM_In.POS_Judge(PWM_RC_Lr_Rr);	
	if(Yaw_Control_Choose != PWM_In_Mid )//打舵则不进行角度控制 并直接用打舵量控制角速度   不打舵则退出并保持回中时角度 
	{
		Control_Para.ATT_Outer_PID_z.Setpoint = ATT_Outer_PID_z_Feedback_2_Setpoint;
		Control_Para.ATT_Inner_PID_z.Setpoint = (1 - ATT_FILTER_SPEED) * Control_Para.ATT_Inner_PID_z.Setpoint + ATT_FILTER_SPEED * Radians((float)Math.Dead_Zone(PWM_RC_MID - PWM_RC_Lr_Rr ,10) / PWM_RC_RANGE * ATT_ANGLE_SPEED_RC_Z_MAX);
	}
	else//不打舵则直接用 外环角度控制输出量 控制 角速度
	{
		Control_Para.ATT_Inner_PID_z.Setpoint = (1 - ATT_FILTER_SPEED) * Control_Para.ATT_Inner_PID_z.Setpoint + ATT_FILTER_SPEED * Outer_Output.z;
	}
}

void POS_Acc_Loop(u32 Time)
{
	//-------------预先处理-------------------------------------------------------------------//
	if(Control_Para.IsLock == True)  
	{
		Control_Para.POS_Acc_PID_x.Rst_I();
		Control_Para.POS_Acc_PID_y.Rst_I();
		Control_Para.POS_Acc_PID_z.Rst_I();
		return;
	}
	
	//姿态模式油门直接取决于遥控输入信号，其他模式油门取决于PID运算结果	
	if(Control_Para.Mode == ATT) 
	{
		//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		//YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
		//ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ
		Control_Para.POS_Acc_PID_x.Rst_I();
		Control_Para.POS_Acc_PID_y.Rst_I();
		Control_Para.POS_Acc_PID_z.Rst_I();
		
		Control_Para.Throttle = (1 - POS_FILTER_ACC) * Control_Para.Throttle + POS_FILTER_ACC * 2 * (PWM_RC_D_U - PWM_RC_MID);		
		Control_Para.Throttle = Math.Constrain(Control_Para.Throttle,POS_OUT_MAX_Z,0);
		return;		
	}
	if(Control_Para.Mode == ALT) 
	{
		Control_Para.POS_Acc_PID_x.Rst_I();
		Control_Para.POS_Acc_PID_y.Rst_I();
	}
	else if(Control_Para.Mode == POS) 
	{
		//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		//--------------pid控制\直接输出------------------------------------------------------------------//
		Control_Para.POS_Acc_PID_x.Feedback = Math.Constrain( Position.Acc.x,POS_ACC_FEEBACK_MAX_XY,-POS_ACC_FEEBACK_MAX_XY);
		// PID计算及限幅
		Control_Para.POS_Acc_PID_x.Output = Math.Constrain(Control_Para.POS_Acc_PID_x.Cal_PID_POS_BT_LPF(Time),POS_OUT_MAX_XY,-POS_OUT_MAX_XY);
		
		//YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
		//--------------pid控制\直接输出------------------------------------------------------------------//
		Control_Para.POS_Acc_PID_y.Feedback = Math.Constrain( Position.Acc.y,POS_ACC_FEEBACK_MAX_XY,-POS_ACC_FEEBACK_MAX_XY);
		// PID计算及限幅
		Control_Para.POS_Acc_PID_y.Output = Math.Constrain(Control_Para.POS_Acc_PID_y.Cal_PID_POS_BT_LPF(Time),POS_OUT_MAX_XY,-POS_OUT_MAX_XY);
	}
	
	if(Control_Para.Mode == ALT || Control_Para.Mode == POS) 
	{
		//ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ
		//--------------pid控制\直接输出------------------------------------------------------------------//
		Control_Para.POS_Acc_PID_z.Feedback = Math.Constrain( Position.Acc.z,POS_ACC_FEEBACK_MAX_Z,-POS_ACC_FEEBACK_MAX_Z);
		// PID计算及限幅
		Control_Para.Throttle = Math.Constrain(Control_Para.POS_Acc_PID_z.Cal_PID_POS_BT_LPF(Time),POS_OUT_MAX_Z,0);
	}
}

void POS_Inner_Loop(u32 Time)
{
	Vector Inner_Output;
	//-------------预先处理-------------------------------------------------------------------//
	if(Control_Para.IsLock == True)  
	{
		Control_Para.POS_Inner_PID_x.Rst_I();
		Control_Para.POS_Inner_PID_y.Rst_I();
		Control_Para.POS_Inner_PID_z.Rst_I();
		return;
	}
	//姿态模式油门直接取决于遥控输入信号，其他模式油门取决于PID运算结果	
	if(Control_Para.Mode == ATT) 
	{
		Control_Para.POS_Inner_PID_x.Rst_I();	
		Control_Para.POS_Inner_PID_y.Rst_I();	
		Control_Para.POS_Inner_PID_z.Rst_I();		
		return;		
	}
	if(Control_Para.Mode == ALT) 
	{
		Control_Para.POS_Inner_PID_x.Rst_I();
		Control_Para.POS_Inner_PID_y.Rst_I();
	}
	else if(Control_Para.Mode == POS) //XY控制
	{
		//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		//--------------pid控制------------------------------------------------------------------//
		Control_Para.POS_Inner_PID_x.Feedback = Math.Constrain(Position.Speed.x,POS_SPEED_FEEBACK_MAX_XY,-POS_SPEED_FEEBACK_MAX_XY);
		// PID计算及限幅
		Inner_Output.x =  Math.Constrain(Control_Para.POS_Inner_PID_x.Cal_PID_POS(Time),POS_ACC_SET_MAX_XY,-POS_ACC_SET_MAX_XY);	
		//--------------输出处理------------------------------------------------------------------//
		// 输出平滑
		Control_Para.POS_Acc_PID_x.Setpoint = (1 - POS_FILTER_ACC) * Control_Para.POS_Acc_PID_x.Setpoint + POS_FILTER_ACC * Inner_Output.x;
		
		//YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
		//--------------pid控制------------------------------------------------------------------//
		Control_Para.POS_Inner_PID_y.Feedback = Math.Constrain(Position.Speed.y,POS_SPEED_FEEBACK_MAX_XY,-POS_SPEED_FEEBACK_MAX_XY);
		// PID计算及限幅
		Inner_Output.y =  Math.Constrain(Control_Para.POS_Inner_PID_y.Cal_PID_POS(Time),POS_ACC_SET_MAX_XY,-POS_ACC_SET_MAX_XY);	
		//--------------输出处理------------------------------------------------------------------//
		// 输出平滑
		Control_Para.POS_Acc_PID_y.Setpoint = (1 - POS_FILTER_ACC) * Control_Para.POS_Acc_PID_y.Setpoint + POS_FILTER_ACC * Inner_Output.y;
	}
	
	if(Control_Para.Mode == ALT || Control_Para.Mode == POS) //Z控制
	{
		//ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ
		//--------------pid控制------------------------------------------------------------------//
		Control_Para.POS_Inner_PID_z.Feedback = Math.Constrain(Position.Speed.z,POS_SPEED_FEEBACK_MAX_Z,-POS_SPEED_FEEBACK_MAX_Z);
		// PID计算及限幅
		Inner_Output.z =  Math.Constrain(Control_Para.POS_Inner_PID_z.Cal_PID_POS(Time),POS_ACC_SET_MAX_Z,-POS_ACC_SET_MAX_Z);	
		//--------------输出处理------------------------------------------------------------------//
		// 输出平滑
		Control_Para.POS_Acc_PID_z.Setpoint = (1 - POS_FILTER_ACC) * Control_Para.POS_Acc_PID_z.Setpoint + POS_FILTER_ACC * Inner_Output.z;
	}
}

// 加锁的方式过于简单，在飞行过程中也会出现油门拉到最低的情况，不能简单的根据油门值加锁
void POS_Outer_Loop(u32 Time)
{
	Vector POS_XY_RC;
	Vector Outer_Output;
	float Z_Angle_Change;
	//-------------预先处理-------------------------------------------------------------------//
	if(Control_Para.IsLock == True) 
	{
		Control_Para.POS_Outer_PID_x.Rst_I();
		Control_Para.POS_Outer_PID_y.Rst_I();
		Control_Para.POS_Outer_PID_z.Rst_I();

		Control_Para.Home = Position.Position_xyz;
		Control_Para.POS_Outer_PID_x.Setpoint = Control_Para.Home.x;		
		Control_Para.POS_Outer_PID_y.Setpoint = Control_Para.Home.y;	
		Control_Para.POS_Outer_PID_z.Setpoint = Control_Para.Home.z;	
		return;
	}
	//实时记录姿态模式下，飞行器高度，以应对在飞行中由姿态模式切换到定高模式
	if(Control_Para.Mode == ATT) 
	{
		Control_Para.POS_Outer_PID_x.Setpoint = Position.Position_xyz.x;
		Control_Para.POS_Outer_PID_y.Setpoint = Position.Position_xyz.y;
		Control_Para.POS_Outer_PID_z.Setpoint = Position.Position_xyz.z;
		Control_Para.POS_Outer_PID_x.Rst_I();
		Control_Para.POS_Outer_PID_y.Rst_I();
		Control_Para.POS_Outer_PID_z.Rst_I();
		return;
	}
	
	if(Control_Para.Mode == ALT) 
	{
		Control_Para.POS_Outer_PID_x.Rst_I();
		Control_Para.POS_Outer_PID_y.Rst_I();
	}
	else if(Control_Para.Mode == POS) //XY控制
	{
		//无头\有头模式转换
		if(Control_Para.Head_Mode == HEAD)
			Z_Angle_Change = Control_Para.Home_Z_Angle;
		else
			Z_Angle_Change = Attitude.Angle->z;
		// x 输出选择 定点或遥控
		PWM_In_POS Position_X_Control_Choose = PWM_In.POS_Judge(PWM_RC_L_R);
		// y 输出选择 定点或遥控
		PWM_In_POS Position_Y_Control_Choose = PWM_In.POS_Judge(PWM_RC_F_B);
		
		if(Position_X_Control_Choose != PWM_In_Mid)
		{
			POS_XY_RC.x = ((PWM_RC_L_R - PWM_RC_MID)/PWM_RC_RANGE*2*POS_SPEED_SET_MAX_XY); //速度控制量取值	
		}
		else
			POS_XY_RC.x = 0;
		
		if(Position_Y_Control_Choose != PWM_In_Mid)
		{
			POS_XY_RC.y = ((PWM_RC_F_B - PWM_RC_MID)/PWM_RC_RANGE*2*POS_SPEED_SET_MAX_XY);	//速度控制量取值
		}
		else
			POS_XY_RC.y = 0;
		POS_XY_RC = Math.XY_Coordinate_Rotate(POS_XY_RC.x,POS_XY_RC.y,Z_Angle_Change);//控制量坐标系转换	
		
		
		//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		//--------------pid控制------------------------------------------------------------------//
		// x PID计算
		Control_Para.POS_Outer_PID_x.Setpoint = Math.Constrain(Control_Para.POS_Outer_PID_x.Setpoint,	Control_Para.Home.x + POS_POS_SET_MAX_XY,Control_Para.Home.x - POS_POS_SET_MAX_XY);//
		Control_Para.POS_Outer_PID_x.Feedback = Math.Constrain(Position.Position_xyz.x,Control_Para.Home.x + POS_POS_FEEBACK_MAX_XY,Control_Para.Home.x - POS_POS_FEEBACK_MAX_XY);
		Outer_Output.x = Math.Constrain(Control_Para.POS_Outer_PID_x.Cal_PID_POS(Time),POS_SPEED_SET_MAX_XY,-POS_SPEED_SET_MAX_XY);
		//--------------输出处理------------------------------------------------------------------//
		// x 输出选择 定点或遥控
		if(POS_XY_RC.x != 0)
		{
			Control_Para.POS_Outer_PID_x.Setpoint = Position.Position_xyz.x; //速度控制下当前距离为目标距离 == 无距离控制
			Control_Para.POS_Inner_PID_x.Setpoint = (1 - POS_FILTER_SPEED)*Control_Para.POS_Inner_PID_x.Setpoint + POS_FILTER_SPEED * POS_XY_RC.x; //速度控制量取值
		}
		else
		{
			Control_Para.POS_Inner_PID_x.Setpoint = (1 - POS_FILTER_SPEED)*Control_Para.POS_Inner_PID_x.Setpoint + POS_FILTER_SPEED * Outer_Output.x;
		}	
		//YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
		//--------------pid控制------------------------------------------------------------------//
		// y PID计算
		Control_Para.POS_Outer_PID_y.Setpoint = Math.Constrain(Control_Para.POS_Outer_PID_y.Setpoint,	Control_Para.Home.y + POS_POS_SET_MAX_XY,Control_Para.Home.y - POS_POS_SET_MAX_XY);//
		Control_Para.POS_Outer_PID_y.Feedback = Math.Constrain(Position.Position_xyz.y,Control_Para.Home.y + POS_POS_FEEBACK_MAX_XY,Control_Para.Home.y - POS_POS_FEEBACK_MAX_XY);
		Outer_Output.y = Math.Constrain(Control_Para.POS_Outer_PID_y.Cal_PID_POS(Time),POS_SPEED_SET_MAX_XY,-POS_SPEED_SET_MAX_XY);
		//--------------输出处理------------------------------------------------------------------//
		// y 输出选择 定点或遥控
		if(POS_XY_RC.y != 0)
		{
			Control_Para.POS_Outer_PID_y.Setpoint = Position.Position_xyz.y;	//速度控制下当前距离为目标距离 == 无距离控制
			Control_Para.POS_Inner_PID_y.Setpoint = (1 - POS_FILTER_SPEED)*Control_Para.POS_Inner_PID_y.Setpoint + POS_FILTER_SPEED * POS_XY_RC.y;	//速度控制量取值
		}
		else
		{
			Control_Para.POS_Inner_PID_y.Setpoint = (1 - POS_FILTER_SPEED)*Control_Para.POS_Inner_PID_y.Setpoint + POS_FILTER_SPEED * Outer_Output.y;
		}		
	}
	
	if(Control_Para.Mode == ALT || Control_Para.Mode == POS) //Z控制
	{
		//ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ
		//--------------pid控制------------------------------------------------------------------//
		// Z PID计算
		Control_Para.POS_Outer_PID_z.Setpoint = Math.Constrain(Control_Para.POS_Outer_PID_z.Setpoint,	Control_Para.Home.z + POS_POS_SET_MAX_Z,Control_Para.Home.z);// 飞行高度限幅  姿态模式不可飞高！姿态模式切换到定高模式会有跳变危险！
		Control_Para.POS_Outer_PID_z.Feedback = Math.Constrain(Position.Position_xyz.z,Control_Para.Home.z + POS_POS_FEEBACK_MAX_Z,Control_Para.Home.z);
		Outer_Output.z = Math.Constrain(Control_Para.POS_Outer_PID_z.Cal_PID_POS(Time),POS_SPEED_SET_MAX_Z,-POS_SPEED_SET_MAX_Z);
		//--------------输出处理------------------------------------------------------------------//
		// Z 输出选择 悬停或遥控
		PWM_In_POS Position_Z_Control_Choose = PWM_In.POS_Judge(PWM_RC_D_U);
		if(Position_Z_Control_Choose != PWM_In_Mid)
		{
			Control_Para.POS_Outer_PID_z.Setpoint = Position.Position_xyz.z;
			Control_Para.POS_Inner_PID_z.Setpoint = (1 - POS_FILTER_SPEED)*Control_Para.POS_Inner_PID_z.Setpoint + POS_FILTER_SPEED * ((PWM_RC_D_U - PWM_RC_MID)/PWM_RC_RANGE*2*POS_SPEED_SET_MAX_Z);
		}
		else
		{
			Control_Para.POS_Inner_PID_z.Setpoint = (1 - POS_FILTER_SPEED)*Control_Para.POS_Inner_PID_z.Setpoint + POS_FILTER_SPEED * Outer_Output.z;
		}
	}
	
}


