#### Description

给定n * m 的零一矩阵， 求包含$[l, r]$个1的矩阵的方案数。

n <= 20  && m <= 5e4

<!--more-->

#### Solution

这一题其实是套路题目， 因为是在二维平面上操作， 如果是一维直线上就好做了。先计算前缀和。 然后维护two pointers, 先钦定左指针，找到从1开始的可行解。

然后使用two pointers， 左指针代表维护当前可行解到左指针之间的线段都是符合$[0, r]$条件的。 右指针则代表$[0, l]$,然后计算左指针与右指针的距离即可。

考虑放到二维怎么做， 我们已经解决了一维问题。考虑从二维转换到一维， 因为第二维度非常小。 我们可以枚举上下的点， 这样就转化为一维问题。



在做二维问题时， 我们可以考虑先确定一维， 然后想办法在可行范围内维护第二维。

在这题中， 因为n维度太小， 可以考虑暴力确定n的维度， 然后用two pointers维护m的维度。 综合复杂度$O(n^2m)$

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
typedef long long LL;
const int maxn = 32, maxm = 5e4 + 10;
int a[maxn][maxm], Sum[maxm], sum[maxn][maxm];
char s[maxm];
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	int n = read(), m = read();
	for(int i = 1; i <= n; ++i)
	{
		scanf("%s", s);
		for(int j = 1; j <= m; ++j)
			a[i][j] = s[j - 1] - '0', sum[i][j] = sum[i - 1][j] + a[i][j];
	}
	int L = read(), R = read();
	LL ans = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = i; j <= n; ++j)
		{
			int r = 1, l = 1;
			Sum[1] = sum[j][1] - sum[i - 1][1];
/**/		if(L == 0) ans = ans + m;
			for(int k = 2; k <= m; ++k)
			{
				Sum[k] = Sum[k - 1] + sum[j][k] - sum[i - 1][k];
				while(Sum[k] - Sum[l - 1] >= L && l <= k) ++l;
				while(Sum[k] - Sum[r - 1] > R && r < k) ++r;
				if(Sum[k] - Sum[r - 1] >= L) ans = ans + max(0, (l - 2) - r) + ((l - 1) != k) + (r != k) - ((l - 1) == r && (l - 1) != k);
			}
		}
	cout << ans << endl;
	return 0;
}
```

### Debug

特判L == 0