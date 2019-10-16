// 1006_Sign_In_and_Sign_Out.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

bool earlierThan(string t1, string t2) {
	for (int i = 0; i < 8; ++i) {
		if (t1[i] < t2[i])
			return true;
		else if (t1[i] > t2[i])
			return false;
	}
	return false;
}

int main()
{
	int m;
	cin >> m;
	string earlist, latest, tempId;
	string earlistTime, latestTime;
	string arriveTime, leaveTime;
	earlistTime = "24:00:00";
	latestTime = "00:00:00";
	for (int i = 0; i < m; ++i) {
		cin >> tempId;
		cin >> arriveTime >> leaveTime;
		if (earlierThan(arriveTime, earlistTime)) {
			earlistTime = arriveTime;
			earlist = tempId;
		}
		if (earlierThan(latestTime, leaveTime)) {
			latestTime = leaveTime;
			latest = tempId;
		}
	}
	cout << earlist << " " << latest;
}
