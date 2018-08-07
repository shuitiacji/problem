#### Description

一个长为$n$的序列,每个元素都在$[1, k]$之间。

现在小C想在序列后面再加上$m$个$[1, k]$之内的元素,使得本质不同的子序列个数尽量多。

两个子序列被认为是不同的,当且仅当它们长度不同,或者至少一个对应位置的值不同。

输出最大的不同子序列个数,对$10^9 + 7$取模。注意空序列不被看作一个子序列。



#### Constraints

$n \le 10^6, m\le 10^{18}, k\le 100$



#### Solution

先考虑怎么算不同子序列个数

设$dp[i]$表示**以$i$这个数字结尾**的子序列个数，那么显然$dp[i] = \sum_{j=1}^{k}dp[j] + 1$

容易发现，无论接下来的元素是什么，其他的$dp[x]$都是没有变化的

所以我们贪心地填当前的$dp$值最小的那个元素，也就是最后出现位置最靠前的那个元素

直接填是$O(m)$的，不难发现我们填的一定是一个$k$的排列重复若干次，所以每$k$个元素的转移都是相同的

因此我们可以矩阵快速幂优化

设$a_i$为**以第$i$个位置结尾**的答案，显然$a_i=\sum_{j=i-k}^{i-1}a_j + 1$那么我们就是要构造一个矩阵$B$，使得

$$B \times \begin{bmatrix} 1 \\ a_{1} \\ a_{2} \\ a^{\vdots }_{k} \end{bmatrix} = \begin{bmatrix} 1\\a_{2} \\ a_{1} \\ a^{\vdots }_{k+1} \end{bmatrix}$$



那么显然

$$B=\begin{bmatrix} 1 & 0 & 0 & 0 & \ldots & 0 \\ 0 & 0 & 1 & 0 & \ldots & 0 \\ 0 & 0 & 0 & 1 & \ldots & 0 \\ & & \ldots & & \\ 1 & 1 & 1 & 1 & ... & 1 \end{bmatrix}$$

然后就可以直接矩阵快速幂了

###Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int maxn = 5e5 + 10;
typedef long long LL;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
struct tree
{
	int x1, x2, y1, y2;
}t[maxn << 2], ans;
int fg;
int n, ta, tb, T, q, A, B;
int p[maxn];
int Pow(int x, int P)
{
	int r = 1;
	while(P)
	{
		if(P & 1) r = 1LL * x * r % mod;
		x = 1LL * x * x % mod; P >>= 1;
	}
	return r;
}
tree merge(const tree &a, const tree &b)
{
	int x1, x2, y1, y2;
	x2 = 1LL * b.x2 * a.x2 % mod;
	y2 = (1LL * b.x2 * a.y2 % mod + b.y2) % mod;
	x1 = 1LL * b.x1 * a.x2 % mod;
	y1 = (b.y1 + 1LL * a.y2 * b.x1 % mod) % mod;
	x1 += a.x1; y1 += a.y1;
	x1 %= mod; y1 %= mod;
	return (tree){x1, x2, y1, y2};
}
void build(int o, int l, int r)
{
	if(l == r)
	{
		t[o].x2 = ((p[l] - 1LL * p[l] * T % mod + T) % mod + mod) % mod; t[o].y2 = p[l];
		t[o].x1 = p[l]; t[o].y1 = p[l];
		return ;
	}
	int mid = (l + r) >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
	t[o] = merge(t[o << 1], t[o << 1 | 1]);
}	
void upt(int o, int l, int r, int pos)
{
	if(l == r)
	{
		t[o].x2 = ((p[l] - 1LL * p[l] * T % mod + T) % mod + mod) % mod; t[o].y2 = p[l];
		t[o].x1 = p[l]; t[o].y1 = p[l];
		return ;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) upt(o << 1, l, mid, pos);
	else upt(o << 1 | 1, mid + 1, r, pos);
	t[o] = merge(t[o << 1], t[o << 1 | 1]);
}
void que(int o, int l, int r, int x, int y)
{
	if(x <= l && r <= y)
	{
		if(fg) ans = t[o], fg = 0;
		else ans = merge(ans, t[o]);
		return ;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) que(o << 1, l, mid, x, y);
	if(y > mid) que(o << 1 | 1, mid + 1, r, x, y);
}
namespace BIT
{
	int c[maxn];
	int lowbit(int x) { return x & (-x); }
	void upt(int x, int v)
	{
		while(x <= n)
		{
			c[x] = (c[x] + v) % mod; x += lowbit(x);
		}
	}
	int que(int x)
	{
		int ret = 0;
		while(x)
		{
			ret = (ret + c[x]) % mod; x -= lowbit(x);
		}
		return ret;
	}
}
int main()
{
	freopen("omeed.in", "r", stdin);
	freopen("omeed.out", "w", stdout);
	int xz_ak_IOI = read();
	n = read(); q = read(); ta = read(); tb = read(); A = read(); B = read();
	T = 1LL * ta * Pow(tb, mod - 2) % mod;
	for(int i = 1; i <= n; ++i)
	{
		int x = read(), y = read();
		p[i] = 1LL * x * Pow(y, mod - 2) % mod;
		BIT::upt(i, p[i]);
	}
	build(1, 1, n);
	for(int i = 1; i <= q; ++i)
	{
		int opt = read();
		if(opt == 0)
		{
			int x = read(), y = read(), z = read();
/**/		BIT::upt(x, (-p[x] + mod) % mod);
			p[x] = 1LL * y * Pow(z, mod - 2) % mod;
			upt(1, 1, n, x); BIT::upt(x, p[x]);
		}
		else 
		{
			int x = read(), y = read();
			fg = 1;
			que(1, 1, n, x, y);
			printf("%lld\n", (1LL * A * ((BIT::que(y) - BIT::que(x - 1) + mod) % mod) % mod + 1LL * B * ans.y1 % mod) % mod);
		}
	}
	return 0;
}
```
###Debug
165行，加mod模mod

