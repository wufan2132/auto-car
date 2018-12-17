#ifndef __ROCKER_H__
#define __ROCKER_H__

struct Para_
{

};

class Rocker_
{
	public:
		Rocker_(void)
		{
			Pitch = 1500;
			Roll = 1500;
			Yaw = 1500;
			Throttle = 1200;
		}

		float Pitch;
		float Roll;
		float Yaw;
		float Throttle;
};

#endif

