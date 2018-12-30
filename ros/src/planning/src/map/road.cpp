#include "planning/map/road.h"



road::road(vector<vector<int>>& rdata)
:data(rdata){
	rows = data.size();
	cols = data.at(0).size();
}

road::~road()
{
}

void road::Narrowing(double width){

	for (int i = 1; i < rows-1;i++)
	for (int j = 1; j < cols-1; j++){
		//�ж��Ƿ��ڱ߽���
		if (data[i][j]==1&&
			(data[i - 1][j] != 1 || data[i + 1][j] != 1 || data[i][j - 1] != 1 || data[i][j + 1] != 1)  ){
			//img->setcolor(i, j, 'g');
			Narrowingcore(i, j, width);
		
		}
	}
}

//���������r���ڵĶ���Ϊ2
void road::Narrowingcore(int x, int y, double r){
	double rx, ry;
	for (int i = max(0.0, x - r); i <= x + r&&i<rows; i++){
		rx = abs(i - x);
		ry = sqrt(r*r - rx*rx);
		for (int j = max(0.0, ceil(y -ry)); j <= floor(ry + y) && j<cols; j++)
		if (data[i][j] == 0){
			data[i][j] = 2;
			img->setcolor(i, j, 'G');
		}	
	}
}



MapPoint road::Map_to_road(MapPoint& p){
	if (data[p.x][p.y] == 0)
		return p;
	int d = 1;
	int x, y;
	while (1){
		x = min(p.x + d, rows - 1);
		y = p.y;
		if (data[x][y] == 0)
			return MapPoint(x,y);
		x = max(p.x - d, 0);
		y = p.y;
		if (data[x][y] == 0)
			return MapPoint(x, y);
		x = p.x;
		y = min(p.y + d, cols - 1);
		if (data[x][y] == 0)
			return MapPoint(x, y);
		x = p.x;
		y = max(p.y - d, 0);
		if (data[x][y] == 0)
			return MapPoint(x, y);
		d++;
	}
}