// 1005_Speel_It_Right.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

string digit2word(int i){
	switch (i) {
	case 48:
		return "zero";
	case 49:
		return "one";
	case 50:
		return "two";
	case 51:
		return "three";
	case 52:
		return "four";
	case 53:
		return "five";
	case 54:
		return "six";
	case 55:
		return "seven";
	case 56:
		return "eight";
	case 57:
		return "nine";
	default:
		return "non-digit";
	}
}
int main()
{
	int sum = 0;
	string input;
	cin >> input;
	for (int i : input) {
		sum += i - 48;
	}
	string res = to_string(sum);
	cout << digit2word(res[0]);
	for (int i = 1; i < res.size(); ++i) {
		cout << " " << digit2word(res[i]);
	}
}

