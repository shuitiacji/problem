
### Description

### Solution
基础分很好搞，关键是连击分
设$f_i$表示$combo(i)$的期望值
显然有$Ans(combo) = B \times \sum_{i = l}^{r} p_i \times (f_{i-1} + 1)$
而$f_i$也很好求
$f_i = p \times (f_{i-1} + 1) + (1-p_i)\times f_{i-1} \times t$
于是$f_i$能够写成$x\times f_i + y$的形式，同理一直搞下去就能把$[l,r]$这段区间所有的$f_i$都写成$x\times f_{l-1} + y$的形式
显然直接只用维护系数就行了
那么用线段树来维护一段区间的和(在这里就是和的$f_{l-1}$的系数,与$y$)，以及$f_r$中的系数(用来合并)。合并时$[l_1,r_1]$与$[l_2,r_2]$时($l_2 = r_1 + 1$)，只要把$f_{l_2 - 1}$ 往回带就可以了

### Code
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
### debug
119行，忘记加$mod$模$mod$
