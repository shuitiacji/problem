#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 998244353;
const int maxn = 1010;
LL fac[maxn], inv[maxn], ifac[maxn], dp[maxn];
int a[maxn], n;
void mathint()
{
	fac[0] = fac[1] = ifac[0] = ifac[1] = inv[0] = inv[1] = 1;
	for(int i = 2; i <= n; ++i)
	{
		fac[i] = fac[i-1] * i %mod;
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		ifac[i] = ifac[i-1] * inv[i] % mod;
	}
}
LL C(LL N, LL M)
{
	if(N < M) return 0;
	if(N == M) return 1;
	return fac[N] * ifac[M] % mod * ifac[N - M] % mod;
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d", &n);
	mathint();
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for(int i = n; i >= 1; --i)
	{
		if(a[i] <= 0) continue;
		dp[i] = C(n - i, a[i]);
		for(int j = i + a[i]; j <= n; ++j)
		{
			dp[i] += (dp[j + 1] * C(j - i, a[i]) % mod);
			dp[i] %= mod;
		}
	}
	LL sum = 0;
	for(int i = 1; i <= n; ++i) sum = (sum + dp[i]) % mod;// cout << dp[i] << endl;
	cout << sum << endl;
	return 0;
}
/*
题意：
如果一个数组 [a1,a2,a3,...,an]a1=n-1 并且 a1>0 ，这个数组就被叫为好数组，如果一个序列能正好分为多个好数组，ta就被叫为好序列，现在给定一个序列，求这个序列有多少好子序列，答案对 998244353 取模

思路：
因为关键在于区间的第一个，我们从后向前考虑，dp[i]表示以i为开头，满足题意的数量
*/
