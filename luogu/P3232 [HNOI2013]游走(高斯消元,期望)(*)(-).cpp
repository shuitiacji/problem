#include<bits/stdc++.h>
using namespace std;
const int maxn = 510, maxm = maxn * maxn;
int to[maxm], nxt[maxm], head[maxn];
double a[maxn][maxn], num[maxn], F[maxn], tmp[maxm];
pair<int, int> E[maxm];
int n, m, e, tot;
void add(int x, int y)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e;
	to[++e] = x; nxt[e] = head[y]; head[y] = e;
	E[++tot].first = x; E[tot].second = y;
}
void gause()
{
	for(int i = 1; i <= n; ++i)
	{
		int r = i;
		for(int j = i + 1; j <= n; ++j)
			if(fabs(a[j][i]) > fabs(a[r][i])) r = j;
		if(r != i) for(int j = 1; j <= n + 1; ++j) swap(a[r][j], a[i][j]);
		for(int j = i + 1; j <= n; ++j)
		{
			double f = a[j][i] / a[i][i];
			for(int k = i; k <= n + 1; ++k)
				a[j][k] -= f * a[i][k];
		}
	}
	for(int i = n; i >= 1; --i)
	{
		for(int j = i + 1; j <= n; ++j)
			a[i][n + 1]	-= a[j][n + 1] * a[i][j];
		a[i][n + 1] /= a[i][i];
	}
	for(int i = 1; i <= n; ++i)
		F[i] = a[i][n + 1];
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	for(int i = 1; i <= n; ++i)
		for(int j = head[i]; j; j = nxt[j])
			num[i] += 1.0;
	for(int i = 1; i <= n; ++i)
	{
		for(int j = head[i]; j; j = nxt[j])
		{
			int v = to[j]; if(v == n) continue;
			a[i][v] = 1. / num[v];
		}
		a[i][i] = -1;
		if(i == 1) a[i][n + 1] = -1.0;
	}
	gause();
	for(int i = 1; i <= m; ++i)
	{
		if(E[i].first != n) tmp[i] += F[E[i].first] / num[E[i].first];
		if(E[i].second != n) tmp[i] += F[E[i].second] / num[E[i].second];
	}
	sort(tmp + 1, tmp + m + 1);
	double ans = 0;
	for(int i = 1; i <= m; ++i)
		ans += tmp[i] * (double)(m - i + 1);
	printf("%.3lf\n", ans);
	return 0;
}
/*
题意：
一个无向连通图，顶点从1编号到N，边从1编号到M。 小Z在该图上进行随机游走，初始时小Z在1号顶点，每一步小Z以相等的概率随机选 择当前顶点的某条边，沿着这条边走到下一个顶点，获得等于这条边的编号的分数。当小Z 到达N号顶点时游走结束，总分为所有获得的分数之和。 现在，请你对这M条边进行编号，使得小Z获得的总分的期望值最小。

思路：
很容易就能看出这是一道期望题
我们要知道每条边被经过的期望值，然后期望值小的给一个比较大的编号
怎么求每条边被经过的期望值？
每条边是否被经过只由它所连接的两端节点决定
由于每个点到与之相连的任意一条边的期望相等，所以到某条特定的边的期望就是经过这个点的期望值乘上 1 / 该点的总边数
那么一条边被经过的期望就应该是两端点到这条边的期望值之和
那么我们就将求边的期望转化为求点的期望
显然的,可以看出每个点的期望是由与其相连的点的经过的期望决定的
设 f[x] 为点 x 的期望, num[x] 为点 x 的总边数, f[x] = sigma(f[i] / num[i]) (i为与x相邻点的编号)
每个点都能够列出这样一个方程
直接用高斯消元法解即可
注意
点 1 与点 n 有些特殊
由于"游走"是从点 1 开始,则计算点 1 期望时实际期望应该是原期望+1
若有点和 n 相连,那么在计算期望时是不需要将其算入的,因为到了点 n 的时候是不会继续"游走"了
注意这两个点,就没有什么问题了
记得将每条边的两端存起来这样最后计算每条边的期望就很简单了

这个边转点的套路可以学习一波
*/
