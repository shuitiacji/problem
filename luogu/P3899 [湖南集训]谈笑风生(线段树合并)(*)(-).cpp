#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define ls lc[o], l, mid
#define rs rc[o], mid + 1, r
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) {	x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
int e;
const int maxn = 3e5 + 10, maxm = maxn << 1;
struct node{
	int y, z;
};
LL ans[maxn];
vector<node> Q[maxn];
int rt[maxn];
int n, q;
namespace SGT{
	int lc[maxn * 25], rc[maxn * 25], tot;
	LL sum[maxn *25];
	void upt(int &o, int l, int r, int p, int v)
	{
		if(!o) o = ++tot;
		sum[o] += v; 
		if(l == r) {return ;}
		int mid = (l+r) >> 1;
		if(p <= mid) upt(ls, p, v);
		else upt(rs, p, v);
	}
	LL que(int o,int l, int r, int x, int y)
	{
		if(!o) return 0;
		if(x <= l && r <= y) return sum[o];
		int mid = (l + r) >> 1;
		LL ret = 0;
		if(x <= mid) ret += que(ls, x, y);
		if(y > mid) ret += que(rs, x, y);
		return ret;
	}
	int merge(int o1, int o2, int l, int r)
	{
		if(!o1) return o2;
		if(!o2) return o1;
		sum[o1] += sum[o2];
		if(l == r) return o1;
		int mid = (l + r) >> 1;
		lc[o1] = merge(lc[o1], lc[o2], l, mid);
		rc[o1] = merge(rc[o1], rc[o2], mid+1, r);
		return o1;
	}
};
int to[maxm], nxt[maxm], head[maxn], sz[maxn], dep[maxn];
void add(int x, int y)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e;
	to[++e] = x; nxt[e] = head[y]; head[y] = e;
}
int depmax;
void dfs_set(int u, int fa)
{
	dep[u] = dep[fa] + 1; sz[u] = 1;
	depmax = max(dep[u], depmax);
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs_set(v, u);
		sz[u] += sz[v];
	}
}
void dfs_calc(int u, int fa)
{
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs_calc(v, u);
		rt[u] = SGT::merge(rt[u], rt[v], 1, depmax);
	}
	for(int i = 0; i < Q[u].size(); ++i){
		ans[Q[u][i].z] += SGT::que(rt[u], 1, depmax, min(depmax, dep[u] + 1), min(depmax, dep[u] + Q[u][i].y));
	}
	SGT::upt(rt[u], 1, depmax, dep[u], sz[u] - 1);
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	n = read(); q = read();
	for(int i = 1; i < n; ++i)
	{
		int x = read(), y = read();
		add(x, y);
	}
	dfs_set(1, 0);
	for(int i = 1; i <= q; ++i)
	{
		int x = read(), y = read();
		Q[x].push_back((node){y, i});
		ans[i] += 1LL * min(dep[x] - 1, y) * (sz[x] - 1);
	}
	dfs_calc(1, 0);
	for(int i = 1; i <= q; ++i) printf("%lld\n", ans[i]);
	return 0;
}
/*
思路：
关于这种树上结构查询子树内满足特殊条件的点，可以尝试线段树合并。
先离线询问，dfs一遍时把儿子的线段树合并，线段树的值域为dep，同时查询答案，再将自己update进去
*/
