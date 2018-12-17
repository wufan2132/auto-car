#ifndef __TARGET_H__
#define __TARGET_H__
#include "Time.h"

typedef void (*pFun)(u16 Time);

class Target_
{
	public:
		Target_(pFun Aim, int Cycle_Time)
		{
			Cycle = Cycle_Time - 1;
			CycleMS = Cycle_Time / 1000;
			Time_Store = 0;
			Target = Aim;
		};
		void Run(void);		
		u32 Frequent;     //实际执行周期
		u32 Time_Need;    //执行花费时间

	private:
		uint64_t Time_Store;  //记忆上一次执行的时间
		u32 Cycle;        //执行周期
		u32 CycleMS;
		pFun Target;
};

#endif
