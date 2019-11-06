// 1015_Reversible_Primes.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

int runFermatPower(int a, int b, int n) {

	int result = 1;

	for (int i = 0; i < b; i++) {
		result *= a;
		result %= n;

	}
	return result;
}

int baseReverse(int n, int d) {
	int rev = 0;
	while (n) {
		rev *= d;
		rev += n % d;
		n /= d;
	}
	return rev;
}

bool isprime(int key) {
	if (key <= 1) {
		return false;
	}
	int upper = (int)sqrt(1.0 * key);
	for (int i = 2; i < upper + 1; i++) {
		if (key % i == 0) {
			return false;
		}
	}
	return true;
}

int main()
{
	int n, d;
	cin >> n;
	while (n > 0) {
		cin >> d;
		if (isprime(n) && isprime(baseReverse(n, d)))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
		cin >> n;
	}
}
