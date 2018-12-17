#pragma once
#include <Eigen/Dense>
#include <vector>
#include<iostream>
#include <math.h>
using namespace std;
using namespace Eigen;


class Spline_Out;
class Interpolating
{
public:
	Interpolating();
	~Interpolating();

	//static function
	/*************三次样条插值函数***********/
	//x,y 输入点坐标
	//csp 输出数据对象
	//spacing 插值间隔，单位m
	static void Spline2D(const VectorXf& x, const VectorXf& y, Spline_Out& csp, float spacing = 0.5);

private:
	static void cal_s(const VectorXf& x, const VectorXf& y, VectorXf& s);
	static void spline(const VectorXf& x, const VectorXf& y, MatrixXf& sp);

	static void cal_position(const VectorXf& step, const MatrixXf& sx, const MatrixXf&sy,
		MatrixXf& xout, MatrixXf& yout);
	static void cal_yaw(const MatrixXf& xout, const MatrixXf& yout, VectorXf& yaw);
	static void cal_curvature(const MatrixXf& xout, const MatrixXf& yout, VectorXf& curvature);
	static int search_index(float st, VectorXf& s);

	
};

class Spline_Out{
public:
	VectorXf s;
	MatrixXf sx;
	MatrixXf sy;
	VectorXf x;
	VectorXf y;
	VectorXf yaw;
	VectorXf curvature;
};