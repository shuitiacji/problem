#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;
const int mod = 998244353;
LL fac[maxn], ifac[maxn], inv[maxn], s[maxn], f[maxn];
int n;
void mathinit()
{
	fac[0] = fac[1] = ifac[0] = ifac[1] = inv[0] = inv[1] = 1;
	for(int i = 2; i <= n; ++i)
	{
		fac[i] = fac[i - 1] * i % mod;
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		ifac[i] = inv[i] * ifac[i - 1] % mod;
	}
}
LL Pow(LL x, int p)
{
	LL r = 1;
	while(p)
	{
		if(p & 1) r = x * r % mod;
		x = x * x % mod; p >>= 1;
	}
	return r;
}
LL C(int N, int M)
{
	if(N < M) return 0;
	return fac[N] * ifac[M] % mod * ifac[N - M] % mod;
}
int main()
{
	freopen("rockginger.in", "r", stdin);
	freopen("rockginger.out", "w", stdout);
	scanf("%d", &n);
	mathinit();
	for(int i = 1; i <= n; ++i)
		s[i] = Pow(2, C(i - 1, 2));
	f[1] = 1;
	for(int i = 2; i <= n; ++i)
	{
		f[i] = s[i];
		for(int j = 1; j < i; ++j) f[i] = (f[i] - C(i - 1, j - 1) * f[j] % mod * s[i - j] % mod) % mod;
	}
	f[n] = (f[n] + mod) % mod;
	LL tmp = Pow(2, C(n, 2));
	tmp = Pow(tmp, mod - 2);
	f[n] = f[n] * tmp % mod;
	cout << f[n] << endl;
	return 0;
}
/*
题意：
求一个n点任意图（可以不联通）为欧拉图的概率

思路：
先研究一些性质
考虑欧拉图的充分必要条件是连通与所有点度数为偶数,那么先考虑设 s(n) 表示 n 个点的所有点度数为偶数的图的个数
考虑一个有偶数个奇度数点的图,新加入的点只要和所有奇点连边就可以使得这个图满足条件,那么 n 个点的偶度数图和 n − 1 个点的所有图
都是一一对应的,那么 s(n) = 2 ^ (C(n - 1, 2)) (因为一条边会对总度数+2,如果有奇数个奇数度点，总度数就不会是2的倍数，所以是一一对应的，而n-1点的图的总数是先找到所有的边C(n, 2), 再2的幂次判这边存不存在。)

满足了度数，同时还要判联通性。
考虑容斥解决这个问题
考虑设 f (n) 表示 n 个点的欧拉图个数,那么考虑一个枚举一号点所在连通块点数的简单容斥:
f(n) = s(n) - sigma(C(n - 1, i - 1) * f(i) * s(n - i)) (i < n)

最后除个总个数，即为概率
*/
