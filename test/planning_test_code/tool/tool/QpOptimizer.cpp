#include "QpOptimizer.h"

int point_in_line = 15;
const int  link_order = 3;
const double limit_R = 2;
const double K_order1 = 1;
const double K_order2 = 2;
const double K_order3 = 10;

QpOptimizer::QpOptimizer(list<Point *>& path, int norder)
{
	order = norder+1;

	VectorXd T0_(6), T1_(6), dT0_(6), dT1_(6), ddT0_(6), ddT1_(6);
	T0_ << 1, 0, 0, 0, 0, 0;
	T1_ << 1, 1, 1, 1, 1, 1;
	dT0_ << 0, 1, 0, 0, 0, 0;
	dT1_ << 0, 1, 2, 3, 4, 5;
	ddT0_ << 0, 0, 2, 0, 0, 0;
	ddT1_ << 0, 0, 2, 6, 12, 20;
	T0.resize(order);
	T1.resize(order);
	dT0.resize(order);
	dT1.resize(order);
	ddT0.resize(order);
	ddT1.resize(order);
	T0 = T0_.head(order);
	T1 = T1_.head(order);
	dT0 = dT0_.head(order);
	dT1 = dT1_.head(order);
	ddT0 = ddT0_.head(order);
	ddT1 = ddT1_.head(order);

	point_num = path.size();
	if (point_in_line == 1)
		point_in_line = 2;
	line_num = ceil((double)(point_num-1) / (double)(point_in_line-1));
	qp_size = order * 2 * line_num;
	constraint_size = (line_num - 1) * 2 * link_order + point_num * 2;
}


QpOptimizer::~QpOptimizer()
{
	delete g;
	delete matH;
	//约束
	delete A;
	delete lb;
	delete ub;
	delete lbA;
	delete ubA;
	//输出
	delete res;
}

VectorXd QpOptimizer::T(double t){
	VectorXd vec(order);
	double x = 1;
	for (int i = 0; i < order; i++){
		vec(i) = x;
		x *= t;
	}
	return vec;
}
VectorXd QpOptimizer::dT(double t){
	VectorXd vec_(6), vec(order);
	vec_ << 0, 1, 2 * t, 3 * t*t, 4 * t*t*t, 5 * t*t*t*t;
	vec = vec_.head(order);
	return vec;
}
VectorXd QpOptimizer::ddT(double t){
	VectorXd vec_(6), vec(order);
	vec_ << 0, 0, 2, 6*t,12*t*t, 20*t*t*t;
	vec = vec_.head(order);
	return vec;
}

void QpOptimizer::addkennel(){
	matH = new MatrixXd(qp_size, qp_size);
	matH->setZero();
	//
	for (int i = 0; i < qp_size; i++){
		(*matH)(i,i) = 0.000000001;
	}
	//一阶导数约束
	for (int i = 0; i < line_num - 1; i++){
		(*matH)(order * i + 1, order * i + 1) = 2.0*K_order1;
		(*matH)(order * i + 1 + qp_size / 2, order * i + 1 + qp_size / 2) = 2.0*K_order1;
	}

	//二阶导数约束
	for (int i = 0; i < line_num - 1; i++){
		(*matH)(order * i + 2, order * i + 2) = 4.0*K_order2;
		(*matH)(order * i + 2 + qp_size / 2, order * i + 2 + qp_size / 2) = 4.0*K_order2;
	}

	//三阶导数约束
	for (int i = 0; i < line_num - 1; i++){
		(*matH)(order*i + 3, order*i + 3) = 36.0*K_order3;
		(*matH)(order * i + 3 + qp_size / 2, order * i + 3 + qp_size / 2) = 36.0*K_order3;
	}
	//cout << "matH:" << endl;
	//cout << *matH << endl;
	//这里因为矩阵是对称的所以不转置了
	H = &(*matH)(0, 0);

	g = new double[qp_size];
	memset(g, 0, qp_size*sizeof(double));
}
void QpOptimizer::addconstraint(list<Point *>& path){
	//A
	int consnum = 0;
	MatrixXd matA(constraint_size, qp_size);
	//位置约束
	for (int i = 0; i < line_num; i++){
		//对于每一条线段
		for (double t = 0; t < 0.999999; t += (double)1 / (double)(point_in_line-1)){
			matA.row(consnum) = VectorXd::Zero(qp_size); //起点与中间点
			matA.row(consnum++).segment(order * i, order) = T(t);
			matA.row(consnum) = VectorXd::Zero(qp_size);
			matA.row(consnum++).segment(order * i + qp_size / 2, order) = T(t);
			//最后一个线段是不完整的
			if (consnum >= 2*(point_num - 1))
				break;
		}
	}
	end_t = (double)(point_num - (line_num - 1) * (point_in_line - 1) - 1) / (double)(point_in_line - 1);
	matA.row(consnum) = VectorXd::Zero(qp_size); //终点
	matA.row(consnum++).segment(qp_size / 2 - order, order) = T(end_t);
	matA.row(consnum) = VectorXd::Zero(qp_size);
	matA.row(consnum++).tail(order) = T(end_t);

	//连接约束1
	for (int i = 0; i < line_num - 1; i++){
		matA.row(consnum) = VectorXd::Zero(qp_size); //x值相等
		matA.row(consnum).segment(order * i, order) = T1;
		matA.row(consnum++).segment(order * (i+1), order) = -T0;
		matA.row(consnum) = VectorXd::Zero(qp_size); //y值相等
		matA.row(consnum).segment(order * i + qp_size / 2, order) = T1;
		matA.row(consnum++).segment(order * (i + 1) + qp_size / 2, order) = -T0;
	}

	//连接约束2
	for (int i = 0; i < line_num - 1; i++){
		matA.row(consnum) = VectorXd::Zero(qp_size); //x一阶导相等
		matA.row(consnum).segment(order * i, order) = dT1;
		matA.row(consnum++).segment(order * (i + 1), order) = -dT0;
		matA.row(consnum) = VectorXd::Zero(qp_size); //y一阶导相等
		matA.row(consnum).segment(order * i + qp_size / 2, order) = dT1;
		matA.row(consnum++).segment(order * (i + 1) + qp_size / 2, order) = -dT0;
	}

	//连接约束3
	if (link_order >= 3){
		for (int i = 0; i < line_num - 1; i++){
			matA.row(consnum) = VectorXd::Zero(qp_size); //x二阶导相等
			matA.row(consnum).segment(order * i, order) = ddT1;
			matA.row(consnum++).segment(order * (i + 1), order) = -ddT0;
			matA.row(consnum) = VectorXd::Zero(qp_size); //y二阶导相等
			matA.row(consnum).segment(order * i + qp_size / 2, order) = ddT1;
			matA.row(consnum++).segment(order * (i + 1) + qp_size / 2, order) = -ddT0;
		}
	}
	if (constraint_size != consnum){
		cerr << "addconstraint: constraint_size error!" << endl;
		return;
	}

	A = new double[constraint_size * qp_size];
	for (int i = 0; i < constraint_size; i++){
		for (int j = 0; j < qp_size; j++){
			A[i*qp_size + j] = matA(i, j);
		}		
	}
	consnum = 0;
	lbA = new double[constraint_size];
	ubA = new double[constraint_size];

	memset(lbA, 0, constraint_size*sizeof(double));
	memset(ubA, 0, constraint_size*sizeof(double));

	for (auto it = path.begin();it!=path.end();it++){
		lbA[consnum] = (*it)->x - limit_R;
		ubA[consnum++] = (*it)->x + limit_R;
		lbA[consnum] = (*it)->y - limit_R;
		ubA[consnum++] = (*it)->y + limit_R;
	}
	//起点与终点不允许有误差
	lbA[0] = path.front()->x;
	ubA[0] = path.front()->x;
	lbA[1] = path.front()->y;
	ubA[1] = path.front()->y;
	lbA[2 * point_num - 2] = path.back()->x;
	ubA[2 * point_num - 2] = path.back()->x;
	lbA[2 * point_num - 1] = path.back()->y;
	ubA[2 * point_num - 1] = path.back()->y;
	//
	lb = nullptr;
	ub = nullptr;
	//lb = new double[qp_size];
	//ub = new double[qp_size];
	//memset(lb, 0, constraint_size*sizeof(double));
	//memset(ub, 0, constraint_size*sizeof(double));

	//for (int i = 0; i < qp_size; i++){
	//	lb[i] = -100000;
	//	ub[i] = 100000;
	//}
	/*预先设置初始值加速运算*/
	xOpt = new double[qp_size];
	memset(xOpt, 0, qp_size*sizeof(double));
	auto it = path.begin();
	for (int i = 0; i < qp_size / 12; i++){
		xOpt[order * i] = (*it)->x;
		xOpt[order * i + qp_size/2] = (*it)->y;
		it++;
	}
	//MatrixXd xqp, yqp;
	//xqp.resize(point_num - 1, order);
	//yqp.resize(point_num - 1, order);
	//for (int i = 0; i< point_num - 1; i++)
	//for (int j = 0; j < order; j++){
	//	xqp(i, j) = xOpt[i * order + j];
	//	yqp(i, j) = xOpt[i * order + j + qp_size / 2];
	//}
	//cout << "xqp:" << endl;
	//cout << xqp << endl;
	//cout << "yqp:" << endl;
	//cout << yqp << endl;
}
void QpOptimizer::getAnswer(MatrixXd& xqp, MatrixXd& yqp){
	//cout << "H:" << endl;
	//printf(H, qp_size, qp_size);

	//cout << "A:" << endl;
	//printf(A, constraint_size, qp_size);
	//
	//cout << "G:" << endl;
	//printf(g, 1, qp_size);
	//cout << endl;
	//cout << "lbA" <<endl;
	//for (int i = 0; i < constraint_size; i++)
	//	cout << lbA[i] << " ";
	//cout << endl;
	//cout << "ubA" << endl;
	//for (int i = 0; i < constraint_size; i++)
	//	cout << ubA[i] << " ";
	//cout << endl;

	QProblem QP(qp_size, constraint_size);
	//设置低输出模式
	Options myOptions;
	myOptions.printLevel = PL_LOW;
	QP.setOptions(myOptions);
	//
	int_t nWSR = qp_size*constraint_size;
	real_t cuptime = 60;
	clock_t start = clock();

	returnValue ret = QP.init(H, g, A, lb, ub, lbA, ubA, nWSR, &cuptime, xOpt);

	int max_recal_time = 5;
	while (ret!= SUCCESSFUL_RETURN){
		cout << "QpOptimizer::getAnswer: recalculate!" << endl;
		ret = QP.hotstart(g, lb, ub, lbA, ubA, nWSR, &cuptime);
		max_recal_time--;
		if (max_recal_time == 0){
			cerr << "QpOptimizer::getAnswer: QPsolve failed!" << endl;
			return;
		}
	}

	clock_t ends = clock();
	cout << "Running Time1 : " << (double)(ends - start) / CLOCKS_PER_SEC << endl;

	res = new double[qp_size];
	QP.getPrimalSolution(res);
	
	cout << "xOpt:"<<endl;
	for (int i = 0; i < qp_size; i++)
		cout << res[i] << ",";
	cout << endl;
	cout << "objVal:" << QP.getObjVal() << endl;
	//
	xqp.resize(line_num, order);
	yqp.resize(line_num, order);
	for (int i = 0; i< line_num; i++)
	for (int j = 0; j < order; j++){
		xqp(i, j) = res[i * order + j];
		yqp(i, j) = res[i * order + j + qp_size/2];
	}
	cout << "xqp:" << endl;
	cout << xqp << endl;
	cout << "yqp:" << endl;
	cout << yqp << endl;
}

void QpOptimizer::printf(real_t* data, int rows, int cols){
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++)
			cout << data[cols * i + j] << " ";
		cout << endl;
	}
}

void QpOptimizer::getpath(MatrixXd& xqp, MatrixXd& yqp, list<Point *>& path){
	path.resize(0);
	for (int i = 0; i < xqp.rows(); i++)
	for (double t = 0; t < 1; t += 0.02){
		double x = xqp.row(i)*T(t);
		double y = yqp.row(i)*T(t);
		if (i == xqp.rows() - 1 && t>end_t){
			return;
		}
		path.push_back(new Point((int)x, (int)y));
	}
}