#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
#define pb push_back
const int maxn = 3e5 + 10, maxm = maxn << 1;
int to[maxm], nxt[maxm], head[maxn], sz[maxn], dep[maxn], son[maxn], f[maxn], top[maxn];
vector<pair<int, int> > vec1[maxn], vec2[maxn];
int ans[maxn], w[maxn];
int n, m, e;
void add(int x, int y)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e;
	to[++e] = x; nxt[e] = head[y]; head[y] = e;
}
namespace HLD
{
	void dfs1(int u, int fa)
	{
		dep[u] = dep[fa] + 1; f[u] = fa; sz[u] = 1; son[u] = 0;
		for(int i = head[u]; i; i = nxt[i])
		{
			int v = to[i];
			if(v == fa) continue;
			dfs1(v, u);
			if(!son[u] || sz[son[u]] < sz[v]) son[u] = v;
			sz[u] += sz[v];
		}
	}
	void dfs2(int u, int tp)
	{
		top[u] = tp;
		if(son[u]) dfs2(son[u], tp);
		for(int i = head[u]; i; i = nxt[i])
		{
			int v = to[i];
			if(v == f[u] || v == son[u]) continue;
			dfs2(v, v);
		}
	}
	int Lca(int u, int v)
	{
		int f1 = top[u], f2 = top[v];
		while(f1 != f2)
		{
			if(dep[f1] < dep[f2]) swap(f1, f2), swap(u, v);
			u = f[f1]; f1 = top[u];
		}
		if(dep[u] > dep[v]) swap(u, v);
		return u;
	}
}
struct SGT
{
	int tot;
	int t[maxn * 40], ls[maxn * 40], rs[maxn * 40], rt[maxn];
	void upt(int &o, int l, int r, int x, int v)
	{
		if(!o) o = ++tot;
		if(l == r) { t[o] += v; return ; }
		int mid = (l + r) >> 1;
		if(x <= mid) upt(ls[o], l, mid, x, v);
		else upt(rs[o], mid + 1, r, x, v);
	}
	int que(int o, int l, int r, int x)
	{
		if(!o) return 0;
		if(l == r) return t[o];
		int mid = (l + r) >> 1;
		if(x <= mid) return que(ls[o], l, mid, x);
		else return que(rs[o], mid + 1, r, x);
	}
	int merge(int o1, int o2, int l, int r)
	{
		if(!o1 || !o2) return o1 | o2;
		if(l == r) { t[o1] += t[o2]; return o1; }
		int mid = (l + r) >> 1;
		ls[o1] = merge(ls[o1], ls[o2], l, mid);
		rs[o1] = merge(rs[o1], rs[o2], mid + 1, r);
		return o1;
	}
}s1, s2;	
void dfs_calc(int u, int fa)
{
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs_calc(v, u);
		s1.rt[u] = s1.merge(s1.rt[u], s1.rt[v], -n, n * 2);
		s2.rt[u] = s2.merge(s2.rt[u], s2.rt[v], -n, n * 2);
	}
	for(int i = 0; i < vec1[u].size(); ++i)
		s1.upt(s1.rt[u], -n, n * 2, vec1[u][i].second, vec1[u][i].first);
	for(int i = 0; i < vec2[u].size(); ++i)
		s2.upt(s2.rt[u], -n, n * 2, vec2[u][i].second, vec2[u][i].first);
	ans[u] += s1.que(s1.rt[u], -n, n * 2, dep[u] + w[u]);
	ans[u] += s2.que(s2.rt[u], -n, n * 2, w[u] - dep[u]);
}	
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	n = read(); m = read();
	for(int i = 1; i < n; ++i)
	{
		int x = read(), y =read();
		add(x, y);
	}
	for(int i = 1; i <= n; ++i) w[i] = read();
	HLD::dfs1(1, 0); HLD::dfs2(1, 1);
	for(int i = 1; i <= m; ++i)
	{
		int s = read(), t = read();
		int tmp = HLD::Lca(s, t), L = dep[s] + dep[t] - 2 * dep[tmp];
		vec1[s].pb(make_pair(1, dep[s]));
		vec2[t].pb(make_pair(1, L - dep[t]));
		vec1[f[tmp]].pb(make_pair(-1, dep[s]));
		vec2[f[tmp]].pb(make_pair(-1, L - dep[t]));
		if(w[tmp] + dep[tmp] == dep[s] && w[tmp] - dep[tmp] == L - dep[t]) ans[tmp]--;
	}
	dfs_calc(1, 0);
	for(int i = 1; i <= n; ++i) printf("%d ", ans[i]);
	return 0;
}	
/*
思路：
把链分解成一条向上的，向下的，差分打标记，对于一个观察员，答案与它子树内的标记点以及标记点的dep有关，离线后线段树合并一遍算答案

debug:
lca答案可能会被一条链算两次，特殊减重复的即可。
*/
