#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 10;
typedef long long LL;
const int mod = 20000909;
int n, L;
int a[maxn], b[maxn];
int ck(int x)
{
	int l = 1, r = 3 * n;
	for(int i = 1; i <= n; ++i)
	{
		while(a[i] - b[l] > x) ++l;
		while(b[r] - a[i] > x) --r;
		if(l > r) return 0;
		++l; ++r;
	}
	return 1;
}
LL Pow(LL x, int p)
{
	LL r = 1;
	while(p)
	{
		if(p & 1) r = x * r % mod;
		x = x * x % mod; p >>= 1;
	}
	return r;
}
int main()
{
	freopen("queue.in", "r", stdin);
	freopen("queue.out", "w", stdout);
	scanf("%d%d", &n, &L);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for(int i = 1; i <= n; ++i) scanf("%d", &b[i]);
	int tot = 0;
	for(int i = n + 1; i <= 3 * n; i += 2)
	{
		++tot;
		b[i] = b[tot] + L; b[i + 1] = b[tot] - L;
	}
	sort(a + 1, a + n + 1);
	sort(b + 1, b + 3 * n + 1);
	int l = 0, r = 1e9 + 10, ans;
	ck(2);
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(ck(mid)) { ans = mid; r = mid - 1; }
		else l = mid + 1;
	}
	cout << Pow(2, ans) << endl;
	return 0;
}
/*
题意：
一些蚯蚓在一个长度为L的数轴圆上，即L与0相连
给出他们的坐标a[i]，以及一些关键点的坐标b[i]
现在每个蚯蚓一起开始以1m/s的速度来移动到关键点（一个萝卜一个坑），求最小时间

思路：
这个环不是很好搞，考虑一个套路
假设一个蚯蚓和一个关键点，可能距离有
a[i] - b[i], b[i] - a[i], a[i] - (b[i] - L), b[i] + L - a[i]
把b[i] - L, b[i] + L 当做新的b[i]，新加到b数组。现在的b[i]是原来的3倍
那么所有的可能距离都变成了a[i] - b[i], b[i] - a[i]

考虑一个二分答案，验证就是看所有a[i]能不能找到一个b[i]来匹配(条件当然时他们的差有没有超过当前二分的答案)
将a与b排序，考虑贪心.
一个a只能选左边的b或者右边的b，对于可行的左边的，肯定贪心选最右的，对于可行的右边的，肯定选最最左的。这样的话就能让后面的更有可能有点满足
实现直接用l,r两个指针搞就行了，直接扫到贪心的最好的地方，如果l > r就不满足。
同时这两个用了之后就不能用了，要++l, ++r
*/
