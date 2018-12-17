#ifndef __COMMON_H__
#define __COMMON_H__
#include "stm32f4xx.h"


typedef enum
{
	False,
	True

}BOOL;
class Vector
{
	public :
		Vector()
		{
			x = 0;
			y = 0;
			z = 0;
		};
		
		Vector(float X_In,float Y_In,float Z_In)
		{
			x = X_In;
			y = Y_In;
			z = Z_In;
		};
	
		float x,y,z;
};



#define BOOL_REVERSE(TMP) { \
if(TMP == True) TMP = False;\
else TMP = True;\
};

#define Enable True
#define Disable False

#endif
