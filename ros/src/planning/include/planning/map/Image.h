#pragma once
#include <vector> 
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include "planning/common.h"
#include "planning/map/map_point.h"

using namespace std;

#define FAR                 far
#define far

typedef u_int32_t         DWORD;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef int32_t             LONG;

typedef struct tagBITMAPFILEHEADER {
        WORD    bfType;
        DWORD   bfSize;
        WORD    bfReserved1;
        WORD    bfOffBits;
        DWORD   bfReserved2;
} BITMAPFILEHEADER, FAR *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
        DWORD      biSize;
        LONG       biWidth;
        LONG       biHeight;
        WORD       biPlanes;
        WORD       biBitCount;
        DWORD      biCompression;
        DWORD      biSizeImage;
        LONG       biXPelsPerMeter;
        LONG       biYPelsPerMeter;
        DWORD      biClrUsed;
        DWORD      biClrImportant;
} BITMAPINFOHEADER, FAR *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagRGBQUAD{
unsigned char rgbBlue;
unsigned char rgbGreen;
unsigned char rgbRed;
unsigned char rgbReserved;
}RGBQUAD;

class Image
{
public:
	Image();
	~Image();

	bool Readpgm(string fileName);

	bool Read24BMP(string strFileName);

	bool Write24BMP(string strFileName);//��???

	void convert_twovalue();

	void drawPoint(int x, int y,char color, int size = 1);

	void bmpbuf_to_vec();//

	void vec_to_bmpbuf();

	MapPoint convert_from_huatu(int x, int y){ return MapPoint(rows - y, x); };

	void setcolor(int x, int y, char color);
	//scaler
	void compressionBMP(Image& img, double scale);
	MapPoint point_scale(MapPoint& p, double scale){ return MapPoint(p.x*scale, p.y*scale); };
	MapPoint point_rescale(MapPoint& p, double scale){ return MapPoint(p.x/scale, p.y/scale); };
	//
	bool twovalue(int R,int G, int B);

	int rows, cols;
	vector<vector<int>> data_R,data_G,data_B;
	vector<vector<int>> data;

	BYTE *pBmpBuf;//???????????????
};

