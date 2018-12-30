#pragma once

#include<iostream>
#include <vector> 
#include <list> 
#include "planning/map/Image.h"
#include "planning/map/map_point.h"

const double kCost1 = 10; //ֱ��һ������ 
const double kCost2 = 14; //б��һ������ 
const double kG = 5; //
const double kH = 1; //����

class Astar
{
public:
	void InitAstar(std::vector<std::vector<int>> &_maze);
	std::list<MapPoint *> GetPath(MapPoint &startPoint, MapPoint &endPoint, bool isIgnoreCorner);

	void setBMP(Image* pImg){ img = pImg; };
	Image* img;

	static void show_path(std::list<MapPoint *>& path, Image* img, char color='r');

	static void smooth(std::list<MapPoint *>& path,int order);

private:
	MapPoint *findPath(MapPoint &startPoint, MapPoint &endPoint, bool isIgnoreCorner);
	std::vector<MapPoint *> getSurroundPoints(const MapPoint *MapPoint, bool isIgnoreCorner) const;
	bool isCanreach(const MapPoint *point, const MapPoint *target, bool isIgnoreCorner) const; //�ж�ĳ���Ƿ����������һ���ж� 
	MapPoint *isInList(const std::list<MapPoint *> &list, const MapPoint *point) const; //�жϿ���/�ر��б����Ƿ����ĳ�� 
	MapPoint *getLeastFpoint(); //�ӿ����б��з���Fֵ��С�Ľڵ� 
	//����FGHֵ 
	int calcG(MapPoint *temp_start, MapPoint *point);
	int calcH(MapPoint *point, MapPoint *end);
	int calcF(MapPoint *point);
private:
	std::vector<std::vector<int>> maze;
	std::list<MapPoint *> openList;  //�����б� 
	std::list<MapPoint *> closeList; //�ر��б� 
};