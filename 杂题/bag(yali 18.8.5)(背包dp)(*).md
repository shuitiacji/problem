

###Description

![](../pic/18.8.5-1.png)

### Solution

考虑到$>\sqrt{n}$的书是用不完的，可以直接$\mathcal{O}(n^2)$完全背包求。

而这个背包要考虑到顺序无关，为防止重复统计，要保证背包内物品有序

具体方法是每次只用两种决策，一是放一个体积为$\sqrt n + 1$的物品，二是将背包内所有物品的体积都加一

不难发现这样就能保证背包内的物品都有序，而且能到达所有可能的状态

这里设$dp[i][j]$表示选了$i$个物品，体积为$j$的方案，有
$$
dp[i + 1][j]+=dp[i][j-\sqrt n -1] \\
dp[i][j+i]+=dp[i][j]
$$
再考虑剩下的

如果直接处理剩下的物品，还要枚举数量，$\mathcal{O(n \times \sqrt n \times \sqrt n)}$也即$\mathcal{O(n^2)}$

设$dp[i][j]$表示前$i$种物品体积为$j$的方案数，你会发现其实在求这个东西
$$
dp[i][j]=\sum_{k<=i}dp[i-1][j-i*k]
$$
这个可以记个前缀和一样的东西转移，就不用枚举用了几个了

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10, mod = 998244353;
int n;
int g[2][maxn], block[maxn], f[2][maxn];
int add(int a, int b)
{
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int main()
{
	freopen("bag.in", "r", stdin);
	freopen("bag.out", "w", stdout);
	scanf("%d", &n);
	int s = sqrt(n) + 1;
	g[0][0] = 1; block[0] = 1;
	int now = 0, pre;
	for(int i = 1; i * s <= n; ++i)
	{
		pre = now; now ^= 1;
		fill(g[now], g[now] + i, 0);
		for(int j = i; j <= n; ++j)
		{
			g[now][j] = g[now][j - i];
			if(j >= s) g[now][j] = add(g[now][j], g[pre][j - s]); 
			block[j] = add(block[j], g[now][j]);
		}
	}
	now = 0;
	f[0][0] = 1;
	for(int i = 1; i < s; ++i)
	{
		pre = now; now ^= 1;
		int res = i * (i + 1);
		for(int j = 0; j < i; ++j)
		{
			int tmp = 0;
			for(int u = j; u <= n; u += i)
			{
				tmp = add(tmp, f[pre][u]);
				if(u - res >= 0) tmp = add(tmp, mod - f[pre][u - res]);
				f[now][u] = tmp;
			}
		}
	}
	int ans = 0;
	for(int i = 0; i <= n; ++i) (ans += 1LL * f[now][i] * block[n - i] % mod) %= mod;
	cout << ans << endl;
	return 0;
}

```

