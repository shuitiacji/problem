#include<bits/stdc++.h>
using namespace std;
const int maxn = 2010, maxm = 2e5;
const int inf = 100000000;
int s, t;
struct cost_flow
{
	int e, COST, FLOW;
	int to[maxm], nxt[maxm], head[maxn], cap[maxm], cost[maxm], from[maxm], dis[maxn], a[maxn], inq[maxn], p[maxn], flow[maxm];
	void add(int x, int y, int z, int Z)
	{
		to[++e] = y; nxt[e] = head[x]; head[x] = e; cap[e] = z; cost[e] = Z; from[e] = x;
		to[++e] = x; nxt[e] = head[y]; head[y] = e; cap[e] = 0; cost[e] = -Z; from[e] = y;
	}
	int spfa()
	{
		memset(dis, 0x3f, sizeof(dis));
		inq[s] = 1; dis[s] = 0; p[s] = 0; a[s] = 0x3f3f3f3f;
		queue<int> q; q.push(s);
		while(!q.empty())
		{
			int u = q.front(); q.pop();
			for(int i = head[u]; i != -1; i = nxt[i])
			{
				int v = to[i];
				inq[v] = 0;
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
		while(u != s) { flow[p[u]] += a[t]; flow[p[u] ^ 1] -= a[t]; u = from[p[u]]; }
		return 1;
	}
}G;
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	memset(G.head, -1, sizeof(G.head));
	G.e = -1;
	int n, m;
	scanf("%d%d", &n, &m);
	s = 0; t = n + 2;	
	for(int i = 1; i <= n; ++i)
	{
		int x; scanf("%d", &x);
		G.add(i, i + 1, inf - x, 0);
	}
	G.add(s, 1, inf, 0); G.add(n + 1, t, inf, 0);
	for(int i = 1; i <= m; ++i)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		G.add(x, y + 1, inf, z);
	}
	while(G.spfa());
	cout <<	G.COST << endl;	
	return 0;
}
/*
题意:
申奥成功后，布布经过不懈努力，终于成为奥组委下属公司人力资源部门的主管。布布刚上任就遇到了一个难题：为即将启动的奥运新项目招募一批短期志愿者。经过估算，这个项目需要N 天才能完成，其中第i 天至少需要Ai 个人。 布布通过了解得知，一共有M 类志愿者可以招募。其中第i 类可以从第Si 天工作到第Ti 天，招募费用是每人Ci 元。新官上任三把火，为了出色地完成自己的工作，布布希望用尽量少的费用招募足够的志愿者，但这并不是他的特长！于是布布找到了你，希望你帮他设计一种最优的招募方案。

思路:
可以化成一个有下界的费用流.
这里有个很巧妙的解决下界问题的套路
把天数化成一条链,第i天对i + 1天连一条容量为inf - a[i]费用为0的边,s对第1天连容量为inf费用为0的边,第n + 1天对t连容量为inf费用为0的边.对于志愿者,在si与ti + 1连一条容量为inf,费用为ci的边.
这样从源点向最后一个时间点跑费用流，如果满流就说明符合条件，此时的费用就是最小的费用。 
我们注意到inf - a[i] 相当于定义了这个点的下界,流断了这条边时这就相当于少了a[i]得用带权边补全INF
*/
