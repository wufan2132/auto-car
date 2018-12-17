#include "Interpolating.h"


Interpolating::Interpolating()
{
}


Interpolating::~Interpolating()
{
}


void Interpolating::Spline2D(const VectorXf& point_x, const VectorXf& point_y, Spline_Out& csp, float spacing){
	int len = point_x.rows();

	cal_s(point_x, point_y, csp.s);

	spline(csp.s, point_x, csp.sx);
	spline(csp.s, point_y, csp.sy);

	cout << "sx" << endl;
	cout << csp.sx << endl;
	cout << "sy" << endl;
	cout << csp.sy << endl;
	int size = csp.s(len - 1)/spacing;
	VectorXf s_step = VectorXf::LinSpaced(size, 0, csp.s(len - 1));
	//VectorXf s_step = csp.s;
	//cout << "s_step" << endl;
	//cout << s_step << endl;
	MatrixXf xout, yout;
	cal_position(s_step, csp.sx, csp.sy, xout, yout);

	cal_yaw(xout, yout, csp.yaw);
	cal_curvature(xout, yout, csp.curvature);
	//cout << "yaw" << endl;
	//cout << yaw << endl;
	//cout << "curvature" << endl;
	//cout << curvature << endl;
	csp.x = xout.row(0);
	csp.y = yout.row(0);
}

void Interpolating::cal_s(const VectorXf& x, const VectorXf& y, VectorXf& s){
	float dx, dy;
	int len = x.rows();
	s.resizeLike(x);
	s(0) = 0;
	for (int i = 1; i < len; i++)
	{
		dx = x(i) - x(i-1);
		dy = y(i) - y(i - 1);
		s(i) = s(i - 1) + sqrt(dx*dx + dy*dy);
	}
}

void Interpolating::spline(const VectorXf& x, const VectorXf& y, MatrixXf& sp){
	int len = x.rows();
	VectorXf hs(len-1);
	for (int i = 0; i < len-1; i++)
		hs(i) = x(i + 1) - x(i);
	//cout << hs << endl;
	//生成系数矩阵A
	MatrixXf A = MatrixXf::Zero(len, len);
	A(0, 0) = 1;
	for (int i = 0; i < len - 1; i++)
	{
		if (i!=len-2)
			A(i + 1, i + 1) = 2 * (hs(i) + hs(i + 1));
		A(i + 1, i) = hs(i);
		A(i, i + 1) = hs(i);
	}
	A(0, 1) = 0;
	A(len-1, len - 2) = 0;
	A(len - 1, len - 1) = 1;
	//cout << A << endl;
	/*生成系数矩阵B*/
	VectorXf B(len);
	for (int i = 0; i < len - 2; i++)
		B(i + 1) = 3 * (y(i + 2) - y(i + 1)) / hs(i + 1) - 3 * (y(i + 1) - y(i)) / hs(i);
	B(0) = 0;
	B(len-1) = 0;
	//cout << B<<endl;
	/*求解 Ac=B*/
	VectorXf c = A.colPivHouseholderQr().solve(B);
	/*生成d b*/
	VectorXf d(len);
	VectorXf b(len);
	for (int i = 0; i < len - 1; i++)
	{
		d(i) = (c(i + 1) - c(i)) / (3 * hs(i));
		b(i) = (y(i + 1) - y(i)) / hs(i) - hs(i)*(c(i + 1) + 2 * c(i)) / 3;
	}
	d(len - 1) = 0;
	b(len - 1) = 0;
	sp.resize(6, len);
	sp.row(0) = x.transpose();
	sp.row(1) = y.transpose();
	sp.row(2) = y.transpose();
	sp.row(3) = b.transpose();
	sp.row(4) = c.transpose();
	sp.row(5) = d.transpose();

	//cout<<sp<<endl;
}

void Interpolating::cal_position(const VectorXf& step, const MatrixXf& sx, const MatrixXf&sy,
	MatrixXf& xout, MatrixXf& yout){
	int len = step.rows();
	int idx;
	float dx, dy;
	VectorXf sx_X = sx.row(0);
	xout.resize(3, len);
	yout.resize(3, len);
	for (int i = 0; i < len; i++)
	{
		idx = search_index(step(i), sx_X);
		cout << sx.row(0) << endl;
		cout << "step:" << step(i) << "  idx" << idx << endl;
		dx = step(i) - sx(0, idx);
		xout(0, i) = sx(2, idx) + sx(3, idx) * dx + sx(4, idx) * dx * dx + sx(5, idx) * dx * dx * dx;
		xout(1, i) = sx(3, idx) + 2 * sx(4, idx) * dx + 3 * sx(5, idx)*dx*dx;
		xout(2, i) = 2 * sx(4, idx) + 6 * sx(5, idx) * dx;
		dy = step(i) - sy(0, idx);
		yout(0, i) = sy(2, idx) + sy(3, idx) * dy + sy(4, idx) * dy * dy + sy(5, idx) * dy * dy * dy;
		yout(1, i) = sy(3, idx) + 2 * sy(4, idx) * dy + 3 * sy(5, idx)*dy*dy;
		yout(2, i) = 2 * sy(4, idx) + 6 * sy(5, idx) * dy;
	}
	//cout << "xout" << endl;
	//cout << xout << endl;
	//cout << "yout" << endl;
	//cout << yout << endl;
}

void Interpolating::cal_yaw(const MatrixXf& xout, const MatrixXf& yout, VectorXf& yaw){
	int len = xout.cols();
	yaw.resize(len);
	for (int i = 0; i < len; i++){
		yaw(i) = atan(yout(1, i) / xout(1, i));
	}
}

void Interpolating::cal_curvature(const MatrixXf& xout, const MatrixXf& yout, VectorXf& curvature){
	int len = xout.cols();
	curvature.resize(len);
	for (int i = 0; i < len; i++){
		curvature(i) = (yout(2, i)*xout(1, i) - yout(1, i)*xout(2, i)) / (xout(1, i)*xout(1, i) + yout(1, i)*yout(1, i));
	}
}

int Interpolating::search_index(float st, VectorXf& s){
	
	static int pos = 0;
	if (st == 0)
	{
		pos = 0;
		return 0;
	}
	int len = s.rows();
	if (st < 0) return 0;
	else if (st >= s(len - 1)) return len - 1;
	
	while (st >= s(pos+1))
	{
		pos++;
	}
	return pos;


	//二分查找
	//int start = 0,mid,end = s.rows();
	//while (start < end)
	//{
	//	mid = (start + end) / 2;
	//	if (st>s(mid))
	//		start = mid;
	//	else if (st < mid)
	//		end = mid;
	//	else
	//		return mid;
	//}
	//return (start + end) / 2;
}