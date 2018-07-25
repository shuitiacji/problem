#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10, maxm = maxn << 2;
int s, t, m, n;
int d[100][100];
struct cost_flow
{
	int e, COST, FLOW;
	int to[maxm], nxt[maxm], head[maxn], cap[maxm], from[maxm], flow[maxm], dis[maxn], a[maxn], inq[maxn], p[maxn], cost[maxm];
	void add(int x, int y, int z, int Z)
	{
		to[++e] = y; nxt[e] = head[x]; head[x] = e; cap[e] = z; cost[e] = Z; from[e] = x;
		to[++e] = x; nxt[e] = head[y]; head[y] = e; cap[e] = 0; cost[e] = -Z; from[e] = y;
	}
	int spfa()
	{
		memset(dis, 0x3f, sizeof(dis));
		memset(inq, 0, sizeof(inq));
		dis[s] = 0; p[s] = 0; a[s] = 0x3f3f3f3f; inq[s] = 1;
		queue<int> q; q.push(s);
		while(!q.empty())
		{
			int u = q.front(); q.pop();
/**/		inq[u] = 0;
			for(int i = head[u]; i != -1; i = nxt[i])
			{
				int v = to[i];
				if(dis[v] > dis[u] + cost[i] && flow[i] < cap[i])
				{
					dis[v] = dis[u] + cost[i];
					a[v] = min(a[u], cap[i] - flow[i]);
					p[v] = i;
					if(!inq[v]) q.push(v), inq[v] = 1;
				}
			}
		}
		if(dis[t] == 0x3f3f3f3f) return 0;
		FLOW += a[t]; COST += a[t] * dis[t];
		int u = t;
		while(u != s)
			flow[p[u]] += a[t], flow[p[u] ^ 1] -= a[t], u = from[p[u]];
		return 1;	
	}
}G;
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d", &m, &n);
	s = 0; t = m * n + n + 1;
	G.e = -1; memset(G.head, -1, sizeof(G.head));
	for(int i = 1; i <= n; ++i) G.add(i + n * m, t, 1, 0);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) 
			scanf("%d", &d[j][i]);
	for(int i = 1; i <= m; ++i)
		for(int j = 1; j <= n; ++j)
		{
			int now = (i - 1) * n + j;
			for(int k = 1; k <= n; ++k) G.add(now, k + n * m, 1, j * d[i][k]);
			G.add(s, now, 1, 0);
		}
	while(G.spfa());
	double tmp = double(G.COST) / (double) n;
	printf("%.2lf\n", tmp);
	return 0;
}
/*
题意:
同一时刻有 N 位⻋主带着他们的爱⻋来到了汽⻋维修中心。维修中心共有 M 位技术人员,不同的技术人员对不同的
⻋进行维修所用的时间是不同的。现在需要安排这 M 位技术人员所维修的⻋及顺序,使得顾客平均等待的时间最小。
说明:顾客的等待时间是指从他把⻋送至维修中心到维修完毕所用的时间。

思路:
两个不同的人修车是可以同时进行的,使得计算总时间变得复杂
这里有一个对付这种情况的套路
我们把每个修⻋师傅拆成 n 个点,对于第 a 个点, ak 代表在这个师傅这里是倒数第 k 个修⻋的,对答案的贡献为k * T,把这个作为费用即可

debug:
24行
*/
