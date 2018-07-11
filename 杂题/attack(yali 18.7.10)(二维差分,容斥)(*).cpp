#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
typedef long long LL;
const int maxn = 2010;
int n, m, k;
LL a[maxn][maxn], b[maxn][maxn], c[maxn][maxn], d[maxn][maxn], dp[maxn][maxn];
int s[maxn][maxn], g[maxn][maxn], f[maxn][maxn], tp, q[maxn];
char S[maxn];
int ksm(int x, int y)
{
	int r = 1;
	while(y)
	{
		if(y & 1) r = (LL)r * x % mod;
		x = (LL) x * x % mod; y >>= 1;
	}
	return r;
}
int solve(int x, int y)
{
	int ans = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
		{
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + a[i][j] + b[i + x][j] + c[i][j + y] + d[i + x][j + y];
			ans = (ans + ksm(dp[i][j] % mod, k)) % mod;
		}
	return ans;
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%s", S);
		for(int j = 0; j < m; ++j)
			s[i][j + 1] = S[j] - '0';
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			f[i][j] = s[i][j] == 1 ? f[i - 1][j] + 1 : 0;
	for(int i = n; i >= 1; --i)
		for(int j = 1; j <= m; ++j)
			g[i][j] = s[i][j] == 1 ? g[i + 1][j] + 1 : 0;
	LL now = 0;
	for(int i = 1; i <= n; ++i)
	{
		q[tp = 1] = m + 1; now = 0;
		for(int j = m; j >= 1; --j)
		{
			while(tp > 1 && g[i][j] <= g[i][q[tp]])
				now -= (q[tp - 1] - q[tp]) * g[i][q[tp]], --tp;
			now += (q[tp] - j) * g[i][j];
			a[i][j] += now; q[++tp] = j;
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		q[tp = 1] = m + 1; now = 0;
		for(int j = m; j >= 1; --j)
		{
			while(tp > 1 && f[i][j] <= f[i][q[tp]])
				now -= (q[tp - 1] - q[tp]) * f[i][q[tp]], --tp;
			now += (q[tp] - j) * f[i][j];
			b[i + 1][j] -= now; q[++tp] = j;
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		q[tp = 1] = 0; now = 0;
		for(int j = 1; j <= m; ++j)
		{
			while(tp > 1 && g[i][j] <= g[i][q[tp]])
				now -= (q[tp] - q[tp - 1]) * g[i][q[tp]], --tp; 
			now += (j - q[tp]) * g[i][j];
			c[i][j + 1] -= now; q[++tp] = j;
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		q[tp = 1] = 0; now = 0;
		for(int j = 1; j <= m; ++j)
		{
			while(tp > 1 && f[i][j] <= f[i][q[tp]])
				now -= (q[tp] - q[tp - 1]) * f[i][q[tp]], --tp;
			now += (j - q[tp]) * f[i][j];
			d[i + 1][j + 1] += now; q[++tp] = j;
		}
	}
	int ans = solve(0, 0) - solve(0, 1) - solve(1, 0) + solve(1, 1);
	cout << (ans % mod + mod) % mod << endl;
	return 0;
}
/*
题意：
你将向敌方发起进攻!敌方的防御阵地可以用一个N × M的 01 矩阵表示,标为 1的表示有效区域,标为 0 的是敌人的预警装置。
你将发起K轮进攻,每一轮选定一个矩形区域对其进行轰炸。如果K轮后存在一个有效区域每次都被轰炸到,并且没有一次触发敌人的预警装置,那么将对敌人造成致命打击。现在你想知道一共有多少种不同的轰炸方案能对敌人造成致命打击,输出对 998244353 取模的结果。

题意：
因为矩形个数过多，显然要从点考虑。
有一个想法是看1×1的有效区域被多少个有效的矩形覆盖，答案为cnt^k。这样的方案记为1*1
显然会算重，可以考虑容斥，因为被多个矩形同时覆盖的始终是矩形，这个区域长度+1宽度+1都会算重更多，要减去1*2,2*1,同时加上2*2

考虑一个矩形，对它区间内的点的贡献可以差分搞，对它的(x1，y1) + 1,(x2,y2 + 1) - 1,(x3 + 1,y3) - 1,(x4 + 1, y4 + 1) + 1。（分别为左上端点，左下端点，右上端点，右下端点
考虑枚举有效矩形，可以分别对以(x,y)为左上坐下右上右下端点的矩形枚举个数，搞个单调栈枚举行扫一遍列即可。

*/
