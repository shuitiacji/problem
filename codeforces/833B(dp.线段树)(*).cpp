#include<bits/stdc++.h>
using namespace std;
const int maxn = 4e5;
int n, k;
int t[maxn << 2], dp[maxn], tag[maxn << 2], a[maxn];
void maintain(int o) { t[o] = max(t[o << 1], t[o << 1 | 1]); }
void build(int o, int l, int r)
{
	tag[o] = 0; t[o] = 0;
	if(l == r) { t[o] = dp[l]; return ; }
	int mid = (l + r) >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
	maintain(o);
}
void pushdown(int o)
{
	if(tag[o])
	{
		tag[o << 1] += tag[o]; tag[o << 1 | 1] += tag[o];
		t[o << 1] += tag[o]; t[o << 1 | 1] += tag[o];
		tag[o] = 0;
	}
}
void upt(int o, int l, int r, int x, int y, int v)
{
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
int que(int o, int l, int r, int x, int y)
{
	if(x <= l && r <= y)
		return t[o];
	pushdown(o);
	int mid = (l + r) >> 1, ret = 0;
	if(x <= mid) ret = max(ret, que(o << 1, l, mid, x, y));
	if(y > mid) ret = max(que(o << 1 | 1, mid + 1, r, x, y), ret);
	return ret;
}
int las[maxn], tmp[maxn];
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]), las[i] = tmp[a[i]], tmp[a[i]] = i;
	for(int j = 1; j <= k; ++j)
	{
		build(1, 0, n);
		for(int i = 1; i <= n; ++i)
			upt(1, 0, n, las[i], i - 1, 1), dp[i] = que(1, 0, n, 0, i - 1);
	}
	cout << dp[n] << endl;
	return 0;
}
/*
题意：
把n个数分成k段，每段的价值为这一段数里不同数字的个数，问价值和最大为多少。

思路：
dp
枚举k，中间枚举n，有dp[i][j] = max(dp[w][j - 1] + val(w, i))
发现枚举n时影响到的value只有las[i]到i-1,用线段树加且维护最大值即可
这种重复数字的，一般和这个las有关

*/
