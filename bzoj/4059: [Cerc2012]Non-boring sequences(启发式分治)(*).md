### Desciption

我们害怕把这道题题面搞得太无聊了，所以我们决定让这题超短。一个序列被称为是不无聊的，仅当它的每个连续子序列存在一个独一无二的数字，即每个子序列里至少存在一个数字只出现一次。给定一个整数序列，请你判断它是不是不无聊的。

<!--more-->

### Solution

考虑这种判重复元素的题，把las与nxt数组设出来

那么这个元素能成为某个区间仅出现一次的数，当且仅当这个区间的左端点在$[last[i]+1,i]$之间，右端点在$[i,next[i]−1]$之间 

~~我们可以将区间的左右端点放在二维平面上，那么一个元素产生的贡献是一个矩形，我们要确定的是所有元素对应的矩形的并集是否是覆盖所有合法区间对应的点，显然线段树+扫描线就行了~~

对于区间[l,r],我们寻找一个i使所有包含i的区间满足条件，然后递归[l,i)和(i,r],如果不存在即可退出。

因为这个划分不均匀，要用启发式分治来保证复杂度，按照l,r,l+1,r-1,l+2,r-2,...的顺序去检验，不难发现这个复杂度只与分治的小一半有关，常数是2，$\mathcal O(nlogn)$

### Code

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
__gnu_pbds::gp_hash_table<int, int> xz;
using namespace std;
const int maxn = 2e5 + 10;
int nxt[maxn], las[maxn], a[maxn], n;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
int gao(int l, int r)
{
	if(l > r) return 0;
	if(l == r) return 0;
	int i = l, j = r;
	while(1)
	{
		if(nxt[i] > r && las[i] < l) return gao(l, i - 1) | gao(i + 1, r); 
		++i;
		if(nxt[j] > r && las[j] < l) return gao(l, j - 1) | gao(j + 1, r);
		--j;
		if(i > j) return 1;
	}
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	int T = read();
	while(T--)
	{
		n = read();
		xz.clear();
		for(int i = 1; i <= n; ++i) nxt[i] = n + 1, las[i] = 0;
		for(int i = 1; i <= n; ++i)
			a[i] = read(), las[i] = xz[a[i]], nxt[xz[a[i]]] = i, xz[a[i]] = i;
		if(gao(1, n)) puts("boring");
		else puts("non-boring");
	}
	return 0;
}
```

