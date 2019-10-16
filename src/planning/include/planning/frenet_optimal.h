#pragma once
#include <Eigen/Dense>
#include <vector>
#include<iostream>
#include <math.h>
#include "planning/Interpolating.h"
#include "planning/Fitting.h"

class car_status;

class frenet_optimal
{
public:
	frenet_optimal();
	~frenet_optimal();
	void process(Spline_Out& csp, car_status& status);

};

// class car_status
// {
// public:
// 	car_status();
// 	~car_status();
// 	float x_s;
// 	float x_speed;
// 	float x_acc;
// 	float y_s;
// 	float y_speed;
// 	float y_acc;
	
// };


