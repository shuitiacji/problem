#include<bits/stdc++.h>
using namespace std;
int n, m, k, s, t;
const int maxn = 510, maxm = maxn * maxn * 4;
int A[maxn][maxn];
struct dinic
{
	int e;
	int to[maxm], nxt[maxm], head[maxn], flow[maxm], cap[maxm], d[maxn], vis[maxn], cur[maxn];
	void add(int x, int y, int z)
	{
		to[++e] = y; nxt[e] = head[x]; head[x] = e; cap[e] = z;
/**/	to[++e] = x; nxt[e] = head[y]; head[y] = e; cap[e] = 0;
	}
	void init()
	{
		e = -1;
		memset(head, -1, sizeof(head));
		memset(flow, 0, sizeof(flow));
	}
	int bfs()
	{
		memset(vis, 0, sizeof(vis));
		vis[s] = 1; d[s] = 0;
		queue<int> q; q.push(s);
		while(!q.empty())
		{
			int u = q.front(); q.pop();
			for(int i = head[u]; i != -1; i = nxt[i])
			{
				int v = to[i];
				if(vis[v] || flow[i] == cap[i]) continue;
				d[v] = d[u] + 1; vis[v] = 1; q.push(v);
			}
		}
		return vis[t];
	}
	int dfs(int u, int a)
	{
		if(u == t || a == 0) return a;
		int FLOW = 0, f;
		for(int &i = cur[u]; i != -1; i = nxt[i])
		{
			int v = to[i];
			if(d[v] == d[u] + 1 && (f = dfs(v, min(a, cap[i] - flow[i]))) > 0)
			{
				FLOW += f;
				flow[i] += f; flow[i ^ 1] -= f;
				a -= f;
				if(a == 0) break;
			}
		}
		return FLOW;
	}
	int gao()
	{
		int ret = 0;
		while(bfs())
		{
			for(int i = s; i <= t; ++i) cur[i] = head[i];
			ret += dfs(s, 0x3f3f3f3f);
		}
		return ret;
	}
}G;
int ck(int x)
{
	G.init();
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			if(A[i][j] <= x) G.add(i, j + n, 1);
	for(int i = 1; i <= n; ++i) G.add(s, i, 1);
	for(int i = 1; i <= m; ++i) G.add(i + n, t, 1);
	return G.gao() >= n - k + 1;
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			scanf("%d", &A[i][j]);
	int l = 1, r = 1e9, ans = -1;
	s = 0; t = n + m + 1;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(ck(mid)) { r = mid - 1; ans = mid; }
		else l = mid + 1;
	}
	cout << ans << endl;
	return 0;
}
/*
题意:
小凸和小方是好朋友，小方给了小凸一个 n × m (n≤m) 的矩阵 A ，并且要求小凸从矩阵中选出 n 个数，其中任意两个数都不能在同一行或者同一列。现在小凸想知道，选出的 n 个数中第 k 大的数的最小值是多少。

思路:
不能在同一行,同一列,可以把行与列抽象成点,跑二分图匹配.
但这个题问的很奇怪,可以二分个答案,若矩阵a行b列的数小于等于二分中点，则由a行向b列连边,判断能不能取出 n-k+1 个 <=mid 的匹配

debug:
13行,写成cap[e] = z
*/
