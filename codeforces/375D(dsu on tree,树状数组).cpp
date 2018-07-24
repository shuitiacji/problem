#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
const int maxn = 1e5 + 10, maxm = maxn << 1;
int e, n;
int to[maxm], nxt[maxm], head[maxn], son[maxn], sz[maxn], cnt[maxn], col[maxn], ans[maxn];
vector<pair<int, int> > vec[maxn];
void add(int x, int y)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e;
	to[++e] = x; nxt[e] = head[y]; head[y] = e;
}
void dfs(int u, int fa)
{
	sz[u] = 1; son[u] = 0;
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs(v, u);
		if(son[u] == 0 || sz[son[u]] < sz[v]) son[u] = v;
		sz[u] += sz[v];
	}
}
namespace BIT
{
	int c[maxn + 10];
	int lowbit(int x) { return x & (-x); }
	void upt(int x, int v)
	{
		if(x == 0) return ;
		x = n - x + 1;
		while(x <= n)
			c[x] += v, x += lowbit(x);
	}
	int que(int x)
	{
		int ret = 0;
		x = n - x + 1;
		if(x <= 0) return 0;
		while(x)
			ret += c[x], x -= lowbit(x);
		return ret;
	}
}
void dfs_set(int u, int fa, int fg)
{
	if(fg)
	{
		cnt[col[u]]++;
		BIT::upt(cnt[col[u]] - 1, -1);
		BIT::upt(cnt[col[u]], 1);
	}
	else 
	{
		cnt[col[u]]--;
		BIT::upt(cnt[col[u]] + 1, -1);
		BIT::upt(cnt[col[u]], 1);
	}
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs_set(v, u, fg);
	}
}
void dsu(int u, int fa, int keep)
{
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa || v == son[u]) continue;
		dsu(v, u, 0);
	}
/**/if(son[u]) dsu(son[u], u, 1);
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa || v == son[u]) continue;
		dfs_set(v, u, 1);
	}
	cnt[col[u]]++; BIT::upt(cnt[col[u]], 1); BIT::upt(cnt[col[u]] - 1, -1);
	for(int i = 0; i < vec[u].size(); ++i)
		ans[vec[u][i].first] = BIT::que(vec[u][i].second);
	if(keep == 0) dfs_set(u, fa, 0);
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	n = read(); int m = read();
	for(int i = 1; i <= n; ++i) col[i] = read();
	for(int i = 1; i < n; ++i) 
	{
		int x = read(), y = read();
		add(x, y);
	}
	for(int i = 1; i <= m; ++i)
	{
		int x = read(), y = read();
		vec[x].push_back(make_pair(i, y));
	}
	dfs(1, 0);
	dsu(1, 0, 1);
	for(int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
	return 0;
}	
/*
题意:
一棵树，询问一个子树内出现次数≥k的颜色有几种

思路:
本来可以dfs序后莫队
但这种可以树上莫队的题,一般也可以dsu on tree
为了求至少,用个BIT就可以了

debug:
81行,if(son[u])
45行
*/
