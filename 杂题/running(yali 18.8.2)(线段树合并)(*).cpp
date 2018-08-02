#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0, f = 1; char c = getchar(); 
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
const int mod = 998244353, maxn = 1e5 + 10, maxm = maxn << 1;
typedef long long LL;
int n, maxdep;
int t[maxn * 60], ls[maxn * 60], rs[maxn * 60];
LL ans;
int sz[maxn], dep[maxn], f[maxn], rt[maxn], e, tot;
int head[maxn], nxt[maxm], to[maxm], w[maxn];
vector<int> vec1[maxn];
vector<pair<int, int> > vec[maxn];
void add(int x, int y)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e;
	to[++e] = x; nxt[e] = head[y]; head[y] = e;
}
void upt(int &o, int l, int r, int p, int v)
{
	if(!o) o = ++tot;
	if(l == r) { t[o] += v; return ; }
	int mid = (l + r) >> 1;
	if(p <= mid) upt(ls[o], l, mid, p, v);
	else upt(rs[o], mid + 1, r, p, v);
}
int que(int o, int l, int r, int p)
{
	if(!o) return 0;
	if(l == r) 
	{
/**/	if(l != p) return 0;
		return t[o];
	}
	int mid = (l + r) >> 1;
	if(p <= mid) return que(ls[o], l, mid, p);
	else return que(rs[o], mid + 1, r, p);
}
int merge(int x, int y, int l, int r)
{
	if(!x || !y) return x | y;
	if(l == r) { t[x] += t[y]; return x; }
	int mid = (l + r) >> 1;
	ls[x] = merge(ls[x], ls[y], l, mid);
	rs[x] = merge(rs[x], rs[y], mid + 1, r);
	return x;
}
void dfs_init(int u, int fa)
{
	dep[u] = dep[fa] + 1; f[u] = fa; sz[u] = 1;
	maxdep = max(dep[u], maxdep);
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs_init(v, u);
		sz[u] += sz[v];
	}
}
void dfs_seg(int u, int fa)
{
/**/upt(rt[u], 1, maxdep, dep[u], 1);
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs_seg(v, u);
/**/	ans += 1LL * que(rt[v], 1, maxdep, dep[u] + w[u]) * (n - sz[v]);
		rt[u] = merge(rt[u], rt[v], 1, maxdep);
	}
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		for(int j = 0; j < vec[v].size(); ++j)
			ans += 1LL * (que(rt[u], 1, maxdep, vec[v][j].first) - vec1[v][j]) * vec[v][j].second;
	}
	for(int j = 0; j < vec[u].size(); ++j) vec1[u].push_back(que(rt[u], 1, maxdep, vec[u][j].first));
}
LL Pow(LL x, int p)
{
/**/x %= mod;
	LL r = 1;
	while(p)
	{
		if(p & 1) r = x * r % mod;
		x = x * x % mod; p >>= 1;
	}
	return r;
}
int main()
{
	freopen("running.in", "r", stdin);
	freopen("running.out", "w", stdout);
	n = read();
	for(int i = 1; i <= n - 1; ++i)
	{
		int x = read(), y = read();
		add(x, y);
	}
	for(int i = 1; i <= n; ++i) w[i] = read();
	dfs_init(1, 0);
/**/for(int i = 1; i <= n; ++i) ans += (w[i] == 0 ? 1 : 0) * n;
	for(int i = 1; i <= n; ++i)
	{
		int r = i;
		while(r != 1)
		{
			int fa = f[r];
			vec[r].push_back(make_pair(2 * dep[fa] - dep[i] + w[i], sz[i]));
			r = fa;
		}
	}
	dfs_seg(1, 0);
	LL TMP = Pow(1LL * n * n, mod - 2);
	printf("%lld\n", ans * TMP % mod);
	return 0;
}
/*
题意：
给定天天爱跑步的观察员，但是现在不是求一条链会被观察几次，而是问随机选取起点终点构成的链会被观察多少次的期望
数据保证树随机

思路：
抛开它的期望，这其实是道计数题

考虑链不固定（即有很多，n^2条），枚举观察员来算它对答案的贡献（即有多少条链被它观察到了）
分两种情况考虑
1.链的起点在这个观察员(i)的子树中
显然这个子树中深度为dep[i] + w[i]的点可以为起点
这里要枚举i的儿子v,对答案的贡献为(v子树中深度为dep[i] + w[i]的点数) * (n - sz[v]) （这里之所以要枚举v，是因为有可能终点也在i的子树中）

2.链的起点不在这个观察员(i)的子树中
假设此时可行的起点是u
显然这个时候要去枚举u与i的lca，才能判断u到底可不可行
因为树的形态随机，深度为期望logn
于是可以枚举i的祖先，也就是枚举lca，假设i一步步跳上来的lca的那个儿子为i`，对答案的贡献就是(lca中除去包括i`的那个子树的其他子树中深度为2 * dep[lca] - dep[i] + w[i]的点数) * sz[i]

实现直接线段树合并即可

debug:
1.37行，如果查询的东西超过了线段树的范围，必须要写上这个东西
2.这题必须把询问挂上去，不能在线搞，因为线段树合并时，当几颗树合并到一起去时，他们的原状态不能保证，因为共用了节点，当后面改变父亲状态时，改变了共有节点，直接会改变原来的状态
3.87
4.108，w[i] = 0的情况要特殊搞
*/
