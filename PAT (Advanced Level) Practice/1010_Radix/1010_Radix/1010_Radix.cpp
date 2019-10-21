// 1010_Radix.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int char2int(int i) {
	if (isdigit(i))
		return i - '0';
	return i - 'a' + 10;
}

long long str2int(string s, long long radix) {
	long long sum = 0;
	long long r = 1;
	while (!s.empty()) {
		sum += char2int(s.back()) * r;
		r *= radix;
		s.pop_back();
	}
	return sum;
}

long long calradix(string s, long long n) {
	long long radix = 0;
	long long low = char2int(*max_element(s.begin(), s.end())) + 1;
	long long high = max(low, n);
	while (low <= high) {
		long long mid = (low + high) / 2;
		long long temp = str2int(s, mid);
		if (temp < 0 || temp > n) {            //考虑溢出
			high = mid - 1;
		}
		else if (temp < n) {
			low = mid + 1;
		}
		else {
			radix = mid;
			break;
		}
	}
	return radix;
}

int main()
{
	string n1, n2, s;
	int tag;
	long long radix, n;
	cin >> n1 >> n2 >> tag >> radix;
	if (tag == 1) {
		n = str2int(n1, radix);
		s = n2;
	}
	else {
		n = str2int(n2, radix);
		s = n1;
	}
	long long r = calradix(s, n);
	if (r) {
		cout << r;
	}
	else {
		cout << "Impossible";
	}
}
