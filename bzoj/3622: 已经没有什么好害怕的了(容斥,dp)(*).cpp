#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 2100;
const int mod = 1e9 + 9;
LL inv[maxn], fac[maxn], ifac[maxn], dp[maxn][maxn];int t[maxn], n, k;
int a[maxn], b[maxn];
void init()
{
	inv[0] = inv[1] = fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	for(int i = 2; i <= maxn - 10; ++i)
	{
		fac[i] = fac[i - 1] * i % mod;
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		ifac[i] = ifac[i - 1] * inv[i] % mod;
	}
}
LL C(int N, int M)
{
	if(N < M) return 0;
/**/return fac[N] * ifac[M] % mod * ifac[N - M] % mod;
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	init();
	scanf("%d%d", &n, &k);
	k = (n + k) >> 1;
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for(int i = 1; i <= n; ++i) scanf("%d", &b[i]);
	sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
	int J = 1;
	for(int i = 1; i <= n; ++i)
	{
		while(a[i] > b[J] && J <= n) ++J;
		t[i] = J - 1;
	}
	dp[0][0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		dp[i][0] = 1;
		for(int j = 1; j <= i; ++j)
			dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1] * max(t[i] - j + 1, 0) % mod) % mod;
	}
	LL ans = 0;
	for(int i = k, j = 1; i <= n; ++i, j = -j)
	{
		ans += 1LL * j * C(i, k) * dp[n][i] % mod * fac[n - i] % mod;
/**/	ans %= mod;
	}
	cout << (ans + mod) % mod << endl;
	return 0;
}
/*
题意：零食魔女夏洛特的结界里有糖果a和药片b各n个，两两配对，a>b的配对比b>a的配对多k个学姐就可能获胜，求方案数

思路：
多k个不好处理，考虑到a!=b，所以不是a>b就是b>a，问题转化成求恰好(n + k) / 2个的方案。
考虑容斥
设dp[i][j]表示为 a 中前 i 个数能选出比 b 大共有 j 对的方案数.
直接dp不好高搞，更改dp顺序，显然要对a与b先排个序
设t[i]表示ai比多少个bj要大
dp[i][j] = dp[i - 1][j] + max(0, t[i] - j + 1) * dp[i - 1][j - 1];

ans = sigma( (-1) ^ (i - k) * C(i, k) * fac[n - i] * dp[n][i] ) ( i >= k)
 
debug：
一定要记得mod，50,21
*/
