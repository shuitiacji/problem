#include<bits/stdc++.h>
using namespace std;
const int maxn = 150010;
int n, m, h;
int a[maxn], b[maxn];
int t[maxn << 2], tag[maxn << 2];
void maintain(int o) { t[o] = min(t[o << 1], t[o << 1 | 1]); }
void build(int o, int l, int r)
{
	if(l == r) { t[o] = -l; return ; }
	int mid = (l + r) >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
	maintain(o);
}
void pushdown(int o)
{
	if(tag[o] == 0) return ;
	t[o << 1] += tag[o]; t[o << 1 | 1] += tag[o];
	tag[o << 1] += tag[o]; tag[o << 1 | 1] += tag[o];
	tag[o] = 0;
}
void upt(int o, int l, int r, int x, int y, int v)
{
/**/if(x > y) return ;
	if(x <= l && r <= y)
	{
		t[o] += v; tag[o] += v;
		return ;
	}
	pushdown(o);
	int mid = (l + r) >> 1;
	if(x <= mid) upt(o << 1, l, mid, x, y, v);
	if(y > mid) upt(o << 1 | 1, mid + 1, r, x, y, v);
	maintain(o);
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &h);
	for(int i = 1; i <= m; ++i) scanf("%d", &b[i]);
	sort(b + 1, b + m + 1);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", &a[i]);
		a[i] = lower_bound(b + 1, b + m + 1, h - a[i]) - b;
	}
	build(1, 1, m);
	int ans = 0;
	for(int i = 1; i <= m; ++i)
		upt(1, 1, m, a[i], m, 1);
	if(t[1] >= 0) ans++;
	for(int i = m + 1; i <= n; ++i)
	{
		upt(1, 1, m, a[i - m], m, -1);
		upt(1, 1, m, a[i], m, 1);
		if(t[1] >= 0) ans++;
	}
	cout << ans << endl;
	return 0;
}
/*
题意：
给出一个长度为 n 的数列 ai和一个长度为 m 的数列 bi，求 ai 有多少个长度为 m 的连续子数列能与 bi 匹配。
两个数列可以匹配，当且仅当存在一种方案，使两个数列中的数可以两两配对，两个数可以配对当且仅当它们的和不小于 h。

思路:
考虑a顺序有关，b顺序无关，考虑把b从小到大排序并从b入手
考虑Hall定理，a,b完美匹配当且仅当b的每个子集连到a的点都大于等于这个子集的点数。
排序后，ai连向b的边是一个b的后缀也即一个连续的区间。
接着发现b的一个子集与a连的点数只与此时子集中最大的那个b有关，也即编号最后的那个，如果此时的点数<=最后的那个b连的点数，即不满足
每一个ai对应的b就是一段后缀，相当于覆盖了一条线段，满足上面的条件其实就是每一个bi被覆盖的次数满足大于等于i(因为以这个bi为最大元素时，点集最大的个数是i，即bi前面的所有b)，这样处理之后就很好用线段树来维护了。

debug:
1.24，一定要考虑lower_bound越界的情况
*/
