# Summary
这题我也真的是傻了。明明用平凡判别法就能弄出来的素性检测，我他妈偏要去看半天数论然后写了个Miller-Rabin塑性检测，结果有一个点怎么也过不去，我怀疑是不是写错了，还是有几个强伪素数就是找不到。。。  
还有，在位处超过7位时好像我写的算法也会出不知道什么错，直接崩了。。。  
然后用普通的迭代判定，直接没超时过了。。。  
这题告诉我们，有简单的算法在不超时的情况下就用简单的方法，不要为了追求简化复杂度去用复杂算法，别抖机灵  
附上我的Miller-Rabin代码，希望最后会有人指出不对的地方
```c++
bool millerRabin(int n, int k) {
	if (n % 2 == 0)
		return false;
	default_random_engine e;
	uniform_int_distribution<int> u(2, n - 2);
	e.seed(time(nullptr));
	for (int i = 0; i < k; ++i) {
		int t = n - 1;
		int s = 0;
		while (t & 1 == 0) {
			t >>= t;
			s += 1;
		}
		int b = u(e);
		int r = runFermatPower(b, t, n);
		if (r == 1 || r == n - 1)
			continue;
		bool isprime = false;
		for(int j = 0; j < s-1; ++j) {
			r = (r*r) % n;
			if (r == n - 1) {
				isprime = true;
				break;
			}
		}
		if (!isprime)
			return false;
	}
	return true;
}
```
