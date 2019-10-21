# Summary
先把给的数转换成10进制，然后一个一个基去试，结果有几个测试点死活过不去。  
后来看了网上的攻略，发现需要注意转换成整数后溢出的情况。给定的数据转换成10进制好像并不会溢出。但在代基的时候有可能发生。所以需要注意使用基计算后出现小于0的情况。  
但改了代码后还是有几个过不了，有个还是超时。。。于是根据网上的改成二分查找，初始上界为转换成10进制的数值，下界为最大数字+1（好像有两个测试点会检查下界是不是太小，比如给定一个数字a，它至少为11进制，如果输出是二进值就错了）。但是题目要求输出最小的基，二分法似乎做不到。。。我又试了几个值，发现好像这个要求并没有测试？？？  
这样改了后却还有2个点过不了。我找了半天发现在将字符串转换为整数时，网上ac代码使用的时cmath中的pow函数计算每个位的底，我用了迭代，每次乘上radix。

**我的代码**
```c++
long long str2int(string s, long long radix) {
	long long sum = 0;
	int r = 1;
	while (!s.empty()) {
		sum += char2int(s.back()) * radix;
		r *= radix;
		s.pop_back();
	}
	return sum;
}
```
**AC代码**  
```c++
long long str2int(string s, long long radix) {
	long long sum = 0;
	int r = 0;
	while (!s.empty()) {
		sum += char2int(s.back()) * pow(radix, r);
        r++;
		s.pop_back();
	}
	return sum;
}
```
这样看好像又是溢出了。。。  
在我把我的代码里`int r`改成`long long r`后果然可以了  

这道题看着简单，但其实要拿满分好像也没那么容易。以后要多注意溢出情况。