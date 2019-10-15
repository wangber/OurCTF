// 1004_Counting_Leaves.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <map>

using namespace std;

struct Node {
	int index;
	//children
	Node* left;
	//brothers
	Node* right;
	int layer;
	Node(int x):index(x), left(nullptr), right(nullptr), layer(0){}
};

map<int, int> calLayer(Node* n, int l) {
	static map<int, int> leaveNum;
	if (n->right) {
		calLayer(n->right, l);
	}
	if (n->left) {
		calLayer(n->left, l + 1);
	}
	else {
		leaveNum[l] += 1;
	}
	n->layer = l;
	return leaveNum;
}
int main()
{
	int n, m;
	cin >> n >> m;
	if (n == 1) {
		cout << 1;
		return 0;
	}
	map<int, Node*> nodes;
	for (int i = 0; i < m; ++i) {
		int id, k;
		cin >> id;
		if (id == 0)
			break;
		Node* parent;
		if (nodes.count(id)) {
			parent = nodes[id];
		}
		else {
			parent = new Node(id);
			nodes[id] = parent;
		}
		cin >> k;
		for (int j = 0; j < k; ++j) {
			int child_id;
			cin >> child_id;
			if (nodes.count(child_id)) {
				//不允许近亲结婚？。。。
				//assume child already entered as a parent (has no brothers)
				Node* child = nodes[child_id];
				child->right = parent->left;
				parent->left = child;
			}
			else {
				Node* child = new Node(child_id);
				child->right = parent->left;
				parent->left = child;
				nodes[child_id] = child;
			}
		}
	}
	if (!nodes.count(1)) {
		cout << 0;
		return 0;
	}
	map<int, int> leaveNum = calLayer(nodes[1], 1);
	int totalLayer = leaveNum.rbegin()->first;
	for (int i = 1; i < totalLayer; ++i) {
		cout << leaveNum[i] << " ";
	}
	cout << leaveNum[totalLayer];
	return 0;
}
