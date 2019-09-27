#pragma once
#include<iostream>
#include <vector> 
#include <list> 
#include "planning/map/Image.h"
#include "planning/map/map_point.h"
using namespace std;


class road
{
public:
	road(vector<vector<int>>& rdata);
	~road();

	void find_start();
	void Narrowing(double width);

	void setBMP(Image* pImg){ img = pImg; };

	MapPoint Map_to_road(MapPoint& p);

	vector<vector<int>>& data;
	Image* img;
	int rows, cols;

private:
	void Narrowingcore(int x, int y, double r);
};

