// 1013_Battle_Over_Cities.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct City {
	int ind;
	int color;     // 0: not found, 1: found but has connected not deceted, 2: detected
	vector<int> connectedCities;
	City(int i=0):ind(i), color(0){}
};

void dfs_visit(map<int, City> &cities, City &c) {
	c.color = 1;
	for (int i : c.connectedCities) {
		if (cities.count(i) && cities[i].color == 0) {
			dfs_visit(cities, cities[i]);
		}
	}
	c.color = 2;
}

int countConnected(map<int, City> cities) {
	int count = 0;
	for (auto i = cities.begin(); i != cities.end(); ++i) {
		if (i->second.color == 0) {
			count += 1;
			dfs_visit(cities, i->second);
		}
	}
	return count;
}

int main()
{
	ios_base::sync_with_stdio(false);
	int n, m, k;
	cin >> n >> m >> k;
	map<int, City> cities;
	for (int i = 1; i <= n; ++i) {
		cities[i] = City(i);
	}
	for (int i = 0; i < m; ++i) {
		int temp1, temp2;
		cin >> temp1 >> temp2;
		cities[temp1].connectedCities.push_back(temp2);
		cities[temp2].connectedCities.push_back(temp1);
	}
	vector<int> ckcities;
	for (int i = 0; i < k; ++i) {
		int temp;
		cin >> temp;
		ckcities.push_back(temp);
	}
	for (int i = 0; i < k; ++i) {
		map<int, City> aftermath = cities;
		aftermath.erase(ckcities[i]);
		cout << countConnected(aftermath) - 1 << endl;
	}
}
