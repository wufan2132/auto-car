#include "BMP.h"


BMP::BMP()
{
}


BMP::~BMP()
{
}


bool BMP::readBmp(char *bmpName)
{
	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;
	

	ifstream src(bmpName, ifstream::binary); //2.bmp为灰度图像
	if (!src)
	{
		cerr << "打开失败";
		return 0;
	}
	src.read((char *)&fh, sizeof(BITMAPFILEHEADER));
	if (fh.bfType != 'MB')
	{
		cerr << "这不是BMP图像";
		return 0;
	}
	src.read((char *)&ih, sizeof(BITMAPINFOHEADER));
	rows = ih.biHeight;
	cols = ih.biWidth;
	//bmp图像数据存储是4字节对齐的
	int colsDQ = (cols + 3) / 4 * 4;
	//移动到图像数据处
	src.seekg(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)* 256, ios::beg);//参数：相对位置，起点
	//读取图像数据
	unsigned char *pData = new unsigned char[rows*colsDQ];
	src.read((char *)pData, rows*colsDQ);

	data.resize(rows);
	for (auto &vec : data)
		vec.resize(cols);

	for (int i = rows - 1; i >= 0; --i) //bmp图像存储为行倒序
	for (int j = 0; j < cols; ++j)
	{
		if (*(pData + i*colsDQ + j) < 400)
			data[rows - 1 - i][j] = 0;
		else
			data[rows - 1 - i][j] = 1;

	}
	return 1;//读取文件成功
}


bool BMP::Read24BMP(const char *strFileName)
{
	if (!strFileName)	return 0;

	BITMAPFILEHEADER	FileHeader;
	BITMAPINFOHEADER	InfoHeader;
	FILE*				fp;
	BYTE			    *pCur;
	BYTE				tmp;
	int					ImgSize, Patch, Extend, i;

	if ((fp = fopen(strFileName, "rb")) == NULL) return 0;
	if (fread((void *)&FileHeader, 1, 14, fp) != 14){ fclose(fp); return 0; }
	if (fread((void *)&InfoHeader, 1, 40, fp) != 40){ fclose(fp); return 0; }
	if (FileHeader.bfOffBits < 54){ fclose(fp); return 0; }
	if (InfoHeader.biBitCount != 24){ fclose(fp); return 0; }

	cols = (int)InfoHeader.biWidth;
	rows = (int)InfoHeader.biHeight;
	Patch = 3 * cols;
	ImgSize = Patch*rows;
	fseek(fp, FileHeader.bfOffBits, SEEK_SET);

	if ((pBmpBuf = new BYTE[ImgSize]) == NULL){ fclose(fp); return 0; }

	Extend = (cols * 3 + 3) / 4 * 4 - cols * 3;
	for (pCur = pBmpBuf + ImgSize - Patch;
		pCur >= pBmpBuf;
		pCur -= Patch)
	{
		if (fread((void *)pCur, 1, Patch, fp) != UINT(Patch))
		{
			delete[]pBmpBuf; fclose(fp); return 0;
		}
		for (i = 0; i < Extend; i++)
		if (fread(&tmp, 1, 1, fp) != 1)
		{
			delete[]pBmpBuf; fclose(fp); return 0;
		}
	}
	fclose(fp);
	bmpbuf_to_vec();
	return 1;
}

bool BMP::Write24BMP(const char *strFileName)
{
	vec_to_bmpbuf();
	if (rows*cols == 0) return false;
	BYTE *pImg = pBmpBuf;

	if (!strFileName)	return false;
	if (!pImg)			return false;

	BITMAPFILEHEADER	FileHeader;
	BITMAPINFOHEADER	InfoHeader;
	FILE				*fp;
	BYTE				*pCur;
	int					ImgSize, Patch, Extend, i;

	Patch = cols * 3;
	ImgSize = (cols + 3) / 4 * 4 * rows;

	if ((fp = fopen(strFileName, "wb+")) == NULL) return false;
	FileHeader.bfType = ((WORD)('M' << 8) | 'B');
	FileHeader.bfOffBits = 54; // sizeof(FileHeader)+sizeof(InfoHeader)
	FileHeader.bfSize = FileHeader.bfOffBits + ImgSize;
	FileHeader.bfReserved1 = 0;
	FileHeader.bfReserved2 = 0;

	InfoHeader.biSize = 40;
	InfoHeader.biWidth = cols;
	InfoHeader.biHeight = rows;
	InfoHeader.biPlanes = 1;
	InfoHeader.biBitCount = 24;
	InfoHeader.biCompression = 0;
	InfoHeader.biSizeImage = ImgSize;
	InfoHeader.biXPelsPerMeter = 0;
	InfoHeader.biYPelsPerMeter = 0;
	InfoHeader.biClrUsed = 0;
	InfoHeader.biClrImportant = 0;

	if (fwrite((void *)&FileHeader, 1, 14, fp) != 14)
	{
		fclose(fp); remove(strFileName); return false;
	}
	if (fwrite((void *)&InfoHeader, 1, 40, fp) != 40)
	{
		fclose(fp); remove(strFileName); return false;
	}

	Extend = (cols * 3 + 3) / 4 * 4 - cols * 3;
	for (pCur = pImg + (rows - 1)*Patch;
		pCur >= pImg;
		pCur -= Patch)
	{
		if (fwrite((void *)pCur, 1, Patch, fp) != UINT(Patch))
		{
			fclose(fp); remove(strFileName); return false;
		}

		for (i = 0; i < Extend; i++)
		if (fwrite((void *)(pCur + Patch - 3), 1, 1, fp) != 1)
		{
			fclose(fp); remove(strFileName); return false;
		}

	}
	fclose(fp);
	return true;
}


void BMP::bmpbuf_to_vec(){
	//resize
	data_R.resize(rows);
	for (auto &vec : data_R)
		vec.resize(cols);
	data_G.resize(rows);
	for (auto &vec : data_G)
		vec.resize(cols);
	data_B.resize(rows);
	for (auto &vec : data_B)
		vec.resize(cols);
	data.resize(rows);
	for (auto &vec : data)
		vec.resize(cols);

	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			data_R[rows - 1 - i][j] = pBmpBuf[j * 3 + 2 + cols*i * 3];
			data_G[rows - 1 - i][j] = pBmpBuf[j * 3 + 1 + cols *i * 3];
			data_B[rows - 1 - i][j] = pBmpBuf[j * 3 + cols *i * 3];
			if (data_R[rows - 1 - i][j] + data_G[rows - 1 - i][j] + data_B[rows - 1 - i][j]< 400)
				data[rows - 1 - i][j] = 0;
			else
				data[rows - 1 - i][j] = 1;
		}
	}
}


void BMP::vec_to_bmpbuf(){
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			pBmpBuf[j * 3 + 2 + cols*i * 3] = data_R[rows - 1 - i][j];
			pBmpBuf[j * 3 + 1 + cols *i * 3] = data_G[rows - 1 - i][j];
			pBmpBuf[j * 3 + cols *i * 3] = data_B[rows - 1 - i][j];
		}
	}
}

void BMP::setcolor(int x, int y, char color){
	switch (color)
	{
		//红
	case 'r': data_R[x][y] = 255;
			  data_G[x][y] = 0;
			  data_B[x][y] = 0;
			  break;
	//绿
	case 'g': data_R[x][y] = 0;
			  data_G[x][y] = 255;
		      data_B[x][y] = 0;
			  break;
	//蓝
	case 'b': data_R[x][y] = 0;
		      data_G[x][y] = 0;
		      data_B[x][y] = 255;
			  break;
			  //白
	case 'W': data_R[x][y] = 255;
		      data_G[x][y] = 255;
		      data_B[x][y] = 255;
			  break;
			  //黑
	case 'B': data_R[x][y] = 0;
		      data_G[x][y] = 0;
		      data_B[x][y] = 0;
			  break;
			  //灰
	case 'G': data_R[x][y] = 100;
			  data_G[x][y] = 100;
		      data_B[x][y] = 100;
		      break;
	default:
		break;
	}

}


void BMP::compressionBMP(BMP& img, double scale){
	//计算图像尺寸
	img.rows = round(scale*rows);
	img.cols = round(scale*cols);
	
	//生成pBmpBuf
	int lineByte2 = (img.cols * 3 + 3) / 4 * 4;
	img.pBmpBuf = new unsigned char[lineByte2 * img.rows];///为缩放后图像分配存储空间
	int pre_i, pre_j, after_i, after_j;//缩放前后对应的像素点坐标
	for (int i = 0; i<img.rows; i++)
	{
		for (int j = 0; j<img.cols; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				after_i = i;
				after_j = j;
				pre_i = min(rows, round(after_i / scale));/////取整，插值方法为：最邻近插值（近邻取样法）
				pre_j = min(cols, round(after_j / scale));
				//在原图范围内
				*(img.pBmpBuf + i * lineByte2 + j * 3 + k) = *(pBmpBuf + pre_i * cols * 3 + pre_j * 3 + k);
			}
		}
	}
	//生成像素矩阵
	img.bmpbuf_to_vec();
}