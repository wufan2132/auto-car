#pragma once
#include <vector> 
#include<iostream>
#include<windows.h>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include "point.h"

using namespace std;




class BMP
{
public:
	BMP();
	~BMP();
	bool readBmp(char *bmpName);

	bool Read24BMP(const char *strFileName);//¶ÁÍ¼Ïñ

	bool Write24BMP(const char *strFileName);//Ð´Í¼Ïñ

	void bmpbuf_to_vec();//

	void vec_to_bmpbuf();

	Point convert_from_huatu(int x, int y){ return Point(rows - y, x); };

	void setcolor(int x, int y, char color);
	//scaler
	void compressionBMP(BMP& img, double scale);
	Point point_scale(Point& p, double scale){ return Point(p.x*scale, p.y*scale); };
	Point point_rescale(Point& p, double scale){ return Point(p.x/scale, p.y/scale); };

	int rows, cols;
	vector<vector<int>> data_R,data_G,data_B;
	vector<vector<int>> data;

	BYTE *pBmpBuf;//¶ÁÈëÍ¼ÏñÊý¾ÝµÄÖ¸Õë



	
};

