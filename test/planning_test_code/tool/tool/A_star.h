#pragma once

/*
//A*算法对象类
*/
#include<iostream>
#include <vector> 
#include <list> 
#include "BMP.h"
#include "point.h"

const double kCost1 = 10; //直移一格消耗 
const double kCost2 = 14; //斜移一格消耗 
const double kG = 5; //
const double kH = 1; //趋势




class Astar
{
public:
	void InitAstar(std::vector<std::vector<int>> &_maze);
	std::list<Point *> GetPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);

	void setBMP(BMP* pImg){ img = pImg; };
	BMP* img;

	static void show_path(std::list<Point *>& path, BMP* img, char color='r');

private:
	Point *findPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);
	std::vector<Point *> getSurroundPoints(const Point *point, bool isIgnoreCorner) const;
	bool isCanreach(const Point *point, const Point *target, bool isIgnoreCorner) const; //判断某点是否可以用于下一步判断 
	Point *isInList(const std::list<Point *> &list, const Point *point) const; //判断开启/关闭列表中是否包含某点 
	Point *getLeastFpoint(); //从开启列表中返回F值最小的节点 
	//计算FGH值 
	int calcG(Point *temp_start, Point *point);
	int calcH(Point *point, Point *end);
	int calcF(Point *point);
private:
	std::vector<std::vector<int>> maze;
	std::list<Point *> openList;  //开启列表 
	std::list<Point *> closeList; //关闭列表 
};