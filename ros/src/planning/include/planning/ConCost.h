#pragma once
#include "planning/common.h"
#include<unordered_map>
#include <iomanip>//��Ҫ���ǰ�����ͷ�ļ�
#include<iostream>
#include<string>
using namespace std;

class ConCost
{
public:
	ConCost();
	~ConCost();

	void set_value(string item_name, double value){
		map[item_name] = value;
	}
	double & value(string item_name){
		return map[item_name];
	}
	double auto_sum();

	void print();

	ConCost operator+(const ConCost& b);
	ConCost operator-(const ConCost& b);
	void operator+=(const ConCost& b);
	void operator-=(const ConCost& b);
	bool operator>(const ConCost& b);
	bool operator<(const ConCost& b);
private:
	double sum_cost = DOUBLE_MAX;
	unordered_map<string, double> map;
};

