#include "planning/Fitting.h"


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
	//cout << "QP" << endl;
	//cout << QP << endl;
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

void Fitting::cal_point_quartic4(const VectorXf& QP, double t, VectorXf& St){
	St.resize(4);

	St << QP(0) + QP(1) * t + QP(2) * t*t + QP(3) * t*t*t + QP(4) * t*t*t*t,
		QP(1) + 2 * QP(2) * t + 3 * QP(3) * t*t + 4 * QP(4) * t*t*t,
		2 * QP(2) + 6 * QP(3) * t + 12 * QP(4) * t*t,
		6 * QP(3) + 24 * QP(4) * t;
}

double Fitting::cal_point_quartic4(const VectorXf& QP, double t){
	return QP(0) + QP(1) * t + QP(2) * t*t + QP(3) * t*t*t + QP(4) * t*t*t*t;
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
	//cout << "Xt" << endl;
	//cout << Xt << endl;
}

void Fitting::cal_point_quintic5(const VectorXf& QP, double t, VectorXf& Xt){
	Xt.resize(4);
	Xt << QP(0) + QP(1) * t + QP(2) * t*t + QP(3) * t*t*t + QP(4) * t*t*t*t + QP(5) * t*t*t*t*t,
		QP(1) + 2 * QP(2) * t + 3 * QP(3) * t*t + 4 * QP(4) * t*t*t + 5 * QP(5) * t*t*t*t,
		2 * QP(2) + 6 * QP(3) * t + 12 * QP(4) * t*t + 20 * QP(5) * t*t*t,
		6 * QP(3) + 24 * QP(4) * t + 60 * QP(5) * t*t;
}

double Fitting::cal_point_quintic5(const VectorXf& QP, double t){
	return QP(0) + QP(1) * t + QP(2) * t*t + QP(3) * t*t*t + QP(4) * t*t*t*t + QP(5) * t*t*t*t*t;
}

void Fitting::gradient_descent(const VectorXf& y,VectorXf& QP,int dime){
	// /***********参数**************/
	// const static float e = 0.01;
	// const static float alpha = 0.001;
	// /****************************/
	// QP.resize(dime+1);
	// //set initvalue
	// QP.setZero();
	// int len = y.rows();
	// //cal_f
	// VectorXf df(dime+1);
	// df.setZero();
	// //计算梯度
	// float x;
	// while(1){
	// 	for(int i=0,x=0;i<len ;i++,x+=1){
	// 		float f = 0;
	// 		float i_mi = 1;
	// 		for(int j=0;j<dime+1;j++){
	// 			f += QP(j)*i_mi;
	// 			i_mi *= x;
	// 		}
	// 		f -= y(i);
	// 		i_mi = 1;
	// 		for(int j=0;j<dime+1;j++){
	// 			df(j) += 2*f*i_mi;
	// 			i_mi *= x;
	// 		}
	// 	}
	// 	QP = QP - alpha * df;
	// 	cout<<"df"<<endl;
	// 	cout<<df<<endl;
	// 	if(df.norm()<e)
	// 		break;
	// }
}
void Fitting::newton(const VectorXf& y,VectorXf& QP){
	QP.resize(3);
	VectorXf df(3);
	df.setZero();
	MatrixXf ddf(3,3);
	ddf.setZero();
	int len = y.rows();
	while(1){
		for(int i=0;i<len;i++){
			float f = QP(0) +  QP(0)*i + QP(0)*i*i - y(i);
			df(0) += 2*f;
			df(1) += 2*f*i;
			df(2) += 2*f*i*i;
			ddf(0,0) += 2;
			ddf(0,1) += 2*i;
			ddf(0,2) += 2*i*i;
			ddf(1,0) += 2*i;
			ddf(1,1) += 2*i*i;
			ddf(1,2) += 2*i*i*i;
			ddf(2,0) += 2*i*i;
			ddf(2,1) += 2*i*i*i;
			ddf(2,2) += 2*i*i*i*i;
		}
		QP = QP - ddf.colPivHouseholderQr().solve(df);
		cout<<df.norm()<<endl;
		if(df.norm()<0.01)
	  		break;
	}
}
void Fitting::gradient_descent_optimizer(VectorXf& y,int dime){
	int len = y.rows();
	VectorXf QP;
	newton(y,QP);
	cout<<"QP"<<endl;
	cout<<QP<<endl;
	y.setZero();
	for(int i=0;i<len;i++){
		for(int j=0;j<dime+1;j++){
			y(i) += QP(j)*pow(i,j);
		}	
	}
}

	// VectorXf C(2*dime+1);
	// VectorXf T(dime+1);
	// C.setZero();
	// T.setZero();
	// VectorXf X = VectorXf::LinSpaced(len, 0, 10);
	// for(int j=0;j<2*dime+1;j++){
	// 	for(int i=0;i<len;i++){
	// 		C(j)+=pow(X(i),j);
	// 		if(j<dime+1)
	// 			T(j)+=y(i)*pow(X(i),j);
	// 	}
	// }
	// MatrixXf S(dime+1,dime+1);
	// for(int i=0;i<dime+1;i++)
	// 	S.row(0) = C.segment(i,dime+1);
	// VectorXf QP = S.colPivHouseholderQr().solve(T);