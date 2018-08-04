#include<bits/stdc++.h>
using namespace std;
const int maxn = 22, maxm = maxn * maxn;
const int mod = 998244353;
int to[maxm], nxt[maxm], head[maxn], e;
int f[maxn][1 << maxn];
void add(int x, int y) { to[++e] = y; nxt[e] = head[x]; head[x] = e; }
int count(int x)
{
	return __builtin_popcount(x);
}
int main()
{
	freopen("match.in", "r", stdin);
	freopen("match.out", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
	}
	f[0][0] = 1;
	for(int i = 1; i <= n; ++i)
		for(int st = 0; st < (1 << n); ++st)
			if(count(st) == i - 1)
				for(int j = head[i]; j; j = nxt[j])
				{
					if((st & (1 << (to[j] - 1)))) continue;
					(f[i][st | (1 << (to[j] - 1))] += f[i - 1][st]) %= mod;
				}
	cout << f[n][(1 << n) - 1] << endl;
	return 0;
}
/*
题意：
现在是世界杯总决赛了,中国队vs德国队。但是德国队已经不行了,加上中
国队有世界第一前锋小hy,所以局面已经一边倒了。才过去笳笰分钟,中国队就
由小hy进了20个球,所以小hy已经心不在焉,开始想别的事情了。
他脑中的画面里出现了 n 个球员,他们有 m 个传球关系。所谓传球关系,是
指 u 号球员可以把球传给 v 号球员。现在小hy想问你有多少种方案,将球员分
成人数大于 1 的若干个集合,并且对于每个集合,其中的任意一个人拿球后,可
以经过不断的传球,使球经过集合中其他人脚下恰好一次,最后回到自己脚下。
由于方案数可能很大,小hy要求你将答案对998244353取模。

思路：
题目就是要找有向图环覆盖的方案数。
有向图环覆盖经典转化:拆点,将每个点拆成入点和出点,如果 u 向 v 连了
一条边,那么就将 u 的出点向 v 的入点连一条边。这样拆完点后构成了一个二分图。那么二分图的一个完美匹配,就是原图的一个环覆盖。
于是就变成了一个二分图完美匹配方案数问题。
考虑状压dp。
设 f [i][j] 表示二分图左边已经匹配了前 i 个点,右边的状态为 j 的方案数。
其中,j 是一个二进制数,二进制位上 1 代表已匹配,0 代表未匹配。
转移就很显然了。枚举 i ,再枚举 i − 1 时的 j 状态,根据 i 连的边转移即
可。
*/
