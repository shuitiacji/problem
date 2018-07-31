#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
typedef long long LL;
LL f[maxn], sum[maxn];
int n, m, k;
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);
	f[0] = 1;
	for(int i = 1; i < k; ++i)
	{
		f[i] = f[i - 1] * m % mod;
		sum[i] = (sum[i - 1] + f[i]) % mod;
	}
	for(int i = k; i <= n; ++i)
	{
		f[i] = (sum[i - 1] - sum[i - k]) * (m - 1) % mod;
		sum[i] = (sum[i - 1] + f[i]) % mod;
	}
	LL ALL = 1;
	for(int i = 1; i <= n; ++i)
		ALL = ALL * m % mod;
	cout << ((ALL - f[n]) + mod) %mod << endl;
	return 0;
}
/*
题意:有n个格子，用m种颜色覆盖，每次只能覆盖k个格子，原来有颜色也可以覆盖，每个格子都要有颜色，问一共有多少种最终状态？

思路：
首先发现性质，最终状态要求至少有一个长度为k的相同颜色的块
逆向思维，dp处理没有这样的块的方案。
dpi为在i时没有这样的块的方案，枚举最后一段相同颜色的长度转移，前缀和优化。
*/
