#include<bits/stdc++.h>
using namespace std;
const int maxn = 310, maxm = 310 * 310 * 5;
int n, m, s, t;
struct dinic
{
	int e;
	int to[maxm], nxt[maxm], head[maxn], cap[maxm], vis[maxn], flow[maxm], cur[maxn], d[maxn];
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
			if(d[v] == d[u] + 1 && (f = dfs(v, min(a, cap[i] - flow[i])) >0)) 
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
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	memset(G.head, -1, sizeof(G.head));
	G.e = -1;
	scanf("%d%d", &n, &m);
	s = 0; t = n + 1;
	for(int i = 1; i <= n; ++i) 
	{
		int x; scanf("%d", &x);
		if(x == 1) G.add(s, i, 1);
		else G.add(i, t, 1);
	}
	for(int i = 1; i <= m; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		G.add(x, y, 1); G.add(y, x, 1);
	}
	cout << G.gao() << endl;
	return 0;
}
/*
题意:
幼儿园里有n个小朋友打算通过投票来决定睡不睡午觉。对他们来说，这个问题并不是很重要，于是他们决定发扬谦让精神。虽然每个人都有自己的主见，但是为了照顾一下自己朋友的想法，他们也可以投和自己本来意愿相反的票。我们定义一次投票的冲突数为好朋友之间发生冲突的总数加上和所有和自己本来意愿发生冲突的人数。
我们的问题就是，每位小朋友应该怎样投票，才能使冲突数最小？

思路:
问题与意愿有关,每个人有选择主见与违背两种选择,且与他人的状态有关
容易想到以意愿建'二分图'(不能说是二分图,同一部其实也有连边),最小割来表示选不选
实现时这样建图：直接将S连向同意的人，T连向不同意的人，若两人是朋友，则在他们之间连一条双向边（这里有些人不理解：若两个人有冲突，则只需要其中任意一个人改变意见就行了，简单说是让a同意b的意见或者b同意a的意见，所以只需割掉一条边满足一种情况就可以了，但是有两种情况，所以建双向边,即有可能在二分图的同一部中有连边,若xy中,x被割即x改变意见,x->y就不会割,但y被割也有情况,所以y->x也要建）。最后就是求最小割了，直接套上最大流的模板就ok了。

*/
