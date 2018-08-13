#### Description

给定n个序列，每个长m， 要求选数， 每次至少选择一个序列， 每个被选序列中选一个数。 求所有方案中gcd的总和， 一个方案不同当且仅当一个序列中的一个数被选， 而另一个序列中没选。

$$ Max\{a_i\} <= 1e5, n <= 20, m <= 1e5 $$

<!--more-->

#### Solution

这题直接做不好做。 我们考虑枚举答案， 并计算答案的方案数（类似贡献）。

设定$f[i]$ 表示当选定数的`gcd` == i时的方案数.

考虑莫比乌斯反演时的经典的转换, 枚举当前i的倍数作为gcd的情况.

考虑如下式子:
$$
F(n) = \sum_{n\mid d}f(d)\\
f(n) = \sum_{n \mid d} \mu(\frac{d}{n}) * F(d)
$$
那么`gcd==i`的情况就可以视为$f(n)$, i | gcd 的情况就可以视为$F(n)$

我们只要能求快速求`F(n)`, 就可以反演出`f(n)`.

考虑F(n)怎么求: 定义$cnt_{ij}$为i行内数字为j的倍数的个数.

那么显然: 
$$
F(x) = \prod_{i = 1}^{n} (cnt_{ix} + 1)  - 1
$$
因为每行可以选或不选, 所以要加1, 再要排除所有行不选的情况.

对于`cnt`, 我们暴力处理, 然后直接反演即可.

### Code

```cpp
#include<bits/stdc++.h>
const int maxn = 22;
const int mod = 1e9 + 7;
int cnt[maxn][(int)(1e5 + 10)];
using namespace std;
int mu[100100], vis[100100], prime[100100];
int ret[maxn], F[100100];
int tot;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
void init()
{
	mu[1] = 1;
	for(int i = 2; i <= (int) (1e5) + 10; ++i)
	{
		if(!vis[i]) mu[i] = -1, prime[++tot] = i;
		for(int j = 1; j <= tot && 1LL * i * prime[j] <= (int)(1e5 + 10); ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j]) mu[i * prime[j]] = -mu[i];
			else { mu[i * prime[j]] = 0; break; }
		}
	}
}
int ans;
int add(int x, int y)
{
	x += y;
	if(x >= mod) x -= mod;
	return x;
}
main()
{
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	int n = read(), m = read();
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
		{
			int x = read();
			cnt[i][x]++;
		}
	init();
	for(int i = 1; i <= (int) 1e5; ++i)
	{
		memset(ret, 0, sizeof(ret));
		for(int j = 1; i * j <= (int) 1e5; ++j)
			for(int i1 = 1; i1 <= n; ++i1)
				ret[i1] = add(ret[i1], cnt[i1][i * j]);
		F[i] = 1;
		for(int j = 1; j <= n; ++j)
			F[i] = 1LL * F[i] *	(ret[j] + 1) % mod;
		F[i]--;
	}
	for(int i = 1; i <= (int) 1e5; ++i)
		for(int j = 1; i * j <= (int) 1e5; ++j)
/**/		ans = add(ans, ((1LL * i * F[i * j] % mod * mu[j] % mod) + mod) % mod);
	cout << ans << endl;
	return 0;
}
```

### Debug

62，一定要加mod模mod