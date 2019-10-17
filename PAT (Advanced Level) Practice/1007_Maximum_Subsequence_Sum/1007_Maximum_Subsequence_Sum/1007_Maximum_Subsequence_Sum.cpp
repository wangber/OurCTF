// 1007_Maximum_Subsequence_Sum.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int k;
	cin >> k;
	vector<int> n;
	int sum = 0, maxsum = -1;
	int maxl = 0, maxr = 0;
	int l = 0, r = 0;
	for (int i = 0; i < k; ++i) {
		int temp;
		cin >> temp;
		sum += temp;
		if (sum < 0) {
			l = i + 1;
			sum = 0;
		}
		else if (sum > maxsum) {
			r = i;
			maxsum = sum;
			maxl = l;
			maxr = r;
		}
		n.push_back(temp);
	}
	if (maxsum == -1) {
		cout << "0 " << n[0] << " " << n[k - 1];
	}
	else
		cout << maxsum << " " << n[maxl] << " " << n[maxr];
}
