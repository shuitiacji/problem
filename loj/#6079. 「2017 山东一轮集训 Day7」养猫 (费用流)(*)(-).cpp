#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1010, maxm = maxn << 4;
int d, s, t;
struct cost_flow
{
	int e;
	LL COST, FLOW;
	LL dis[maxn];
	int inq[maxn], to[maxm], nxt[maxm], head[maxn], cost[maxm], from[maxm], p[maxn], a[maxn], cap[maxm], flow[maxm];
	void add(int x, int y, int z, int Z)
	{
		to[++e] = y; nxt[e] = head[x]; head[x] = e; cap[e] = z; cost[e] = Z; from[e] = x;
		to[++e] = x; nxt[e] = head[y]; head[y] = e; cap[e] = 0; cost[e] = -Z; from[e] = y;
	}
	int spfa()
	{
		for(int i = s; i <= d; ++i) dis[i] = (int) 1e18;
		dis[s] = 0; a[s] = 0x3f3f3f3f;p[s] = 0; inq[s] = 1;
		queue<int> q; q.push(s);
		while(!q.empty())
		{
			int u = q.front(); q.pop();
			inq[u] = 0;
			for(int i = head[u]; i != -1; i = nxt[i])
			{
				int v = to[i];
				if(dis[v] > dis[u] + cost[i] && flow[i] < cap[i])
				{
					p[v] = i; dis[v] = dis[u] + cost[i]; a[v] = min(a[u], cap[i] - flow[i]); 
					if(!inq[v]) q.push(v), inq[v] = 1;
				}
			}
		}
		if(dis[t] == (int) 1e18) return 0;
		FLOW += a[t]; COST += 1LL * a[t] * dis[t];
		int u = t;
		while(u != s) { flow[p[u]] += a[t]; flow[p[u] ^ 1] -= a[t]; u = from[p[u]]; }
		return 1;
	}
}G;
int S[maxn], e[maxn], now[maxn];
int n, k, ms, me;
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	memset(G.head, -1, sizeof(G.head));
	G.e = -1;
	scanf("%d%d%d%d", &n, &k, &ms, &me);
	for(int i = 1; i <= n; ++i) scanf("%d", &S[i]);
	for(int i = 1; i <= n; ++i) scanf("%d", &e[i]);
	d = n + 2; s = 0; t = n + 1;
	G.add(s, d, k - ms, 0);
	for(int i = 1; i <= k; ++i)
		G.add(d, i, 1, 0);
	LL ans = 0;
	for(int i = 1; i <= n; ++i)
	{
		ans += S[i];
		G.add(i, min(i + k, n + 1), 1, S[i] - e[i]); now[i] = G.e - 1;
		G.add(i , i + 1, k - ms - me, 0);
	}
	while(G.spfa());
	cout << ans - G.COST << endl;
	for(int i = 1; i <= n; ++i) if(G.flow[now[i]]) cout << 'E'; else cout << 'S';
	return 0;
}
/*
题意：
你养了一只猫，为了让它快乐地成长，你需要合理地安排它每天的作息时间。假设一天分为 n 个时刻，猫在每个时刻要么是吃东西，要么是睡觉。在第 i 个时刻，假如猫是去吃东西，那么它能获得愉悦值 ei ，假如是去睡觉，那么能获得的愉悦值为 si.
猫要成长，不仅仅需要快乐，还需要健康的作息。经过研究，对于每一个连续的长度为 k 的作息区间，即所有的时刻区间 [i,i+k−1],1≤i≤n−k+1，猫都要至少有 ms 的时刻用来睡觉，me 的时刻用来吃东西，这样猫才能健康成长。
现在你想合理地安排一天中的这n个时刻，使得猫在能健康成长的前提下，获得尽量多的愉悦值。

思路：
首先强制让猫每天都睡觉,然后考虑用最小的代价将其中一些点改成吃饭,并使其符合条件。
设源点为 s, 汇点为 t,并设一个辅助点d
首先 s向 d连流量为 k - ms的边,表示你每个⻓度为 k的区间最多能更改这么多点
向前 k个点连流量为一的边
每个点 i向min(i + k, t)连费用为si - ei（表示此点要吃饭）
每个点 i向 i + 1连容量为k - ms - me的边。（流断后来限制流，使得部分流走有花费的边）
这种断流后，使得部分流走费用边，是费用流一种常见的套路

*/
