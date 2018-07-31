#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 2e5 + 10;
#define pb push_back
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar();}
	return x * f;
}
struct magician
{
	int p, l, r;
}Q[maxn];
int a[maxn]; 
LL ANS[maxn];
int pre[maxn], las[maxn], nxt[maxn], fir[maxn];
vector<pair<int, int> > vec[maxn];
#define ls o << 1, l, mid
#define rs o << 1 | 1, mid + 1, r
struct SGT
{
	LL t[maxn << 2], tag[maxn << 2];
	void pushdown(int o, int l, int r)
	{
		if(!tag[o]) return ;
		int mid = (l + r) >> 1;
		tag[o << 1] += tag[o];
		tag[o << 1 | 1] += tag[o];
		t[o << 1] += 1LL * (mid - l + 1) * tag[o];
		t[o << 1 | 1] += 1LL * (r - mid) * tag[o];
		tag[o] = 0;
	}
	void maintain(int o)
	{
		t[o] = t[o << 1] + t[o << 1 | 1];
	}
	void upt(int o, int l, int r, int x, int y, LL v)
	{
		if(x > y) return ;
		Upt(o, l, r, x, y, v);
	}
	void Upt(int o, int l, int r, int x, int y, LL v)
	{
		if(x <= l && r <= y)
		{
			t[o] += v;
			tag[o] += v;
			return ;
		}
		pushdown(o, l, r);
		int mid = (l + r) >> 1;
		if(x <= mid) Upt(ls, x, y, v);
		if(y > mid) Upt(rs, x, y, v);
		maintain(o);
	}
	LL que(int o, int l, int r, int p)
	{
		if(l == r)
			return t[o];
		pushdown(o, l, r);
		int mid = (l + r) >> 1;
		if(p <= mid) return que(ls, p);
		else return que(rs, p);
	}
}T1, T2, T3, T4;
int main()
{
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
	int n = read(), q = read();
	int fg = 0;
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= q; ++i)
	{
		scanf("%d%d%d", &Q[i].p, &Q[i].l, &Q[i].r);
		vec[Q[i].l - 1].pb(make_pair(-1, i));
		vec[Q[i].r].pb(make_pair(1, i));
	}
	for(int i = 1; i <= n; ++i)
	{
		if(las[a[i]]) nxt[las[a[i]]] = i, pre[i] = las[a[i]];
		else fir[a[i]] = i;
		las[a[i]] = i;
	}
	for(int i = 1; i <= n; ++i)
	{
		for(int j = fir[i]; j; j = nxt[j])
		{
			int mid = (j + nxt[j]) >> 1;
			int Mid = (j + pre[j]) >> 1;
			if(j == fir[i])
				T1.upt(1, 1, n, 1, j - 1, j), T3.upt(1, 1, n, 1, j - 1, 1);
			else T1.upt(1, 1, n, Mid + 1, j - 1, j), T3.upt(1, 1, n, Mid + 1, j - 1, 1);
			if(!nxt[j])
				T2.upt(1, 1, n, j, n, -j), T4.upt(1, 1, n, j, n, 1);
			else T2.upt(1, 1, n, j, mid, -j), T4.upt(1, 1, n, j, mid, 1);
		}
		for(int j = 0; j < vec[i].size(); ++j)
		{
			int w = vec[i][j].second;
			int W = Q[w].p;
			ANS[w] += vec[i][j].first * (T4.que(1, 1, n, W) * Q[w].p + T2.que(1, 1, n, W) + T1.que(1, 1, n, W) - T3.que(1, 1, n, W) * W);
		}
	}
	for(int i = 1; i <= q; ++i) printf("%lld\n", ANS[i]);
	return 0;
}
/*
题意:
达拉然国中有一条长为 n 的街道,其中也住满了 q 个法师,并且街道中每一户仅存在一种法力水晶 a i 。法师们会一种神奇的法术,就是瞬间收
集一个法力水晶,其需要消耗的法力值就是该法师到法力水晶中的距离。每个法师都喜欢一些法力水晶,并且喜欢的种类都恰好是一个连续的区间 [l, r] 。他想收集到街道中每一种他喜欢并且 存在 的法力水晶(每一种只需收集一个)。而法师很懒,呆在他所在的位置 p 不会走动,他想知道最少需要耗费多少法力值才能满足要求。

思路：
考虑离线法师到数轴上，并考虑从水晶入手。
发现一个a水晶x能造成的影响，一定是在它和下一个a水晶y之间的法师（或上一个a水晶），并且中间划开，左半边的选x，右半边选y。
因为距离是abs，要分情况讨论，在法师前的贡献算负的，在后的算正的，这个显然可以用线段树维护。
同时还要看这个法师前面选了多少个水晶，后面选了多少个水晶，因为要加上或减去这个法师的位置，这可以再开个线段树维护。

当法师对水晶有要求时，这变成了一个二维问题，不止和位置有关，还要考虑种类。
用扫描线消去一维，对水晶种类排序，按种类加进去，在每个法师询问开始与结束用差分打标记即可。

debug:
1.nxt记成与位置有关的，调用时却用的权值。
*/
