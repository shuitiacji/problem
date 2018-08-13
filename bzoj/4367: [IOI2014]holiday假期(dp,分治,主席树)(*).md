### Description

健佳正在制定下个假期去台湾的游玩计划。在这个假期，健佳将会在城市之间奔波，并且参观这些城市的景点。

在台湾共有n个城市，它们全部位于一条高速公路上。这些城市连续地编号为0到n-1。对于城市i(0<i<n-1)而言，与其相邻的城市是i-1和i+1。但是对于城市 0，唯一与其相邻的是城市 1。而对于城市n-1，唯一与其相邻的是城市n-2。

每个城市都有若干景点。健佳有d天假期并且打算要参观尽量多的景点。健佳已经选择了假期开始要到访的第一个城市。在假期的每一天，健佳可以选择去一个相邻的城市，或者参观所在城市的所有景点，但是不能同时进行。即使健佳在同一个城市停留多次，他也不会去重复参观该城市的景点。请帮助健佳策划这个假期，以便能让他参观尽可能多的景点。

<!--more-->

### Solution

考虑可能的路线就4种，一直向右，一直向左，向左走再折回向右，向右走再折回向左

容易想到，设$f[i],g[i],g1[i],f1[i]$分别表示向右走，向左走，向右走再折回起点，向左走再折回起点，用了i天的最优值

$ans=max\{max(f1[i]+g[m-i],g[i]+f1[m-i]),i=0...m\}$

每个东西的求法都类似，以f[i]为例

枚举向右能到达的最远点k，取i到k中的最大的$m-k+1$，$\mathcal O(n^3)$，可以主席树优化

考虑有个性质，设f[i]达到最优时到的最远点是d[i]

显然d[i]是单调递增的

用分治来利用这个条件

假设当前我们要算的是f[l]-f[r]，且d[l]-d[r]的取值范围是x到y

$mid = (l + r)/2$，暴力枚举x到y，算出f[mid]与d[mid]

得到两个子问题(l,mid-1,x,d[mid]),(mid+1,r,d[mid],y)

$\mathcal O(n \times log^2 n)$

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define debug(...) fprintf(stderr, __VA_ARGS__)
const int maxn = 2e5 + 5e4 + 10;
int rt[maxn];
LL f[maxn], g[maxn], g1[maxn], f1[maxn];
int f1d[maxn], g1d[maxn], fd[maxn], gd[maxn];
int a[maxn], b[maxn], len, n, m, s;
LL Ret;
namespace SGT
{
	int ls[1800000], rs[1800000], t[1800000];
	int tot = 0;
	LL sum[1800000];
	void upt(int o, int &o1, int l, int r, int pos, int v)
	{
		o1 = ++tot;
		ls[o1] = ls[o]; rs[o1] = rs[o]; t[o1] = t[o] + 1; sum[o1] = sum[o] + v;
		if(l == r) return ;
		int mid = (l + r) >> 1;
		if(pos <= mid) upt(ls[o], ls[o1], l, mid, pos, v);
		else upt(rs[o], rs[o1], mid + 1, r, pos, v);
	}
	void que(int o, int o1, int l, int r, int k)
	{
		if(!o && !o1) return ;
/**/	if(k > t[o1] - t[o]) return ; 
		if(k <= 0) { Ret += sum[o1] - sum[o]; return ; }
		if(l == r)
		{
/**/		Ret += 1LL * (t[o1] - t[o] - k + 1) * a[l];
			return ;
		}
		int mid = (l + r) >> 1, tmp = t[ls[o1]] - t[ls[o]];
		if(tmp < k) que(rs[o], rs[o1], mid + 1, r, k - tmp); 
/**/	else { Ret += sum[rs[o1]] - sum[rs[o]]; que(ls[o], ls[o1], l, mid, k); }
	}
}
void gao1(int l, int r, int L, int R)
{
	if(l > r) return ;
	int mid = (l + r) >> 1;
	for(int i = L; i <= R; ++i)
	{
		Ret = 0;
		SGT::que(rt[s - 1], rt[i], 1, len, i - s + 1 - (mid - (i - s)) + 1);
		if(f[mid] < Ret || !fd[mid]) f[mid] = Ret, fd[mid] = i;
	}
	gao1(l, mid - 1, L, fd[mid]); gao1(mid + 1, r, fd[mid], R);
}
void gao2(int l, int r, int L, int R)
{
	if(l > r) return ;
	int mid = (l + r) >> 1;
/**/for(int i = R; i >= L; --i)
	{
		Ret = 0;
		SGT::que(rt[i - 1], rt[s - 1], 1, len, s - i - (mid - (s - i)) + 1);
		if(g[mid] < Ret || !gd[mid]) g[mid] = Ret, gd[mid] = i;
	}
/**/gao2(mid + 1, r, L, gd[mid]); gao2(l, mid - 1, gd[mid], R);
}
void gao3(int l, int r, int L, int R)
{
	if(l > r) return ;
	int mid = (l + r) >> 1;
	for(int i = L; i <= R; ++i)
	{
		Ret = 0;
		SGT::que(rt[s - 1], rt[i], 1, len, i - s + 1 - (mid - ((i - s) << 1)) + 1);
		if(f1[mid] < Ret || !f1d[mid]) f1[mid] = Ret, f1d[mid] = i;
	}
	gao3(l, mid - 1, L, f1d[mid]); gao3(mid + 1, r, f1d[mid], R);
}
void gao4(int l, int r, int L, int R)
{
	if(l > r) return ;
	int mid = (l + r) >> 1;
/**/for(int i = R; i >= L; --i)
	{
		Ret = 0;
		SGT::que(rt[i - 1], rt[s - 1], 1, len, s - i - (mid - ((s - i) << 1)) + 1);
		if(g1[mid] < Ret || !g1d[mid]) g1[mid] = Ret, g1d[mid] = i;
	}
/**/gao4(mid + 1, r, L, g1d[mid]); gao4(l, mid - 1, g1d[mid], R);
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d%d", &n, &s, &m);
	++s;
	for(int i = 1; i <= n; ++i)
		scanf("%d", &b[i]), a[i] = b[i];
	sort(a + 1, a + n + 1);
	len = unique(a + 1, a + n + 1) - a - 1;
	for(int i = 1; i <= n; ++i)
	{
/**/	int tmp = lower_bound(a + 1, a + len + 1, b[i]) - a;
		SGT::upt(rt[i - 1], rt[i], 1, len, tmp, b[i]);
	}
	gao1(1, m, s, min(n, s + m));
	gao2(1, m, max(s - m, 1), s);
	gao3(1, m, s, min(n, s + (m >> 1)));
	gao4(1, m, max(1, s - (m >> 1)), s); 
	LL ans = 0;
	for(int i = 0; i <= m; ++i)
	{
		ans = max(ans, max(f[i] + g1[m - i], g[i] + f1[m - i]));
	}
	Ret = 0;
	SGT::que(rt[0], rt[2], 1, len, 1);
	cout << ans << endl;
	return 0;
}
```

### Debug

1.28行

2.32行，一个权值有可能有多个点，不能都算进来

3.37行，k写成tmp

4.56行，80行，要从R到L，因为如果只有0的话，要优先选右的

5.62行，86行，L,g1d,R,g1d写反

6.100行，len写成n

