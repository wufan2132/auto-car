#pragma once
#include <Eigen/Dense>
#include <vector>
#include<iostream>


using namespace Eigen;
using namespace std;


class car_status;

class Fitting
{
public:
	Fitting();
	~Fitting();
	/*纵向四次多项式拟合*/
	// 用当前时刻xs，vxs，axs与目标时刻的速度vxe、加速度axe，时刻 两个点拟合4次多项式
	static VectorXf quartic4_polynomial(float now_s, float now_speed, float now_acc, float aim_speed, float aim_acc, float t);
	/*************** St 排列***********************/
	/*         s0,s_d0,s_dd0,s_ddd0           */
	/*         s1,s_d1,s_dd1,s_ddd1           */
	/*         ....................           */
	/*         sN,s_dN,s_ddN,s_dddN           */
	static void cal_point_quartic4(const VectorXf& QP, const VectorXf& t, MatrixXf& St);
	static void cal_point_quartic4(const VectorXf& QP, double t, VectorXf& Xt);
	static double cal_point_quartic4(const VectorXf& QP, double t);
	/*横向五次多项式拟合*/
	static VectorXf quintic5_polynomial(float now_hs, float now_hs_d, float now_hs_dd, float aim_hs, float aim_hs_d, float aim_hs_dd, float t);
	static void cal_point_quintic5(const VectorXf& QP, const VectorXf& t, MatrixXf& Xt);
	static void cal_point_quintic5(const VectorXf& QP, double t, VectorXf& Xt);
	static double cal_point_quintic5(const VectorXf& QP, double t);
	/*N多项式优化*/
	static void gradient_descent(const VectorXf& y,VectorXf& QP, int dime);
	static void gradient_descent_optimizer(VectorXf& y,int dime = 2);
	static void newton(const VectorXf& y,VectorXf& QP);
};
