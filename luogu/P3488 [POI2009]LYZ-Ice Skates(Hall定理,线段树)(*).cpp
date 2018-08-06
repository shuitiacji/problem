#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
typedef long long LL;
int n, m, k, d;
LL t[maxn << 2], Maxl[maxn << 2], Max[maxn << 2], Maxr[maxn << 2];;
void maintain(int o)
{
	t[o] = t[o << 1] + t[o << 1 | 1];
	Maxl[o] = max(Maxl[o << 1], t[o << 1] + Maxl[o << 1 | 1]);
	Maxr[o] = max(Maxr[o << 1 | 1],	t[o << 1 | 1] + Maxr[o << 1]);
	Max[o] = max(max(Max[o << 1], Max[o << 1 | 1]), Maxr[o << 1] + Maxl[o << 1 | 1]);
}
void build(int o, int l, int r)
{
	if(l == r)
	{
		Max[o] = Maxl[o] = Maxr[o] = t[o] = -k;
		return ;
	}
	int mid = (l + r) >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
	maintain(o);
}
void upt(int o, int l, int r, int p, int v)
{
	if(l == r)
	{
		Max[o] = Maxl[o] = Maxr[o] = t[o] = t[o] + v;
		return ;
	}
	int mid = (l + r) >> 1;
	if(p <= mid) upt(o << 1, l, mid, p, v);
	else upt(o << 1 | 1, mid + 1, r, p, v);
	maintain(o);
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &k, &d);
	build(1, 1, n);
	for(int i = 1; i <= m; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		upt(1, 1, n, x, y);
		if(Max[1] <= 1LL * d * k)
			puts("TAK");
		else puts("NIE");
	}
	return 0;
}
/*
题意：
滑冰俱乐部初始有 1..n 号码溜冰鞋各 k 双,已知 x 号脚的人可以穿 x..x + d 号码的鞋子。现
在有 m 次操作,每次两个数 r、x,表示 r 号脚的人来了 x 个,x 为负表示离开。对于每次操作,
输出溜冰鞋是否足够。

思路：
显然是个二分图匹配，考虑Hall来判
这里有个贪心思路，就是最不可能满足的子集都满足了，则肯定是匹配的，这样就不需要看所有的子集了
从最劣情况入手，显然选择连续型号的人会使右边与他相连的人最少.
有sigma(ai) <= (r - l + 1 + d) * k  (l <= i <= r)
sigma(ai - k) <= d * k

显然用线段树维护最大子段和，看有没有超过d * k即可
具体就是用线段树维护一个区间内的和，最大子段和，以左端点为起点的最大子段和，以右端点为终点的最大子段和
*/
