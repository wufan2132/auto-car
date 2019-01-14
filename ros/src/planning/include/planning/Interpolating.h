#pragma once
#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include <math.h>
#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "yaml-cpp/yaml.h"

using namespace std;
using namespace Eigen;


class Spline_Out;

class Interpolating_conf{
public:
	double Spline_space;
};

class Interpolating
{
public:
	Interpolating(YAML::Node yaml_conf);
	~Interpolating();
	//

	Spline_Out* process(const car_msgs::trajectory& trajectory_in, car_msgs::trajectory& trajectory_out);

	//static function
	/*************三次样条插值***********/
	//x,y ���������
	//csp ������ݶ���
	//spacing ��ֵ����λm
	static void Spline2D(const VectorXf& x, const VectorXf& y, Spline_Out& csp, float spacing = 0.5);
	
	Interpolating_conf conf;
	//tool
	static float curvature(float dx, float ddx, float dy, float ddy);
	static float yaw(float dx, float dy);

private:
	static void cal_s(const VectorXf& x, const VectorXf& y, VectorXf& s);
	static void spline(const VectorXf& x, const VectorXf& y, MatrixXf& sp);

	static void cal_position(const VectorXf& step, const MatrixXf& sx, const MatrixXf& sy,
		MatrixXf& xout, MatrixXf& yout);
	static void cal_yaw(const MatrixXf& xout, const MatrixXf& yout, VectorXf& yaw);
	static void cal_curvature(const MatrixXf& xout, const MatrixXf& yout, VectorXf& curvature);
	static int search_index(float st, VectorXf& s);

	
};

class Spline_Out{
public:
	int length;
	VectorXf s;
	MatrixXf sx;
	MatrixXf sy;
	VectorXf x;
	VectorXf y;
	VectorXf yaw;
	VectorXf curvature;
};