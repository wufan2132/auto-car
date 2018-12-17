#pragma once
#include <vector> 
#include <list> 

class Point
{
public:
	int x, y; //点坐标，这里为了方便按照C++的数组来计算，x代表横排，y代表竖列 
	double F, G, H; //F=G+H 
	Point *parent; //parent的坐标，这里没有用指针，从而简化代码 
	Point(int _x, int _y) :x(_x), y(_y), F(0), G(0), H(0), parent(NULL)  //变量初始化 
	{
	}
};