# Summary
思路就是使用队列模拟  

这题需要注意的就是在要关门的时候如果已经在服务中的顾客需要继续被服务直到完成。。。这点还是比较坑的，因为题目里说输出时间HH在08-17之间，MM在00-59之间。如果服务超时超过一个小时的顾客不就需要17之后的时间了吗  

所以一开始我就按照最后离开时间来算，如果离开时间在17点之后就Sorry了，但是3个检查点没过  
我改成超过17点就不再处理，多过了一个  

我的程序逻辑是先将所有人入队（在人入队过程中若有满员就将队头出队，在出队时计算并更新时间），若时间到了就停止入队。这应该没什么问题。问题是在全部入队后还需要将剩余顾客出队来计算他们最后服务时间，而在队中的最后会不会Sorry也要看前面人结束服务时间。我并没有将每个队列单独计算时间，并且没有记录开始服务时间，而是在每次更新时间时减少队首结束服务还需等待的时间。这导致了最后如果同时有几列队伍在加班，一列先加班结束了，其他正在被服务的客户也会被Sorry。。后拉参考了网上大神的代码发现别人的逻辑就是将每列单独计算自己的结束时间与第一个人离开时间。最后嫌麻烦，直接用网上的代码AC了。。。这里附上我原来的代码，以防还有其他没考虑到的情况。(工程中的AC代码在提交时需要改scanf_s，VS的尿性。。。)

```c++
// 1014_Waiting_in_Line.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <climits>

using namespace std;

struct Customer {
	int idx;
	int time;
	int finishTime;
	Customer(int i = 0, int t = 0) :idx(i), time(t), finishTime(-1) {}
};

string min2time(int mins) {
	if (mins < 0) {
		return "Sorry";
	}
	char s[6];
	sprintf_s(s, "%02d:%02d", mins / 60 + 8, mins % 60);
	return s;
}

int main()
{
	int n, m, k, q;
	cin >> n >> m >> k >> q;
	vector<queue<Customer>> lines(n);
	Customer cusinfo[1010];
	int queryQueue[1010];
	for (int i = 0; i < k; ++i) {
		int tempTime;
		cin >> tempTime;
		Customer cus(i, tempTime);
		cusinfo[i] = cus;
	}
	for (int i = 0; i < q; ++i) {
		int qcustomer;
		cin >> qcustomer;
		queryQueue[i] = qcustomer;
	}
	int time = 0;
	int i = 0;
	while (i < k) {
		if (time >= 540)
			break;
		int leastNum = m;
		int leastQueue = 0;
		for (int j = 0; j < n; ++j) {
			if (lines[j].size() < leastNum) {
				leastNum = lines[j].size();
				leastQueue = j;
			}
		}
		if (leastNum < m) {          // can still gets in
			lines[leastQueue].push(cusinfo[i]);
			i++;
		}
		else {                       // all full
			int leastTime = INT_MAX;
			for (int j = 0; j < n; ++j) {         //find least time
				if (lines[j].front().time < leastTime) {
					leastTime = lines[j].front().time;
				}
			}
			time += leastTime;
			for (int j = 0; j < n; ++j) {        //dequeue and update finish time
				if (!lines[j].empty()) {
					lines[j].front().time -= leastTime;
					if (lines[j].front().time == 0) {
						cusinfo[lines[j].front().idx].finishTime = time;
						lines[j].pop();
					}
				}
			}
		}
	}
	// after all enqueue, dequeue all
	int leastLeft = k;
	while (leastLeft > 0) {
		if (time >= 540)
			break;
		int leastTime = INT_MAX;
		for (int j = 0; j < n; ++j) {         //find least time
			if (!lines[j].empty() && lines[j].front().time < leastTime) {
				leastTime = lines[j].front().time;
			}
		}
		time += leastTime;
		for (int j = 0; j < n; ++j) {        //dequeue and update finish time
			if (!lines[j].empty()) {
				lines[j].front().time -= leastTime;
				if (lines[j].front().time == 0) {
					cusinfo[lines[j].front().idx].finishTime = time;
					lines[j].pop();
				}
			}
		}
		leastLeft = 0;
		for (int j = 0; j < n; ++j) {
			leastLeft += lines[j].size();
		}
	}
	for (int i = 0; i < q; ++i) {
		cout << min2time(cusinfo[queryQueue[i] - 1].finishTime) << endl;
	}
}
```