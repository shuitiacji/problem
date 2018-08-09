### Description

给定你一个图，要求将其划分成两个点集，使得两个子集都是完全图，且使得属于两个完全图的边数最少，无重边自环

<!--more-->

### Solution

 对完全图，考虑它的补图。把它的补图建出来后，一条边相连的两条边显然不能在一个点集中，因为总共两个点集，所以它的补图显然是二分图，根据二分图染色来判无解

由于补图不连通，对于每一个联通块的二分图，同一种颜色的只能放在同一点集里，而不同的联通块则没有要求

这个直接用bitset维护即可，$f[i]$表示点数为$i$的点集是否存在，对于每个联通块，$a[i],b[i]$分别表示该联通块两种颜色个数
$$
f = (f << a[i]) | (f << b[i])
$$
贪心地使两个点集的个数接近即可，即从$n/2$从大到小贪心取

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 710, maxm = maxn * maxn;
int tot, e, n, m; 
int vis[maxn], a[maxn], b[maxn], E[maxn][maxn], c[maxn];
bitset<maxn> f;
int to[maxm], nxt[maxm], head[maxn];
void add(int x, int y)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e;
	to[++e] = x; nxt[e] = head[y]; head[y] = e;
}
int dfs(int x, int col)
{
	vis[x] = 1;
	c[x] = col;
	if(col) a[tot]++; else b[tot]++;
	for(int i = head[x]; i; i = nxt[i])
	{
		int v = to[i];
		if(vis[v]) { if(c[v] == col) return 0; }
		else if(!dfs(v, col ^ 1)) return 0;
	}
	return 1;
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i)
	{
		int x, y; scanf("%d%d", &x, &y);
		E[x][y] = 1; E[y][x] = 1;
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j < i; ++j)
			if(!E[i][j]) add(i, j);
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
		{
			++tot;
			if(!dfs(i, 0)) { puts("-1"); return 0; }
		}
	f[0] = 1;
	for(int i = 1; i <= tot; ++i) f = (f << a[i]) | (f << b[i]);
	for(int i = n / 2; i >= 0; --i)
		if(f[i]) 
		{	
			printf("%d\n", i * (i - 1) / 2 + (n - i) * (n - i - 1) / 2);
			return 0;
		}
	return 0;
} 
```



