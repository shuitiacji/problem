#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
const int maxn = (1e5 + 10) * 2;
typedef long long LL;
using namespace std;
LL read()
{
	LL x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
LL s[maxn];
__gnu_pbds::gp_hash_table<LL, int > hs;
int tag[maxn << 2], flip[maxn << 2], t[maxn << 2];
int mk;
void build(int o, int l, int r)
{
	tag[o] = -1; flip[o] = 0; t[o] = 0;
	if(l == r) return ;
	int mid = (l + r) >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
}
void pushdown(int o, int l, int r)
{
	int mid = (l + r) >> 1;
	if(tag[o] == -1) goto nxt ;
	t[o << 1] = (mid - l + 1) * tag[o]; t[o << 1 | 1] = (r - mid) * tag[o];
	tag[o << 1] = tag[o]; tag[o << 1 | 1] = tag[o];
/**/flip[o << 1] = 0; flip[o << 1 | 1] = 0;
	tag[o] = -1;
	nxt:;
	if(!flip[o]) return ;
	t[o << 1] = (mid - l + 1) - t[o << 1]; t[o << 1 | 1] = (r - mid) - t[o << 1 | 1];
	flip[o << 1] ^= 1; flip[o << 1 | 1] ^= 1;
	flip[o] ^= 1;
}
void maintain(int o) { t[o] = t[o << 1] + t[o << 1 | 1]; }
void upt(int o, int l, int r, int x, int y, int v, int fg)
{
	if(x <= l && r <= y)
	{
		if(fg) { t[o] = v * (r - l + 1); tag[o] = v; flip[o] = 0; }
		else { t[o] = (r - l + 1) - t[o]; flip[o] ^= 1; }
		return ;
	}
	pushdown(o, l, r);
	int mid = (l + r) >> 1;
	if(x <= mid) upt(o << 1, l, mid, x, y, v, fg);
	if(y > mid) upt(o << 1 | 1, mid + 1, r, x, y, v, fg);
	maintain(o);
}
void query(int o, int l, int r)
{
	if(l == r) { cout << s[l] << endl; return ; } 
	pushdown(o, l, r);
	int mid = (l + r) >> 1;
	if(mid - l + 1 > t[o << 1]) query(o << 1, l, mid);
	else query(o << 1 | 1, mid + 1, r);
}
struct node
{
	LL t, l, r;
}q[maxn];
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	int n = read(); int tot = 0;
	for(int i = 1; i <= n; ++i)
	{
		q[i].t = read(); q[i].l = read(); q[i].r = read();
		++q[i].r;
		s[++tot] = q[i].l; s[++tot] = q[i].r;
	}
	s[++tot] = 1;
	sort(s + 1, s + tot + 1);
	tot = unique(s + 1, s + tot + 1) - s - 1;
	build(1, 1, tot);
	for(int i = 1; i <= tot; ++i) hs[s[i]] = i;
	for(int i = 1; i <= n; ++i)
	{
		q[i].l = hs[q[i].l]; q[i].r = hs[q[i].r] - 1;
		if(q[i].t == 1)
			upt(1, 1, tot, q[i].l, q[i].r, 1, 1);
		if(q[i].t == 2)
			upt(1, 1, tot, q[i].l, q[i].r, 0, 1);
		if(q[i].t == 3)
			upt(1, 1, tot, q[i].l, q[i].r, 0, 0);
		query(1, 1, tot);
	}
	return 0;
}
/*
题意：
维护一个长度10^18的01序列，要求兹瓷区间赋值、区间取反、查询第一个0的位置。

思路：
考虑这个东西有个性质，可能的第一个0的位置为1, l, r+1，(l,r为修改操作中的l,r)
直接按修改的l,r离散一下，用线段树维护所有的操作即可

debug:
31行
*/
