#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 998244353;
const int maxn = 1e6 + 10;
LL ksm(LL x, LL p)
{
	LL r = 1;
	while(p)
	{
		if(p & 1) r = x * r % mod;
		x = x * x % mod; p >>= 1;
	}
	return r;
}
LL inv[maxn], fac[maxn], ifac[maxn]; 
int n;
void mathint()
{
	inv[0] = inv[1] = ifac[0] = ifac[1] = fac[0] = fac[1] = 1;
	for(int i = 2; i <= n; ++i)
	{
		fac[i] = fac[i - 1] * i % mod;
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		ifac[i] = ifac[i - 1] * inv[i] % mod;
	}
}
LL C(int N, int M)
{
	if(M > N) return 0;
	return fac[N] * ifac[M] % mod * ifac[N - M] % mod;
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d", &n);
	mathint();
	LL ans = 0;
	for(int i = 1; i <= n; ++i)
		(ans += (i & 1 ? 1 : -1) * C(n, i) * ksm(3, 1LL * n * (n - i) + (LL)i) % mod) %= mod;
	ans = ans * 2 % mod;
	LL tmp = 0;
	for(int i = 0; i < n; ++i)
	{
		int t = mod - ksm(3, i);
		tmp += C(n, i) * (ksm(1 + t, n) - ksm(t, n ) + mod) % mod * (i & 1 ? 1 : -1);	
		tmp %= mod;
	}
	tmp = tmp * 3LL % mod;
	ans = (ans + tmp) % mod;
	ans = (ans + mod) % mod;
	cout << ans << endl;
	return 0;
}
/*
http://www.perfectpan.org/archives/2062
*/
