#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int n, m, mod;
int dp[5020][5020], p[5020], pm[5020], sum[1000100], Dp[2][5010];
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &mod);	
	dp[0][0] = 1;
	for(int i = 1; i <= 5010; ++i)
		for(int j = 1; j <= i; ++j)
			dp[i][j] = (dp[i - 1][j - 1] + 1LL * dp[i - 1][j] * (j - 1)) % mod;
	p[0] = 1;
	for(int i = 1; i <= 5010; ++i) p[i] = 1LL * p[i - 1] * i % mod;
	pm[0] = 1;
	for(int i = 1; i <= min(m, 5010); ++i) pm[i] = 1LL * pm[i - 1] * (m - i + 1) % mod;
	sum[0] = 1;
	int pos = 0, lst = 0;
	for(int i = 1; i <= n; ++i)
	{
		memset(Dp[pos], 0, sizeof(Dp[pos]));
		int l;
		scanf("%d", &l);
		for(int j = 1; j <= l; ++j)
		{
			Dp[pos][j] = 1LL * sum[i - 1] * dp[l][j] % mod * pm[j] % mod;
			if(i > 1 && j <= lst)
				Dp[pos][j] = (Dp[pos][j] - 1LL * Dp[pos ^ 1][j] * dp[l][j] % mod * p[j] % mod) % mod;
			sum[i] = (sum[i] + Dp[pos][j]) % mod;
		}
		lst = l; pos ^= 1;
	}
	cout << (sum[n] + mod) % mod << endl;
	return 0;
}
/*
题意:
有n段绳子，m种颜色，每一米染一个色，要求同一段绳子内，相邻两米的颜色不同，且相邻两端绳子的包含的颜色种类不完全相同

思路：
考虑只有一段绳子的情况
设dp[i][j]为在长度为i的绳子上染j种颜色的方案
dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] * (j - 1)
考虑到这个东西并没考虑选了哪些颜色，以及这些颜色的排列，所以最后要用的时候还要乘以一个A(j, m)

设Dp[i][j]表示第1到第i - 1条绳子都已合法染色完毕，第i根绳子染了j种颜色的方案
Dp[i][j] = (sigma(Dp[i - 1][k])(k <= j)) * (A(j, m) * dp[l][j]) - (i与i-1颜色相同的方案)
考虑这个颜色相同的怎么搞
因为此时第 i - 1 根绳子的颜色种类及顺序已经确定了,这个在求Dp数组的过程中可以看出,所以对于第 i 根颜色不需要再去枚举是由哪 j 种颜色组成了,但是任要枚举顺序, i - 1染 j 种颜色且前面全部合法的方案为Dp[i - 1][j], 染 j 种颜色的合法方案为dp[l][j],再乘上一个 j!。
*/
