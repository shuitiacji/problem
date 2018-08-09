### Description

小 Z 的家很大, 构成一个 N 个点 M 条边的无向联通图.但是小 Z 有很严重的选择恐惧症, 他希望删掉家中的一些边, 使得从 1号点到 N 号点的路径是唯一的, 同时他希望删去的边权值和尽可能小.

<!--more-->

### Solution

1 号点到 N 的路径唯一相当于存在一条 1 到 N 的链, 并且不在链上的每个联通块最多只和链上的一个点有连边，因为如果有两个，就存在一条通过这两个点经过联通块的新的路径

考虑n很小，状压dp。$dp[i][j]$表示当前考虑的点集是i，当前链尾是j

可能的转移方式有两种，一种是让链的长度增加一，第二种是添加一个新的与j相连的点集，因为这个点集与i没有重复元素，它连到这个链的点最多只有这个链尾j，保证不存在新的路径

具体方法是预处理出来$s[i]$表示联通点集i的边的和，枚举子集来处理出与j相连的联通块

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 17;
int n, m;
int e[maxn][maxn];
LL dp[1 << maxn][maxn], s[1 << maxn], sum;
int main()
{
	freopen("connect.in", "r", stdin);
	freopen("connect.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		e[x][y] = z; e[y][x] = z;
		sum += z;
	}
	for(int i = 1; i < (1 << (n)); ++i)
	{
		int tmp = __builtin_ctz(i);
		int j = i ^ (1 << (tmp));
		s[i] = s[j];
		for(int w = 1; w <= n; ++w)
			if((i & (1 << (w - 1))) && (e[w][tmp + 1])) s[i] += e[w][tmp + 1];
	}
	memset(dp, ~0x3f3f3f3f, sizeof(dp));
/**/for(int i = 1; i < (1 << (n)); i += 2)
	{
		dp[i][1] = s[i];
		for(int j = 1; j <= n; ++j) if(dp[i][j] >= 0)
		{
			int tmp = ((1 << (n)) - 1) ^ i;
			for(int w = tmp; w; w = (w - 1) & tmp)
				dp[i ^ w][j] = max(dp[i ^ w][j], dp[i][j] + s[(1<< (j - 1)) ^ w]);
		}
		for(int k = 1; k <= n; ++k) if(dp[i][k] >= 0)
		{
			for(int j = 1; j <= n; ++j)
				if(!(i & (1 << (j - 1))))
					dp[i ^ (1 << (j - 1))][j] = max(dp[i ^ (1 << (j - 1))][j], dp[i][k] + e[k][j]);
		}
	}	
	cout << sum - dp[(1 << (n)) - 1][n] << endl;
	return 0;
}
```

### Debug

29行，+=2来保证1一定在i中

注意(1<<n)-1不要写成(1<<(n-1))-1