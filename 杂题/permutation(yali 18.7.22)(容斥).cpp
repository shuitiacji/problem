#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace std;
__gnu_pbds:: gp_hash_table<int, int> hs;
typedef long long LL;
const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
LL inv[maxn], ifac[maxn], fac[maxn], bit[maxn];
int cnt, n;
void init()
{
	inv[0] = inv[1] = ifac[0] = ifac[1] = fac[0] = fac[1] = 1;
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
	return fac[N] * ifac[M] % mod * ifac[N - M] % mod;
}
LL Pow(LL x, int p)
{
	LL r = 1;
	while(p)
	{
		if(p & 1) r = r * x % mod;
		x = x * x % mod; p >>= 1;
	}
	return r;
}
int main()
{
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		int x;
		scanf("%d", &x);
		if(hs.find(x) != hs.end()) cnt++;
		else hs[x] = 1;
	}
	init();
	bit[0] = 1;
	for(int i = 1; i <= cnt; ++i) bit[i] = bit[i - 1] * 2 % mod;
	for(int i = 1; i <= cnt; ++i) bit[i] = Pow(bit[i], mod - 2);//, bit[i] = Pow(bit[i], mod - 2);
	LL ans = fac[n] * bit[cnt] % mod;
	for(int i = 1, j = -1; i <= cnt; ++i, j = -j)
		ans = (ans + 1LL * j * C(cnt, i) * fac[n - i] % mod * bit[cnt - i] % mod) % mod;
	cout << (ans % mod + mod) % mod << endl;
	return 0;
}
/*
题意:
HYJ 觉得他的键盘有点脏了,于是决定将键帽拆下来洗一洗。
他将键帽排成了一列,他认为一个键帽排列是好的当且仅当没有两个相同的键帽相邻。他
想知道有多少种排列是好的。由于 HYJ 还在忙着洗键盘,你能帮他解决这个问题吗?
数据保证每种键帽最多出现两次。

思路:
考虑强行枚举至少有1对的,发现这样会算重(你在保证1号成对时,有可能使2号成对,在保证二号成对时,有可能使1号成对,算重),为了去重,容斥一下
注意是可重元素的排列,还要除掉重的东西的排列.
ans = n!/2^(cnt) - sigma((-1) ^ (i - 1) * C(cnt, i) * (n - i)! / 2 ^ (cnt - i)) (1 <= i <= cnt)
*/
