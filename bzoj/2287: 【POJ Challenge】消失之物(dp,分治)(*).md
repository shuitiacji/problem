### Description

ftiasch 有 *N* 个物品, 体积分别是 *W1*, *W2*, ..., *WN*。 由于她的疏忽, 第 *i* 个物品丢失了。 “要使用剩下的 *N* - 1 物品装满容积为 *x* 的背包，有几种方法呢？” -- 这是经典的问题了。她把答案记为 *Count(i, x)* ，想要得到所有1 <= i <= N, 1 <= x <= M的 *Count(i, x)* 表格。

<!--more-->

### Solution

一种经典的套路，用分治减少重复计算，你会发现它与bzoj3237很像，都是去掉一些东西，然后再算答案，而且去掉的东西很少

考虑一种暴力，对每种物品，去掉它再跑背包

你会发现，由于物品的顺序对答案无影响，有大量的重复计算部分，比如说去掉i，你需要算(i+1,n)物品的贡献，去掉j，你需要算(j+1,n)物品的贡献，而(i+1,n)与(j+1,n)显然有重叠，考虑利用这部分

把所有的东西，一起跑一遍分治，当前分治区间(l,r)表示已算上了(1,l-1)与(r+1,n)物品的背包

将[l,r]分为两段,如果要处理[l,mid],就用(mid,r]的物品更新当前背包;处理(mid,r],就用[l,mid]的物品去更新当前
背包。
•l=r时,当前背包就是去掉物品l的答案了。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e3 + 10;
int dp[25][maxn], w[maxn], n, m;
void gao(int l, int r, int dep)
{
	if(l == r)
	{
		for(int i = 1; i <= m; ++i) printf("%d", dp[dep][i] % 10);
		printf("\n");
		return ;
	}
	int mid = (l + r) >> 1;
/**/for(int i = 0; i <= m; ++i) dp[dep + 1][i] = dp[dep][i];
	for(int i = mid + 1; i <= r; ++i)
		for(int j = m; j >= w[i]; --j)
			dp[dep + 1][j] = (dp[dep + 1][j] + dp[dep + 1][j - w[i]]) % 10;
	gao(l, mid, dep + 1);
/**/for(int i = 0; i <= m; ++i) dp[dep + 1][i] = dp[dep][i];
	for(int i = l; i <= mid; ++i)
		for(int j = m; j >= w[i]; --j)
			dp[dep + 1][j] = (dp[dep + 1][j] + dp[dep + 1][j - w[i]]) % 10;
	gao(mid + 1, r, dep + 1);
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &w[i]);
	dp[0][0] = 1;
	gao(1, n, 0);
	return 0;
}
```

### Debug

14行19行，要从零开始