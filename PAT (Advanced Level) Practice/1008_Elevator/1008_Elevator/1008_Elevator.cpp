// 1008_Elevator.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int time = 0;
	int floor = 0;
	int nextrequire;
	for (int i = 0; i < n; ++i) {
		cin >> nextrequire;
		if (nextrequire > floor) {
			time += (nextrequire - floor) * 6;
			floor = nextrequire;
		}
		else if (nextrequire < floor) {
			time += (floor - nextrequire) * 4;
			floor = nextrequire;
		}
		time += 5;
	}
	cout << time;
}
