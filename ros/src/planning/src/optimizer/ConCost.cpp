#include "planning/ConCost.h"


ConCost::ConCost()
{
}


ConCost::~ConCost()
{
}


double ConCost::auto_sum(){
	sum_cost = 0;
	for (auto pair : map){
		sum_cost += pair.second;
	}
	return sum_cost;
}

ConCost ConCost::operator+(const ConCost& b){
	ConCost cost;
	for (auto pair : this->map){
		if(b.map.count(pair.first))
			cost.map[pair.first] = pair.second + b.map.at(pair.first);
		else
			cost.map[pair.first] = pair.second;
	}
	cost.auto_sum();
	return cost;
}
ConCost ConCost::operator-(const ConCost& b){
	ConCost cost;
	for (auto pair : this->map){
		if(b.map.count(pair.first))
			cost.map[pair.first] = pair.second - b.map.at(pair.first);
		else
			cost.map[pair.first] = pair.second;
	}
	cost.auto_sum();
	return cost;
}
void ConCost::operator+=(const ConCost& b){
	for (auto& pair : this->map){
		if(b.map.count(pair.first))
			pair.second += b.map.at(pair.first);
	}
	auto_sum();
}
void ConCost::operator-=(const ConCost& b){
	for (auto& pair : this->map){
		if(b.map.count(pair.first))
			pair.second -= b.map.at(pair.first);
	}
	auto_sum();
}
bool ConCost::operator>(const ConCost& b){
	return this->sum_cost > b.sum_cost;
}
bool ConCost::operator<(const ConCost& b){
	return this->sum_cost < b.sum_cost;
}

void ConCost::print(){
	cout << "---cost---" << endl;
	int count = 0;
	for (auto pair : map){
		
		if (count >= 3){
			count = 0;
			cout << endl;
		}
		count++;
		cout << pair.first << ":" << setw(15 - pair.first.size()) << setprecision(4)<<pair.second << " ";
	}
	cout << endl;
	cout << " cost sum: " << setprecision(6) << sum_cost << endl;
};