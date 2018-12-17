#pragma once
#include <qpOASES.hpp>
#include <Eigen/Dense>
#include<iostream>
#include "point.h"
#include <math.h>
#include <time.h>
using namespace std;
using namespace Eigen;
using namespace qpOASES;
class QpOptimizer
{
public:
	QpOptimizer(list<Point *>& path, int norder=5);
	~QpOptimizer();
	void addkennel();
	void addconstraint(list<Point *>& path);
	void getAnswer(MatrixXd& xqp, MatrixXd& yqp);
	void printf(real_t* data, int rows, int cols);
	void getpath(MatrixXd& xqp, MatrixXd& yqp, list<Point *>& path);
	//参数
	int order;
	int point_num;
	int line_num;
	int qp_size;
	int constraint_size;
	//
	VectorXd T0;
	VectorXd T1;
	VectorXd dT0;
	VectorXd dT1;
	VectorXd ddT0;
	VectorXd ddT1;
	VectorXd T(double t);
	VectorXd dT(double t);
	VectorXd ddT(double t);
	//优化目标
	real_t* H;
	real_t* g;
	MatrixXd* matH;
	//约束
	real_t* A;
	real_t* lb;
	real_t* ub;
	real_t* lbA;
	real_t* ubA;
	//输出
	real_t* res;
	real_t* xOpt;
	//其他参数
	double end_t;
};

///* Setup data of first QP. */
//real_t H[2 * 2] = { 2.0, 0.0, 2.0, 0.0 };
//real_t A[1 * 2] = { 1.0, 1.0 };
//real_t g[2] = { -2.0, -4.0 };
//real_t lb[2] = { 0, 0 };
//real_t ub[2] = { 100, 100 };
//real_t lbA[1] = { 1 };
//real_t ubA[1] = { 1 };
///* Setup data of second QP. */
////real_t g_new[2] = { 1.0, 1.5 };
////real_t lb_new[2] = { 0.0, -1.0 };
////real_t ub_new[2] = { 5.0, -0.5 };
////real_t lbA_new[1] = { -2.0 };
////real_t ubA_new[1] = { 1.0 };
///* Setting up QProblem object. */
//QProblem example(2, 1);
///* Solve first QP. */
//int_t nWSR = 10;
//example.init(H, g, A, lb, ub, lbA, ubA, nWSR);
/////* Solve second QP. */
////nWSR = 10;
////example.hotstart(g_new, lb_new, ub_new, lbA_new, ubA_new, nWSR);
/////* Get and print solution of second QP. */
//real_t xOpt[2];
//example.getPrimalSolution(xOpt);
//printf("\n xOpt = [ %e, %e ]; objVal = %e\n\n",
//	xOpt[0], xOpt[1], example.getObjVal());