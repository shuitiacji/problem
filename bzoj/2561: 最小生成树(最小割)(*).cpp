#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 1) + (x << 3) + (c ^ 48); c = getchar(); }
	return x * f;
}
const int maxn = 2e4 + 10, maxm = (int)(2e5 + 10) << 2;
int s, t;
int m, n;
struct dinic
{
	int e;
	int to[maxm], nxt[maxm], head[maxn], cap[maxm], vis[maxn], d[maxn], flow[maxm], cur[maxn];
	void add(int x, int y, int z)
	{
		to[++e] = y; nxt[e] = head[x]; head[x] = e; cap[e] = z;
		to[++e] = x; nxt[e] = head[y]; head[y] = e; cap[e] = 0;
	}
	int bfs()
	{
		memset(vis, 0, sizeof(vis));
		d[s] = 0; vis[s] = 1;
		queue<int> q; q.push(s);
		while(!q.empty())
		{
			int u = q.front(); q.pop();
			for(int i = head[u]; i != -1; i = nxt[i])
			{
				int v = to[i];
				if(vis[v] || cap[i] == flow[i]) continue;
				d[v] = d[u] + 1; vis[v] = 1; q.push(v);
			}
		}
		return vis[t];
	}
	int dfs(int x, int a)
	{
		if(x == t || a == 0) return a;
		int FLOW = 0, f;
		for(int &i = cur[x]; i != -1; i = nxt[i])
		{
			int v = to[i];
			if(d[v] == d[x] + 1 && ((f = dfs(v, min(a, cap[i] - flow[i]))) > 0)) 
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
			for(int i = 1; i <= n; ++i) cur[i] = head[i];
			ret += dfs(s, 0x3f3f3f3f);
		}
		return ret;
	}
}G1, G2;
struct edge
{
	int x, y, z;
}e[maxm];
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	n = read(); m = read();
	for(int i = 1; i <= m; ++i)
		e[i].x = read(), e[i].y = read(), e[i].z = read();
	s = read(); t = read(); int k = read();
	int ans = 0;
	memset(G1.head, -1, sizeof(G1.head));
	memset(G2.head, -1, sizeof(G2.head));
	G1.e = -1; G2.e = -1;
	for(int i = 1; i <= m; ++i)
		if(e[i].z < k) G1.add(e[i].x, e[i].y, 1), G1.add(e[i].y, e[i].x, 1);
		else if(e[i].z > k) G2.add(e[i].x, e[i].y, 1), G2.add(e[i].y, e[i].x, 1);
	ans += G1.gao() + G2.gao();
	cout << ans << endl;
	return 0;
}
/*
题意:
给定一个边带正权的连通无向图G=(V,E)，其中N=|V|，M=|E|，N个点从1到N依次编号，给定三个正整数u，v，和L (u≠v)，假设现在加入一条边权为L的边(u,v)，那么需要删掉最少多少条边，才能够使得这条边既可能出现在最小生成树上，也可能出现在最大生成树上？

思路:
以最小生成树为例。把所有小于L的边取出来，显然这些边不能连通u和v，否则将u和v连起来在环上去掉L显然更小。所以求一个最小割就行了。最大生成树同理，两者相加就是答案。
*/
