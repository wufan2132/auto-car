#ifndef __SYS_STATE_H__
#define __SYS_STATE_H__
#include "Board.h"

extern struct SystemState_
{
	void (*Updata)(u16 Time);
}SystemState;



#endif
