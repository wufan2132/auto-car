#pragma once
#include <vector> 
#include <list> 

class MapPoint
{
public:
	int x, y; //�����꣬����Ϊ�˷��㰴��C++�����������㣬x������ţ�y�������� 
	double F, G, H; //F=G+H 
	MapPoint *parent; //parent�����꣬����û����ָ�룬�Ӷ��򻯴��� 
	MapPoint(int _x, int _y) :x(_x), y(_y), F(0), G(0), H(0), parent(NULL)  //������ʼ�� 
	{
	}
};