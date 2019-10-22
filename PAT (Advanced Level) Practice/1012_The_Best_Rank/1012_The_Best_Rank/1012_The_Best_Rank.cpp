// 1012_The_Best_Rank.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	struct Node {
		int c, m, e, a;
	};
	int n, k;
	cin >> n >> k;
	vector<int> a, c, m, e;
	map<string, Node> hash;
	for (int i = 0; i < n; ++i) {
		Node g;
		string s;
		cin >> s;
		cin >> g.c >> g.m >> g.e;
		g.a = (g.c + g.m + g.e) / 3;
		hash[s] = g;
		a.push_back(g.a);
		c.push_back(g.c);
		m.push_back(g.m);
		e.push_back(g.e);
	}
	sort(a.rbegin(), a.rend());
	sort(c.rbegin(), c.rend());
	sort(m.rbegin(), m.rend());
	sort(e.rbegin(), e.rend());
	for (int i = 0; i < k; ++i) {
		string s;
		cin >> s;
		if (hash.count(s) == 0) {
			cout << "N/A" << endl;
		}
		else {
			Node g = hash[s];
			int rank_a, rank_c, rank_m, rank_e;
			vector<pair<int, int>> v;
			pair<int, int> p;
			p.first = distance(a.begin(), find(a.begin(), a.end(), g.a));
			p.second = 0;
			v.push_back(p);
			p.first = distance(c.begin(), find(c.begin(), c.end(), g.c));
			p.second = 1;
			v.push_back(p);
			p.first = distance(m.begin(), find(m.begin(), m.end(), g.m));
			p.second = 2;
			v.push_back(p);
			p.first = distance(e.begin(), find(e.begin(), e.end(), g.e));
			p.second = 3;
			v.push_back(p);
			sort(v.begin(), v.end());
			cout << v[0].first + 1 << " ";
			switch (v[0].second) {
			case 0:
				cout << 'A' << endl;
				break;
			case 1:
				cout << 'C' << endl;
				break;
			case 2:
				cout << 'M' << endl;
				break;
			case 3:
				cout << 'E' << endl;
				break;
			}
		}
	}
}
