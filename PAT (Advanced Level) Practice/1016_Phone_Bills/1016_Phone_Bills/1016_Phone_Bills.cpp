// 1016_Phone_Bills.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int toll[24];

struct Record {
	string mon;
	string name;
	string time;
	bool on;
};

bool cmp(const Record &a, const Record &b) {
	return a.time < b.time;
}

/*
void time_and_bill_one_day(int start_h, int start_min, int end_h, int end_min, int &time, int &bill) {
	time = (end_h - start_h) * 60 - start_min + end_min;
	bill = 0;
	bill += (-start_min)*toll[start_h];
	for (int i = start_h; i < end_h; ++i) {
		bill += toll[i] * 60;
	}
	bill += end_min * toll[end_h];
}
*/

void get_time_and_bill(string on_time, string out_time, int &time, int &bill) {
	/*
	int start_h, start_min, end_h, end_min, start_day, end_day;
	start_day = stoi(on_time.substr(0, 2));
	start_h = stoi(on_time.substr(3, 2));
	start_min = stoi(on_time.substr(6, 2));
	end_day = stoi(out_time.substr(0, 2));
	end_h = stoi(out_time.substr(3, 2));
	end_min = stoi(out_time.substr(6, 2));
	
	int bill_first, bill_last, time_first, time_last;
	time_and_bill_one_day(start_h, start_min, 24, 0, time_first, bill_first);
	time_and_bill_one_day(0, 0, end_h, end_min, time_last, bill_last);
	int day_num = end_day - start_day - 1;
	time = day_num * 24 * 60 + time_first + time_last;
	int day_bill = 0;
	for (int i = 0; i < 24; ++i) {
		day_bill += toll[i];
	}
	day_bill *= 60;
	bill = day_num * day_bill + bill_first + bill_last;
	*/
	int start_h, start_min, end_h, end_min, start_day, end_day;
	start_day = stoi(on_time.substr(0, 2));
	start_h = stoi(on_time.substr(3, 2));
	start_min = stoi(on_time.substr(6, 2));
	end_day = stoi(out_time.substr(0, 2));
	end_h = stoi(out_time.substr(3, 2));
	end_min = stoi(out_time.substr(6, 2));
	
	time = bill = 0;
	while (start_day != end_day || start_h != end_h || start_min != end_min) {
		bill += toll[start_h];
		start_min++;
		time++;
		if (start_min == 60) {
			start_h++;
			start_min = 0;
		}
		if (start_h == 24) {
			start_day++;
			start_h = 0;
		}
	}
}

int main()
{
	for (int i = 0; i < 24; ++i) {
		cin >> toll[i];
	}
	int n;
	cin >> n;
	set<string> users;
	vector<Record> records;
	string name, time, on;
	for (int i = 0; i < n; ++i) {
		cin >> name >> time >> on;
		Record r;
		r.name = name;
		r.mon = time.substr(0, 2);
		r.time = time.substr(3);
		r.on = (on == "on-line");
		records.push_back(r);
		users.insert(name);
	}
	sort(records.begin(), records.end(), cmp);

	// string month = time.substr(0, 2);
	string month;
	for (auto i = users.begin(); i != users.end(); ++i) {
		int totalamount = 0;
		int flag = 0;
		string start_time;
		for (int j = 0; j < n; ++j) {    // 仅用于计算总花费是否为0以确定要不要输出
			if (records[j].name == *i) {
				if (records[j].on) {
					start_time = records[j].time;
					flag = 1;
				}
				else if (flag == 1) {
					flag = 0;
					month = records[j].mon;
					int time, bill;
					get_time_and_bill(start_time, records[j].time, time, bill);
					totalamount += bill;
				}
			}
		}
		if (totalamount == 0)
			continue;
		cout << *i << " " << month << endl;
		flag = 0;
		for (int j = 0; j < n; ++j) {
			if (records[j].name == *i) {
				if (records[j].on) {
					start_time = records[j].time;
					flag = 1;
				}
				else if(flag == 1){
					flag = 0;
					int time, bill;
					get_time_and_bill(start_time, records[j].time, time, bill);
					cout << start_time << " " << records[j].time << " " << time;
					printf(" $%.2f\n", bill / 100.0);
				}
			}
		}
		printf("Total amount: $%.2f\n", totalamount / 100.0);
	}
}
