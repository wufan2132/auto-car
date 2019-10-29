#pragma once
#include<iostream>
#include <vector> 
#include <list> 
#include "planning/map/Image.h"
#include "planning/map/map_point.h"


class road
{
public:
	road(std::vector<std::vector<int>>& rdata);
	~road();

	void find_start();
	void Narrowing(double width);

	void setBMP(Image* pImg){ img = pImg; };

	MapPoint Map_to_road(MapPoint& p);

	std::vector<vector<int>>& data;
	Image* img;
	int rows, cols;

private:
	void Narrowingcore(int x, int y, double r);
};

