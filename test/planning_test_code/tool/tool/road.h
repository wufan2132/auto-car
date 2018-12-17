#pragma once
#include<iostream>
#include <vector> 
#include <list> 
#include "BMP.h"
#include "point.h"
using namespace std;


class road
{
public:
	road(vector<vector<int>>& rdata);
	~road();

	void find_start();
	void Narrowing(double width);

	void setBMP(BMP* pImg){ img = pImg; };

	Point Map_to_road(Point& p);

	vector<vector<int>>& data;
	BMP* img;
	int rows, cols;

private:
	void Narrowingcore(int x, int y, double r);
};

