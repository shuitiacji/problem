### Description

年级第一的小学生 Fkb 因为上数学课睡觉被老师点名,老师在黑板上写下了一个序列$a_1,a_2,...,a_n$, 让 Fkb 在相邻两个数之间填上$+, -, \times$中的某一个,并让 Fkb 计算所有可能的序列的答案之和, Fkb 很轻松就答出来的。老师又每次修改某个$a_i$ ,并让 Fkb 快速求出每次修改之后的答案,由于修改实在是太多了, Fkb 只好求助于你。结果对于1e9 + 7取模。

### Solution

考虑算这个东西，你会发现所有形如这样的式子都是没有贡献的：$a_i \times a_{i+1} \times a_{i+2} \times ... \times a_{j}$，因为$a_i$可以填$+,-$，在总答案中就没有贡献

只有从$a_1$开始的式子是有贡献的，因为$a_1$前填不了符号

对于$a_1 \times a_2 \times a_3 \times ... a_j$它出现的次数是$3^{n - j -1} \times 2$，也即前面j个只能选$\times$，第j+1个只能选$+,-$

考虑动态，你就是要维护n个式子的和

如果你改$a_i$，就会对前i个式子产生影响，你直接对前i个式子除掉$a_i$，再乘上新的$a_i$，用线段树维护即可

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
const int maxn = 1e5 + 100, mod = 1e9 + 7;
int a[maxn], s[maxn];
LL t[maxn << 2], tag[maxn << 2]; 
int Pow (int x, int p)
{
	if (p < 0) return 0;
	int ans = 1;
	while (p)
	{
		if (p & 1) ans = 1LL * ans * x % mod;
		x = 1LL * x * x % mod; p >>= 1;
	}
	return ans;
}
void pushup(int o) { t[o] = (t[o << 1] + t[o << 1 | 1]) % mod; }
void pushdown(int o)
{
	if(tag[o] == 1) return ;
	t[o << 1] = t[o << 1] * tag[o] % mod; t[o << 1 | 1] = t[o << 1 | 1] * tag[o] % mod;
	tag[o << 1] = tag[o << 1] * tag[o] % mod; tag[o << 1 | 1] = tag[o << 1 | 1] * tag[o] % mod;
	tag[o] = 1;
}	
void build(int o, int l, int r)
{
	tag[o] = 1;
	if(l == r) { t[o] = s[l]; return ; }
	int mid = (l + r) >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
	pushup(o);
}
void upt(int o, int l, int r, int x, int y, int v)
{
	if(x <= l && r <= y)
	{
		t[o] = t[o] * (LL)v % mod; tag[o] = tag[o] * (LL)v % mod;
		return ;
	}
	int mid = (l + r) >> 1;
	pushdown(o);
	if(x <= mid) upt(o << 1, l, mid, x, y, v);
	if(y > mid) upt(o << 1 | 1, mid + 1, r, x, y, v);
	pushup(o);
}
int main()
{
	freopen("math.in", "r", stdin);
	freopen("math.out", "w", stdout);
	int n = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	LL fac = 1;
	for(int i = 1; i < n; ++i)
	{
		fac = fac * a[i] % mod;
		s[i] = fac * Pow(3, n - i - 1) % mod * 2 % mod; 
	}
	s[n] = fac * a[n] % mod; 
	build(1, 1, n);
	for(int i = 1; i <= m; ++i)
	{
		int x = read(), y = read();
		upt(1, 1, n, x, n, Pow(a[x], mod - 2));
		a[x] = y;
		upt(1, 1, n, x, n, a[x]);
		cout << t[1] << endl;
	}
	return 0;
}
```

