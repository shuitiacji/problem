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
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
const int maxn = 2e5 + 10;
const int maxnode = (int)(maxn * 2.8);
const int mod = 998244353;
int n, q;
namespace SGT
{
	int mul[maxnode], add[maxnode], sz[maxnode], sum[maxnode];
	gp_hash_table<int, int> appear[maxnode], full[maxnode];
	void build(int o, int l, int r)
	{
		add[o] = 0; mul[o] = 1; sum[o] = 0; sz[o] = r - l + 1;
		if(l == r) return ;
		int mid = (l + r) >> 1;
		build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
	}
	void pushdown(int o)
	{
		if(mul[o] > 1)
		{
			sum[o << 1] = 1LL *	sum[o << 1] * mul[o] % mod;
			sum[o << 1 | 1] = 1LL * sum[o << 1 | 1] * mul[o] % mod;
			add[o << 1] = 1LL * add[o << 1] * mul[o] % mod;
			add[o << 1 | 1] = 1LL * add[o << 1 | 1] * mul[o] % mod;
			mul[o << 1] = 1LL * mul[o << 1] * mul[o] % mod;
			mul[o << 1 | 1] = 1LL * mul[o << 1 | 1] * mul[o] % mod;
			mul[o] = 1;
		}
		if(add[o])
		{
			sum[o << 1] = (sum[o << 1] + 1LL * add[o] * sz[o << 1] % mod) % mod;
			sum[o << 1 | 1] = (sum[o << 1 | 1] + 1LL * add[o] * sz[o << 1 | 1]) % mod;
			add[o << 1] = (add[o << 1] + add[o]) % mod;
			add[o << 1 | 1] = (add[o << 1 | 1] + add[o]) % mod;
			add[o] = 0;
		}
	}
	void pushup(int o)
	{
		sum[o] = (sum[o << 1] + sum[o << 1 | 1]) % mod;
	}
	void upt(int o, int l, int r, int x, int y, int v, int fg)
	{
		if(full[o].find(v) != full[o].end()) fg = 1;
		if(x <= l && r <= y)
		{
			if(fg)
			{
				mul[o] = mul[o] * 2 % mod;
				sum[o] = sum[o] * 2 % mod;
				add[o] = add[o] * 2 % mod;
				return ;
			}
			if(appear[o].find(v) == appear[o].end())
			{
				full[o][v] = 1;
				sum[o] = (sum[o] + sz[o]) % mod;
				add[o] = (add[o] + 1) % mod;
				return ;
			}
		}
		pushdown(o);
		appear[o][v] = 1;
		int mid	= (l + r) >> 1;
		if(x <= mid) upt(o << 1, l, mid, x, y, v, fg);
		if(y > mid) upt(o << 1 | 1, mid + 1, r, x, y, v, fg);
		pushup(o);
	}
	int que(int o, int l, int r, int x, int y)
	{
		if(x <= l && r <= y)
			return sum[o];
		int mid = (l + r) >> 1;
		int ret = 0;
		pushdown(o);
		if(x <= mid) ret += que(o << 1, l, mid, x, y);
		if(y > mid) ret += que(o << 1 | 1, mid + 1, r, x, y);
		return ret % mod;
	}
}
int main()
{
	freopen("multiset.in", "r", stdin);
	freopen("multiset.out", "w", stdout);
	n = read(); q = read();
	SGT::build(1, 1, n);
	for(int i = 1; i <= q; ++i)
	{
		int opt = read(), l = read(), r = read();
		if(opt == 1)
		{
			int x = read();
			SGT::upt(1, 1, n, l, r, x, 0);
		}
		else printf("%d\n", SGT::que(1, 1, n, l, r));
	}	
	return 0;
}
/*
题意：
你的魔法导师有 n 个魔法抽屉, 编号为 1, 2, 3, ..., n, 并且这些魔法抽屉和它们的主人一样法力无边.
这些抽屉原本都是给魔法导师存放贵重物品的, 但由于这几天魔法导师外出旅行, 带走了所有的物品, 所以现在所有抽屉都是空的.
对于所有的魔法抽屉都有一个相同的收纳机制, 若该抽屉要收纳一个没有在该抽屉中出现过的物品, 则将这个物品简单的收纳进去; 而当该抽屉要收纳一个已经在该抽屉中出现过的物品, 则该抽屉中的每个物品会被复制成双.
例如, 该抽屉中原本有 1 个 1号物品, 2 个 2号物品, 1 个 3号物品. 若再将一个 2号物品放入该抽屉中, 则现该抽屉中有 2 个 1号物品, 4 个 2号物品, 2 个 3号物品. 而若将一个 4号物品放入该抽屉中, 则该抽屉中会有 1, 3, 4号物品各 1个, 2号物品 2个.
这显然不符合质量守恒定律和能量守恒定律, 然而在魔法学院却司空见惯.
你的魔法导师发现有人在动他的魔法抽屉, 于是给你隔空传来了一道难题, 他给了你 q 个操作,
分为两类.
第一类操作表示你需要对于第 l, l + 1, l + 2, ..., r 个抽屉施展魔法,放入 x 号物品.
第二类操作表示你需要输出第 l, l + 1, l + 2, ..., r 个抽屉的物品个数总和, 这个和可能很大, 所
以请你输出答案对 998244353 取模的结果.

思路：
势能分析线段树，能直接打tag就打，不能就暴力递归下去。
对每个节点记一个appear，一个full，这两个hash数组分别表示这个节点中出没出现过一个抽屉有这个物品，和这个节点的抽屉是不是全有这个个物品。
显然如果full中满足，则可直接打*2标记，若appear没有这个物品，则打+1标记，若full不满足而appear满足，就暴力递归。
会被卡空间，可以使用gp_hash_table，以及玄学调参线段树，空间开2.8倍。

*/
