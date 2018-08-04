#include<bits/stdc++.h>
using namespace std;
const int maxn = 500010, maxm = maxn << 1;
int n, to[maxm], nxt[maxm], head[maxn], e;
double f[maxn], q[maxn], w[maxm], g[maxn]; 
void add(int x, int y, double z)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e; w[e] = z;
	to[++e] = x; nxt[e] = head[y]; head[y] = e; w[e] = z;
}
void dfs1(int u, int fa)
{
	f[u] = 1 - q[u];
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs1(v, u);
/**/	f[u] *= f[v] + (1 - f[v]) * (1 - w[i]);
	}
}
void dfs2(int u, int fa)
{
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		double t = g[u] * f[u] / (f[v] + (1 - f[v]) * (1 - w[i]));
		g[v] = t + (1 - t) * (1 - w[i]);
		dfs2(v, u);
	}
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i < n; ++i)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		add(x, y, z / 100.);
	}
	for(int i = 1; i <= n; ++i) { int q1; scanf("%d", &q1); q[i] = q1 / 100.; }
	g[1] = 1.;
	dfs1(1, 0);
	dfs2(1, 0);
	double ans = 0;
	for(int i = 1; i <= n; ++i) ans += (1 - g[i] * f[i]);
	printf("%.6lf\n", ans);
	return 0;
}
/*
题意：
著名的电子产品品牌SHOI 刚刚发布了引领世界潮流的下一代电子产品—— 概率充电器：
“采用全新纳米级加工技术，实现元件与导线能否通电完全由真随机数决 定！SHOI 概率充电器，您生活不可或缺的必需品！能充上电吗？现在就试试看 吧！”
SHOI 概率充电器由n-1 条导线连通了n 个充电元件。进行充电时，每条导 线是否可以导电以概率决定，每一个充电元件自身是否直接进行充电也由概率 决定。随后电能可以从直接充电的元件经过通电的导线使得其他充电元件进行 间接充电。
作为SHOI 公司的忠实客户，你无法抑制自己购买SHOI 产品的冲动。在排 了一个星期的长队之后终于入手了最新型号的SHOI 概率充电器。你迫不及待 地将SHOI 概率充电器插入电源——这时你突然想知道，进入充电状态的元件 个数的期望是多少呢？

思路：
由于这是个树，考虑树形dp
考虑状态的设计，因为正着考虑不好算，因为一个点会被充电是只要与它相连的有一个有电就行，是一个或的关系，无法将与它相连的有电的概率简单相加或相乘，所以要记一个点没电的概率
现在一个点有电的情况：
他自己给自己充电
他的儿子给他充电
他的爸爸给他充电
(这里将儿子与爸爸分开，是利用了树形dp的思想，巧妙的解决了相邻两个点的状态会互相影响的问题)
状态：
f[x]他儿子或他自己不给他充电的概率
g[x]他爸爸不给他充电的概率

先处理f，显然每个点的f初值为(1 - q[x])即自己不直接有电，然后找它的儿子乘上f[v] + (1 - f[v]) * (1 - w[i])
再处理g，设t为当前fa[x]没电的概率
t = g[fa] * f[fa]
这样是有问题的，因为我们要算x没电的概率，有个x没电的前提，而f[fa]中显然算了f[x] + (1 - f[x]) * (1 - w[i])
所以t还要除以个f[x] + (1 - f[x]) * (1 - w[i])
最后g[x] = t + (1 - t) * (1 - w[i])

ans += sigma(1 - f[i] * g[i])

debug:
1.19行要写在18行后
*/
