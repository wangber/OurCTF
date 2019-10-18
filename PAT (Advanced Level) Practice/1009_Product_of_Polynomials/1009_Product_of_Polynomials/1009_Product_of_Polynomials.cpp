// 1009_Product_of_Polynomials.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <map>

using namespace std;

int main()
{
	map<int, double> p1;
	int k, e;
	double c;
	cin >> k;
	for (int i = 0; i < k; ++i) {
		cin >> e >> c;
		p1[e] = c;
	}
	cin >> k;
	map<int, double> p;
	for (int i = 0; i < k; ++i) {
		cin >> e >> c;
		for (auto j = p1.begin(); j != p1.end(); ++j) {
			int re = j->first + e;
			p[re] += c * j->second;
			if (p[re] == 0)
				p.erase(re);
		}
	}
	cout << p.size();
	for (auto i = p.rbegin(); i != p.rend(); ++i) {
		printf(" %d %.1f", i->first, i->second);
	}
}
