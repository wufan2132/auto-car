#ifndef __ELIPSOID_H__
#define __ELIPSOID_H__
#include "arm_math.h"
#include "Common.h"
class Elipsoid_
{
	public:
		Elipsoid_(void)
		{
			a = 1;b = 1;c = 1;d = 1;e = 1;f = 1;g = 1;
		};
		void Input(Vector NewValue);
		void Calulate(void);
		float a,b,c,d,e,f,g;
		float Matrix[7][7];
};


#endif
