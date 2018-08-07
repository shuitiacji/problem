### Description

Fkb不喜欢运动,所以这天体育课他和博弈 doe 在操场上博弈。操场上有 个点, Fkb 和博弈 doe 轮流选择一个
点, Fkb先选,最后每个人的得分是他所选取的两两点之间的欧几里德距离之和。令 V=Fkb 得分 - 博弈 doe 得分, Fkb要最大化 V ,而博弈 doe 要最小化 V ,他们都采取最优策略,那么最终 V 会是多少?

### Solution

这个题有个很显然的套路，把边权化成点权。即把一条边的权值除以2，分别给到它连的两个点上。

把V计算成Fkb选的点权减去doe选的点权，这个显然是对的，因为一条边的值计算进去只有可能两边的两个点都被一个人选了，如果两个人分别选了这两个点，就会把这条边的权值给减完了

把点按点权排序，两个人贪心选一下就行了

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2510 << 1;
/**/
#define squ(x) ((x) * (x))
double v[maxn], x[maxn], y[maxn];
double dis(int a, int b) { return sqrt(squ(x[a] - x[b]) + squ(y[a] - y[b])); }
int cmp(double a, double b) { return a > b; }
int main()
{
	freopen("by.in", "r", stdin);
	freopen("by.out", "w", stdout);
	int n;
	scanf("%d", &n);
	n *= 2;
	for(int i = 1; i <= n; ++i) scanf("%lf%lf", &x[i], &y[i]);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			v[i] += dis(i, j);
	sort(v + 1, v + n + 1, cmp);
	double ans = 0;
	for(int i = 1; i <= n; ++i)
	{
		if(i & 1) ans += v[i];
		else ans -= v[i];
	}
	printf("%.3lf\n", ans / 2.);
	return 0;
}
```

### Debug

第5行，一定要写成$((x) \times (x))$不能写成$(x \times x)$

