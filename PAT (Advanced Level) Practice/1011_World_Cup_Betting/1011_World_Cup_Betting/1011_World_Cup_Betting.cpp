// 1011_World_Cup_Betting.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	int max;
	vector<double> odds(3);
	double p = 1;
	string output = "";
	for (int i = 0; i < 3; ++i) {
		cin >> odds[0] >> odds[1] >> odds[2];
		max = 0;
		if (odds[1] > odds[0]) {
			max = 1;
		}
		if (odds[2] > odds[max]) {
			max = 2;
		}
		switch (max) {
		case 0:
			output += "W ";
			break;
		case 1:
			output += "T ";
			break;
		case 2:
			output += "L ";
			break;
		}
		p *= odds[max];
	}
	cout << setiosflags(ios::fixed);
	cout << output << setprecision(2) << p * 0.65 * 2 - 2;
}
