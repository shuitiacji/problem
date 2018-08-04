#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10, maxm = 100;
vector<int> a;
typedef long long LL;
LL dp[maxm][maxm], d[maxn];
int n, m, q;
void add(int x, int y, LL z)
{
	dp[x][y] = min(dp[x][y], z);
	dp[y][x] = min(dp[x][y], z);
}
LL dis(int x, int y)
{
	if(x > y) swap(x, y);
	return min(d[y] - d[x], d[n + 1] - d[y] + d[x]);
}
LL gao(int x, int x1, int x2, int y, int y1, int y2)
{
	LL tmp = dp[y1][x1] + dis(a[x1], x) + dis(y, a[y1]);
	tmp = min(tmp, dp[y1][x2] + dis(a[x2], x) + dis(y, a[y1]));
	tmp = min(tmp, dp[y2][x1] + dis(a[x1], x) + dis(y, a[y2]));
	tmp = min(tmp, dp[y2][x2] + dis(a[x2], x) + dis(y, a[y2]));
	tmp = min(tmp, dis(x, y));
	return tmp;
}
struct node
{
	int x, y; LL z;
}e[maxm];
int main()
{
	freopen("fly.in", "r", stdin);
	freopen("fly.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) { int x; scanf("%d", &x), d[i + 1] += d[i] + x; }
	memset(dp, 0x3f, sizeof(dp));
/**/for(int i = 0; i <= 90; ++i) dp[i][i] = 0;
	for(int i = 1; i <= m; ++i)
	{
		int u, v; LL w;
		scanf("%d%d%lld", &u, &v, &w);
		a.push_back(u); a.push_back(v);
		e[i] = (node){u, v, w};
	}
	sort(a.begin(), a.end());
	vector<int>:: iterator it = unique(a.begin(), a.end());
	a.erase(it, a.end());
/**/for(int i = 0; i < (int)((int)a.size() - 1); ++i)
		add(i, i + 1, d[a[i + 1]] - d[a[i]]);
	if(a.size() > 1) add(0, a.size() - 1, d[n + 1] - d[a[a.size() - 1]] + d[a[0]]);
	for(int i = 1; i <= m; ++i)
		add(lower_bound(a.begin(), a.end(), e[i].x) - a.begin(), lower_bound(a.begin(), a.end(), e[i].y) - a.begin(), e[i].z);
	for(int i = 0; i < a.size(); ++i)
		for(int j = 0; j < a.size(); ++j)
			for(int w = 0; w < a.size(); ++w)
				dp[j][w] = min(dp[j][w], dp[j][i] + dp[i][w]);
	scanf("%d", &q);
	for(int i = 1; i <= q; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
/**/	if(m == 0) { printf("%lld\n", dis(u, v)); continue; }
		int x1 = lower_bound(a.begin(), a.end(), u) - a.begin() - 1;if(x1 <= -1) x1 = a.size() - 1;
		int x2 = lower_bound(a.begin(), a.end(), u) - a.begin(); if(x2 >= a.size()) x2 = 0;
		int y1 = lower_bound(a.begin(), a.end(), v) - a.begin() - 1; if(y1 <= -1) y1 = a.size() - 1;
		int y2 = lower_bound(a.begin(), a.end(), v) - a.begin(); if(y2 >= a.size()) y2 = 0;
		printf("%lld\n", gao(u, x1, x2, v, y1, y2));
	}
	return 0;
}
/*
题意：
现在,小hy和他的队员来到了卡塔尔。卡塔尔有 n 座城市,这些城市组成了一个环形。第 i 座城市与第 i + 1 座城市存在一条公路(第 n + 1 座城市视为第1 座城市),公路耗时为 d i ,并且公路双向。同时,城市群中有 m 条航线,每条航线连接两座城市,也需要耗时。航线的出发地、目的地与耗时均会给出。
世界杯的比赛会更换场馆,所以球员们需要奔波。显然,奔波时间越短,球员的精力就越好,战斗力就更强。于是,小hy产生了 q 个询问,对于每个询问,他想知道从城市 u 到城市 v 的最短耗时是多少,以便迅速更换场地。
因为小hy还要训练,所以这 q 个询问就交给你了。

思路：
考虑m <= 20，那么与航线有关的城市就不超过40座
直接只考虑这40座城市，并且把边只建到这些城市上
在这些城市上floyd
查询时，分别二分找到u,v左边的城市与右边的城市（就是那40座特殊的城市）
直接分4种情况找最小的即可

debug:
1.38,floyd初始化
2.49,.size()是unsighed的，如果size()=0，size() 又减一就会有问题
3.63，特判
*/
