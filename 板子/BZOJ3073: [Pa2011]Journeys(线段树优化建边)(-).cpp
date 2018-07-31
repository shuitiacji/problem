#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
int tot = 0, e = 0;
int n, m, s;
const int maxn = 500010 * 9, maxm = maxn * 6;
int to[maxm], nxt[maxm], head[maxn], w[maxm], hs[maxn], dis[maxn];
struct node
{
	int x, y;
	bool operator > (const node &b) const { return y > b.y; }
};
void add(int x, int y, int z, int Fg)
{
	if(Fg) { to[++e] = y; nxt[e] = head[x]; head[x] = e; w[e] = z; }
	else { to[++e] = x; nxt[e] = head[y]; head[y] = e; w[e] = z; }
}
int p;
struct SGT
{
	int hs[maxn], lc[maxn], rc[maxn], fg, x, y, v;
	void build(int &o, int l, int r)
	{
		o = ++tot;
		if(l == r){
			hs[l] = o; return ;
		}
		int mid = (l + r) >> 1;
		build(lc[o], l, mid); build(rc[o], mid + 1, r);
		add(o, lc[o], 0, fg); add(o, rc[o], 0, fg);
	}
	void upt(int o, int l, int r){
		if(x <= l && r <= y)
		{
			add(o, p, v, fg ^ 1);
			return ;
		}
		int mid = (l + r) >> 1;
		if(x <= mid) upt(lc[o], l, mid);
		if(y > mid) upt(rc[o], mid + 1, r);
	}
}S1, S2;
void dij()
{
	static priority_queue<node, vector<node>, greater<node> > q;
	memset(dis, 0x3f, sizeof(dis));
	q.push((node){S1.hs[s], 0}); dis[S1.hs[s]] = 0; dis[S2.hs[s]] = 0;
	while(!q.empty())
	{
		int u = (q.top()).x; q.pop();
		for(int i = head[u]; i; i = nxt[i])
		{
			int v = to[i];
			if(dis[v] > dis[u] + w[i])
			{
				dis[v] = dis[u] + w[i];
				q.push((node){v, dis[v]});
			}
		}
	}
	for(int i = 1; i <= n; ++i) printf("%d\n", dis[S2.hs[i]]);
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	n = read(); m = read(); s = read();
	int rt1 = 0, rt2 = 0;
	S1.fg = 0; S2.fg = 1;
	S1.build(rt1, 1, n); S2.build(rt2, 1, n);
	S1.v = 1; S2.v = 0;
	for(int i = 1; i <= m; ++i)
	{
		int a = read(), b = read(), c = read(), d = read();
		p = ++tot;
		S1.x = a; S1.y = b; S2.x = c; S2.y = d;
		S1.upt(rt1, 1, n); S2.upt(rt2, 1, n);
		p = ++tot;
		S1.x = c; S1.y = d; S2.x = a; S2.y = b;
		S1.upt(rt1, 1, n); S2.upt(rt2, 1, n);
	}
	for(int i = 1; i <= n; ++i) add(S1.hs[i], S2.hs[i], 0, 0);
	dij();	
	return 0;
}
/*
题意：
Seter建造了一个很大的星球，他准备建造N个国家和无数双向道路。N个国家很快建造好了，用1..N编号，但是他发现道路实在太多了，他要一条条建简直是不可能的！于是他以如下方式建造道路：(a,b),(c,d)表示，对于任意两个国家x,y，如果a<=x<=b,c<=y<=d，那么在xy之间建造一条道路。Seter保证一条道路不会修建两次，也保证不会有一个国家与自己之间有道路。
Seter好不容易建好了所有道路，他现在在位于P号的首都。Seter想知道P号国家到任意一个国家最少需要经过几条道路。当然，Seter保证P号国家能到任意一个国家。

注意：可能有重边


debug:
7.12
一定要从第二颗线段树的叶子往第一颗对应的叶子连边
*/
