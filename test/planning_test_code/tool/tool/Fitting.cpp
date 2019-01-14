#include "Fitting.h"


Fitting::Fitting()
{
}


Fitting::~Fitting()
{
}


VectorXf Fitting::quartic4_polynomial(float now_s, float now_speed, float now_acc, float aim_speed, float aim_acc, float t){
	Matrix2f A;
	Vector2f B;
	A << 3 * t * t, 4 * t*t*t, 6 * t, 12 * t*t;
	B << aim_speed - now_speed - now_acc*t, aim_acc - now_acc;
	VectorXf QP(5);
	QP.head(3) << now_s, now_speed, now_acc / 2;
	QP.tail(2) = A.colPivHouseholderQr().solve(B);
	//cout << "QP" << endl;
	//cout << QP << endl;
	return QP;
}

VectorXf Fitting::quintic5_polynomial(float now_hs, float now_hs_d, float now_hs_dd, float aim_hs, float aim_hs_d, float aim_hs_dd, float t){
	Matrix3f A;
	Vector3f B;
	A << t*t*t, t*t*t*t, t*t*t*t*t, 3 * t*t, 4 * t*t*t, 5 * t*t*t*t, 6 * t, 12 * t*t, 20 * t*t*t;
	B << aim_hs - now_hs - now_hs_d*t - now_hs_dd*t*t / 2, aim_hs_d - now_hs_d - now_hs_dd*t, aim_hs_dd - now_hs_dd;
	VectorXf QP(6);
	QP.head(3) << now_hs, now_hs_d, now_hs_dd / 2;
	QP.tail(3) = A.colPivHouseholderQr().solve(B);
	cout << "QP" << endl;
	cout << QP << endl;
	return QP;
}

void Fitting::cal_point_quartic4(const VectorXf& QP, const VectorXf& t, MatrixXf& St){
	int len = t.rows();
	St.resize(len, 4);
	for (int i = 0; i < len; i++){
		St.row(i) << QP(0) + QP(1) * t(i) + QP(2) * t(i)*t(i) + QP(3) * t(i)*t(i)*t(i) + QP(4) * t(i)*t(i)*t(i)*t(i),
			QP(1) + 2 * QP(2) * t(i) + 3 * QP(3) * t(i)*t(i) + 4 * QP(4) * t(i)*t(i)*t(i),
			2 * QP(2) + 6 * QP(3) * t(i) + 12 * QP(4) * t(i)*t(i),
			6 * QP(3) + 24 * QP(4) * t(i);
	}
}

void Fitting::cal_point_quintic5(const VectorXf& QP, const VectorXf& t, MatrixXf& Xt){
	int len = t.rows();
	Xt.resize(len, 4);
	for (int i = 0; i < len; i++){
		Xt.row(i) << QP(0) + QP(1) * t(i) + QP(2) * t(i)*t(i) + QP(3) * t(i)*t(i)*t(i) + QP(4) * t(i)*t(i)*t(i)*t(i) + QP(5) * t(i)*t(i)*t(i)*t(i)*t(i),
			QP(1) + 2 * QP(2) * t(i) + 3 * QP(3) * t(i)*t(i) + 4 * QP(4) * t(i)*t(i)*t(i) + 5 * QP(5) * t(i)*t(i)*t(i)*t(i),
			2 * QP(2) + 6 * QP(3) * t(i) + 12 * QP(4) * t(i)*t(i) + 20 * QP(5) * t(i)*t(i)*t(i),
			6 * QP(3) + 24 * QP(4) * t(i) + 60 * QP(5) * t(i)*t(i);
	}
	cout << "Xt" << endl;
	cout << Xt << endl;
}