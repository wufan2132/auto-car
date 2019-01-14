#include "planning/map/A_star.h"
#include <math.h> 

Astar::Astar(YAML::Node yaml_conf)
:kG(yaml_conf["kG"].as<double>()),
kH(yaml_conf["kH"].as<double>()){}

void Astar::InitAstar(std::vector<std::vector<int>> &_maze)
{
	maze = _maze;
}



double Astar::calcG(MapPoint *temp_start, MapPoint *point)
{
	double extraG = (abs(point->x - temp_start->x) + abs(point->y - temp_start->y)) == 1 ? kCost1 : kCost2;
	double parentG = point->parent == NULL ? 0 : point->parent->G; //����ǳ�ʼ�ڵ㣬���丸�ڵ��ǿ� 
	return parentG + extraG;
}

double Astar::calcH(MapPoint *point, MapPoint *end)
{
	//�ü򵥵�ŷ����þ������H�����H�ļ����ǹؼ������кܶ��㷨��û�����о�^_^ 
	return sqrt((double)(end->x - point->x)*(double)(end->x - point->x) + (double)(end->y - point->y)*(double)(end->y - point->y))*kCost1;
}

double Astar::calcF(MapPoint *point)
{
	return kG*point->G + kH*point->H;
}

MapPoint *Astar::getLeastFpoint()
{
	if (!openList.empty())
	{
		auto resPoint = openList.front();
		for (auto &point : openList)
		if (point->F<resPoint->F)
			resPoint = point;
		return resPoint;
	}
	return NULL;
}

MapPoint *Astar::findPath(MapPoint &startPoint, MapPoint &endPoint, bool isIgnoreCorner)
{
	openList.push_back(new MapPoint(startPoint.x, startPoint.y)); //�������,��������һ���ڵ㣬������� 
	while (!openList.empty())
	{
		auto curPoint = getLeastFpoint(); //�ҵ�Fֵ��С�ĵ� 

		//std::cout << "find_node:" << openList.size() << "  cur_distant:" << curPoint->H << std::endl;

		openList.remove(curPoint); //�ӿ����б���ɾ�� 
		closeList.push_back(curPoint); //�ŵ��ر��б� 
		//1,�ҵ���ǰ��Χ�˸����п���ͨ���ĸ��� 
		auto surroundPoints = getSurroundPoints(curPoint, isIgnoreCorner);
		for (auto &target : surroundPoints)
		{
			//2,��ĳһ�����ӣ���������ڿ����б��У����뵽�����б����õ�ǰ��Ϊ�丸�ڵ㣬����F G H 
			if (!isInList(openList, target))
			{
				target->parent = curPoint;

				target->G = calcG(curPoint, target);
				target->H = calcH(target, &endPoint);
				target->F = calcF(target);

				openList.push_back(target);

				//img->setcolor(target->x, target->y, 'G');
			}
			//3����ĳһ�����ӣ����ڿ����б��У�����Gֵ, �����ԭ���Ĵ�, ��ʲô������, �����������ĸ��ڵ�Ϊ��ǰ��,������G��F 
			else
			{
				int tempG = calcG(curPoint, target);
				if (tempG<target->G)
				{
					target->parent = curPoint;

					target->G = tempG;
					target->F = calcF(target);
				}
			}
			MapPoint *resPoint = isInList(openList, &endPoint);
			if (resPoint)
				return resPoint; //�����б���Ľڵ�ָ�룬��Ҫ��ԭ�������endpointָ�룬��Ϊ��������� 
		}
	}

	return NULL;
}

std::list<MapPoint *> Astar::GetPath(MapPoint &startPoint, MapPoint &endPoint, bool isIgnoreCorner)
{
	MapPoint *result = findPath(startPoint, endPoint, isIgnoreCorner);
	std::list<MapPoint *> path;
	if(result==NULL)
		ROS_ERROR("Astar::GetPath: Can not find a feasible path!");
	//����·�������û�ҵ�·�������ؿ����� 
	while (result)
	{
		path.push_front(result);
		result = result->parent;
	}
	return path;
}

MapPoint *Astar::isInList(const std::list<MapPoint *> &list, const MapPoint *point) const
{
	//�ж�ĳ���ڵ��Ƿ����б��У����ﲻ�ܱȽ�ָ�룬��Ϊÿ�μ����б����¿��ٵĽڵ㣬ֻ�ܱȽ����� 
	for (auto p : list)
	if (p->x == point->x&&p->y == point->y)
		return p;
	return NULL;
}


//
//maze[x][y] == 0: 可走
//其他值：不可走
bool Astar::isCanreach(const MapPoint *point, const MapPoint *target, bool isIgnoreCorner) const
{
	if (target->x<0 || target->x>maze.size() - 1
		|| target->y<0 && target->y>maze[0].size() - 1
		|| maze[target->x][target->y] != 0
		|| target->x == point->x&&target->y == point->y
		|| isInList(closeList, target)) //������뵱ǰ�ڵ��غϡ�������ͼ�����ϰ�������ڹر��б��У�����false 
		return false;
	else
	{
		if (abs(point->x - target->x) + abs(point->y - target->y) == 1) //��б�ǿ��� 
			return true;
		else
		{
			//б�Խ�Ҫ�ж��Ƿ��ס 
			if (maze[point->x][target->y] == 0 && maze[target->x][point->y] == 0)
				return true;
			else
				return isIgnoreCorner;
		}
	}
}

std::vector<MapPoint *> Astar::getSurroundPoints(const MapPoint *point, bool isIgnoreCorner) const
{
	std::vector<MapPoint *> surroundPoints;

	for (int x = point->x - 1; x <= point->x + 1; x++)
	for (int y = point->y - 1; y <= point->y + 1; y++)
	if (isCanreach(point, new MapPoint(x, y), isIgnoreCorner))
		surroundPoints.push_back(new MapPoint(x, y));

	return surroundPoints;
}


void Astar::show_path(std::list<MapPoint *>& path, Image* img, char color){
	for (auto it = path.begin(); it != path.end(); it++){
		//
		//cout << "x:" << (*it)->x << "  y:" << (*it)->y << endl;
		int x = min((*it)->x, img->rows-1);
		x = max(0, x);
		int y = min((*it)->y, img->cols-1);
		y = max(0, y);
		img->setcolor(x, y, color);
	}
	cout << endl;
}

//移动平滑滤波
void Astar::smooth(std::list<MapPoint *>& path,int order){
	int len = path.size();
	vector<int> path_x(len);
	vector<int> path_y(len);
	vector<int> temp(len);

	auto it = path.begin();
	for (int i = 0; it != path.end();i++, it++){
		path_x[i] = (*it)->x;
		path_y[i] = (*it)->y;
	}
	//x
	it = path.begin();
	for (int i = 0; it != path.end(); i++, it++){
		int x = 0, y =0, n = 1;
		x += path_x[i];
		y += path_y[i];
		while (n < order&&i + n < len && i - n >= 0){		
				x += path_x[i + n];
				x += path_x[i - n];
				y += path_y[i + n];
				y += path_y[i - n];
				n++;
		}
		(*it)->x = x / (2 * n - 1);
		(*it)->y = y / (2 * n - 1);
	}
}