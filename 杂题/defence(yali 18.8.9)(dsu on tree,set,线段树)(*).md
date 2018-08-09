### Desription

A 国的各个城邦正在修建大规模防御工事, 工事可以抽象为一个长度为 M 的 01 序列, 初始时每个位置均为 0, 称一个防御工事是好的当且仅当序列上的每个位置都是 1.
要操作这个工事有两套系统, 符咒和法术, 法术可以将序列的某个位置变成 1, 每个符咒可以将序列中每个 1 左边的 0 变成 1, 或者将序列中每个 1右边的 0 变成 1.
这 N 个城邦间存在管辖关系, 构成一棵以 1 为根的有根树. 对于第 i个城邦掌握的法术, 管辖它的所有城邦也能掌握. 现在 A 国的所有城主想让你告诉他们, 对于他们的城邦, 要将防御工事变成好的最少需要消耗多少符咒.

### Solution

首先显然会把法术全部放完再考虑符咒, 考虑放完法术后的 01 序列:假设 L 是前缀 0 的数量, R 是后缀 0 的数量, M 是最长的连续 0 的数量,显然答案就是$max\{L + R, M\}$

直接上dsu on tree，用个set维护即可(查前继后继)，最大值M为了卡常用权值线段树维护

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
const int maxn = 1e5 + 10, maxm = maxn;
set<int> xz;
int to[maxn << 1], nxt[maxn << 1], head[maxn], e;
int ans[maxn], cnt[maxm], sz[maxn], son[maxn];
vector<int> val[maxn];
int n, m, q;
void add(int x, int y)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e;
	to[++e] = x; nxt[e] = head[y]; head[y] = e;
}
namespace SGT
{
	int t[maxm << 2];
	void upt(int o, int l, int r, int p, int v)
	{
		t[o] += v;
		if(l == r) return;
		int mid = (l + r) >> 1;
		if(p <= mid) upt(o << 1, l, mid, p, v);
		else upt(o << 1 | 1, mid + 1, r, p, v);
	}
	int que(int o, int l, int r)
	{
		if(l == r) return l;
		int mid = (l + r) >> 1, tmp = t[o << 1 | 1];
		if(tmp > 0) return que(o << 1 | 1, mid + 1, r);
		else return que(o << 1, l, mid);
	}
}
void dfs(int u, int fa)
{
	sz[u] = 1;
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs(v, u);
/**/	if(!son[u] || sz[son[u]] < sz[v]) son[u] = v;
		sz[u] += sz[v];
	}
}
int sum;
void Add(int u)
{
	for(int i = 0; i < val[u].size(); ++i)
	{
		int v = val[u][i];
		cnt[v]++;
		if(cnt[v] == 1) { 
			sum++;
/**/		set<int> :: iterator it1 = xz.upper_bound(v), it2 = it1;
			it2--;
			if(*it2 != -1 && *it1 != m + 1)
				SGT::upt(1, 0, m, *it1 - *it2 - 1, -1); 
			if(*it1 != m + 1)
				SGT::upt(1, 0, m, *it1 - v - 1, 1); 
			if(*it2 != -1)
				SGT::upt(1, 0, m, v - *it2 - 1, 1);
			xz.insert(v);
		}
	}
}
void Del(int u)
{
	for(int i = 0; i < val[u].size(); ++i)
	{
		int v = val[u][i];
		cnt[v]--;
		if(cnt[v] == 0)
		{
			sum--;
/**/		set<int> :: iterator it1 = xz.upper_bound(v), it2 = it1;
			--(--it2);
			if(*it2 != -1 && *it1 != m + 1)
				SGT::upt(1, 0, m, *it1 - *it2 - 1, 1);
			if(*it1 != m + 1) 
				SGT::upt(1, 0, m, *it1 - v - 1, -1);
			if(*it2 != -1)
				SGT::upt(1, 0, m, v - *it2 - 1, -1);
			xz.erase(++it2);
		}
	}
}
void dfs_set(int u, int fa, int fg)
{
	if(fg) Add(u);
	else Del(u);
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
	if(son[u]) dsu(son[u], u, 1);
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa || v == son[u]) continue;
		dfs_set(v, u, 1);
	}
	Add(u);
	if(sum == 0) { ans[u] = -1; if(keep == 0) dfs_set(u, fa, 0); return; }
	int Min = *(++xz.begin()), Max = *(--(--xz.end()));
	ans[u] = max(Min - 1 + (m - Max), SGT::que(1, 0, m));
	if(keep == 0) dfs_set(u, fa, 0);
}
int main()
{
	n = read(); m = read(); q = read();
	for(int i = 1; i < n; ++i)
	{
		int x = read() , y = read();
		add(x, y);
	}
	xz.insert(-1); xz.insert(m + 1);
	for(int i = 1; i <= q; ++i) { int x = read(), y = read(); val[x].push_back(y); }
	dfs(1, 0);
	dsu(1, 0, 1);
	for(int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
	return 0;
}

```

### Debug

1.48行，写成v=son[u]

2.61行，82行，不能写it2 = --it1，会把it1的值也改掉

