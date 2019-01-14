#include<iostream>
#include <Eigen/Dense>
#include "Interpolating.h"
#include "Fitting.h"
#include "BMP.h"
#include "A_star.h"
#include "road.h"
#include "QpOptimizer.h"
#include <qpOASES.hpp>
using namespace std;
using namespace Eigen;
using namespace qpOASES;

//int main(){
//
//
//	///* Setup data of first QP. */
//	//real_t H[3 * 3] = { 1, 0, 0, 
//	//					0, 1, 0,
//	//					0, 0, 1, };
//	//real_t A[2 * 3] = { 1,2,-1,
//	//					1,-1,1 };
//	//real_t g[3] = { 0,0,0 };
//	//real_t lb[3] = { -100, -100,-100 };
//	//real_t ub[3] = { 100, 100,100 };
//	//real_t lbA[2] = { 4, -2 };
//	//real_t ubA[2] = { 4, -2 };
//	///* Setup data of second QP. */
//	////real_t g_new[2] = { 1.0, 1.5 };
//	////real_t lb_new[2] = { 0.0, -1.0 };
//	////real_t ub_new[2] = { 5.0, -0.5 };
//	////real_t lbA_new[1] = { -2.0 };
//	////real_t ubA_new[1] = { 1.0 };
//	///* Setting up QProblem object. */
//	//QProblem example(3, 0);
//	///* Solve first QP. */
//	//int_t nWSR = 100;
//	//example.init(H, g, A, lb, ub, lbA, ubA, nWSR);
//	/////* Solve second QP. */
//	////nWSR = 10;
//	////example.hotstart(g_new, lb_new, ub_new, lbA_new, ubA_new, nWSR);
//	/////* Get and print solution of second QP. */
//	//real_t xOpt[3];
//	//example.getPrimalSolution(xOpt);
//	//cout << "xOpt:" << endl;
//	//for (int i = 0; i < 3; i++)
//	//	cout << xOpt[i] << ",";
//	//cout << endl;
//	//cout << "objVal:" << example.getObjVal() << endl;
//
//	system("pause");
//	return 0;
//
//}

//
const double origin_road_width = 55;
const double scale = 0.2;

//矩阵的按元素赋值
int main()
{
	//原图信息
	BMP origin_img;
	origin_img.Read24BMP("road.bmp");
	Point origin_start(origin_img.convert_from_huatu(889, 102));
	Point origin_end(origin_img.convert_from_huatu(133, 698));//(836, 430))
	//低分辨图
	BMP img;
	origin_img.compressionBMP(img, scale);
	Point start = img.point_scale(origin_start, scale);
	Point end = img.point_scale(origin_end, scale);
	double road_width = origin_road_width*scale;
	double half_width = road_width / 2.0-1;

	////设置起始和结束点 
	//////高分辨率
	////img.Read24BMP("road_high.bmp");
	////Point start(img.convert_x(580, 80), img.convert_y(580, 80));
	////Point end(img.convert_x(42, 330), img.convert_y(42, 330));
	////double road_width = 16;


	////中分辨率 start:290 40 end: 21 165
	////img.Read24BMP("road_mid.bmp");
	////Point start(img.convert_x(300, 40), img.convert_y(300, 40));
	////Point end(img.convert_x(178, 215), img.convert_y(178, 215));
	////double road_width = 7.8;

	//////低分辨率 start:97 12 end: 7 56
	//img.Read24BMP("road_pool.bmp");
	//Point start(img.convert_from_huatu(97, 13));
	//Point end(img.convert_from_huatu(7, 56));
	//double road_width = 2;


	road road_(img.data);
	road_.setBMP(&img);
	road_.Narrowing(half_width); //
	//标注起点和终点
	img.setcolor(start.x, start.y, 'g');
	img.setcolor(end.x, end.y, 'g');
	//map 起点与终点
	start = road_.Map_to_road(start);
	end = road_.Map_to_road(end);
	//标注map起点和终点
	img.setcolor(start.x, start.y, 'b');
	img.setcolor(end.x, end.y, 'b');


	//A* 初始化
	Astar astar;
	vector<vector<int>> &maze = img.data;
	astar.InitAstar(maze);
	astar.setBMP(&img);
	//A*算法找寻路径 
	list<Point *> path = astar.GetPath(start, end, false);
	//显示
	astar.show_path(path, astar.img);
	img.Write24BMP("roadout_pool.bmp");

	//映射到原图
	list<Point *> path_origin;
	for (auto it = path.begin(); it != path.end(); it++){
		Point* p = new Point(0,0);
		*p = img.point_rescale((**it), scale);
		path_origin.push_back(p);
	}
	//显示
	astar.show_path(path_origin, &origin_img);
	cout << "path.size:" << path_origin.size() << endl;
	origin_img.Write24BMP("roadout.bmp");

	//list<Point *> path_origin;
	//for (int i = 0; i < 7; i++){
	//	path_origin.push_back(new Point(i, 2 * i));
	//}

	QpOptimizer qp(path_origin,5);

	qp.addkennel();
	qp.addconstraint(path_origin);
	MatrixXd matX, matY;
	qp.getAnswer(matX, matY);
	//计算位置
	list<Point *> path_output;
	qp.getpath(matX, matY, path_output);
	astar.show_path(path_output, &origin_img,'g');
	cout << "path_output.size:" << path_output.size() << endl;
	origin_img.Write24BMP("roadqp.bmp");
	
	system("pause");
	return 0;
}
