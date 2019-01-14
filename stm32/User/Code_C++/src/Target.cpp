#include "Target.h"

#define DEBUG
void Target_ :: Run(void)
{

	uint64_t Time_Enter = SystemTime.Now_US();

	if(Time_Enter >= Time_Store + Cycle)
	{
		(*Target)(CycleMS);
#ifdef DEBUG
		Time_Need = SystemTime.Now_US() - Time_Enter;
		Frequent = Time_Enter - Time_Store;
#endif
		Time_Store = Time_Enter;
	}
}

