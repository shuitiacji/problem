#include<bits/stdc++.h>
using namespace std;
#define ls o << 1, l, mid
#define rs (o << 1) | 1, mid, r
#define hash HHHAASSHH
typedef long long LL;
const int maxn = 1e5 + 5;
int n, a, b, c, m, q;
char s[maxn];
int hash[maxn << 2], hashN;
struct node
{
	int x, y;
}Q[maxn];
int cnt;
namespace SGT{
	int Sum[maxn << 4], tag[maxn << 4];
	void maintain(int o)
	{
		Sum[o] = Sum[o << 1] + Sum[(o << 1) | 1];
	}
	void pushdown(int o, int len)
	{
		if(tag[o] == 0) return ;
		Sum[o << 1] += tag[o] * (len >> 1);
		Sum[(o << 1) | 1] += tag[o] * (len - (len >> 1));
		tag[o << 1] += tag[o];
		tag[(o << 1) | 1] += tag[o];
		tag[o] = 0;
	}
	void upt(int o, int l, int r, int x, int y, int v)
	{
		if(x <= l && r <= y)
		{
			Sum[o] += (r - l) * v; tag[o] += v; return ;
		}
		pushdown(o, r - l);
		int mid = (l + r) >> 1;
		if(x < mid) upt(ls, x, y, v);
		if(y > mid) upt(rs, x, y, v);
		maintain(o);
	}
	int que(int o, int l, int r, int x)
	{
		if(l + 1 == r) return Sum[o];
		pushdown(o, r - l);
		int mid = (l + r) >> 1;//, ret = 0;
		if(x < mid) return que(ls, x);
		else return que(rs, x);
	}
}
int find(int x)
{
	return lower_bound(hash, hash + hashN, x) - hash;
}
void UPT(int l, int r, int v)
{
	if(l > r) SGT::upt(1, 0, hashN, find(l), find(n), v), SGT::upt(1, 0, hashN, find(0), find(r), v);
	else SGT::upt(1, 0, hashN, find(l), find(r), v);
}
/**/int mod(int x)
{
	return x >= n ? x - n : x;
}
int main()
{
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	scanf("%d%d%d%d%d", &n, &a, &b, &c, &m);
	scanf("%s", s);
	scanf("%d", &q);
	for(int i = 1; i <= q; ++i) scanf("%d%d", &Q[i].x, &Q[i].y);
	for(int i = 0; i < m; ++i)
	{
		int d = (LL) a * i % n;
		hash[hashN++] = mod(c - d + n);
		hash[hashN++] = mod(n - d + n);
		hash[hashN++] = mod(0 - d + n);
	}
	for(int i = 1; i <= q; ++i)
		hash[hashN++] = ((LL)Q[i].y * a + b) % n;
	sort(hash, hash + hashN);
	hashN = unique(hash, hash + hashN) - hash;
	for(int i = 0; i < m; ++i)
	{
		int d = (LL) a * i % n;
		if(s[i] == '1')
			UPT(mod(0 - d + n), mod(c - d + n), 1);
		else 
			UPT(mod(c - d + n), mod(n - d + n), 1);
	}
	for(int i = 1; i <= q; ++i)
	{
		if(Q[i].x == 1)
		{
			int d = ((LL) a * Q[i].y + b) % n;
			printf("%d\n", SGT::que(1, 0, hashN, find(d)));
		}
		else {
			int d = (LL) a * Q[i].y % n;
			if(s[Q[i].y] == '1')
			{
				s[Q[i].y] = '0';
				UPT(mod(0 - d + n), mod(c - d + n), -1);
				UPT(mod(c - d + n), mod(n - d + n), 1);
			}
			else 
			{
				s[Q[i].y] = '1';
				UPT(mod(c - d + n), mod(n - d + n), -1);
				UPT(mod(0 - d + n), mod(c - d + n), 1);
			}
		}
	}
	return 0;
}
/*
题意：
给定一个长度为n的01串和一个长度为m的01串T
S通过给定的参数a,b,c构造，其中a满足gcd(a,n) = 1
Si = [(a*i + b) mod n >= c]
现在有q个操作或询问
1 p：询问S的第p位开始往后取m位得到的字符串与T有多少位不同
2 p：将T的第p位取反

思路：
观察 S 的生成方式, 发现 (ai + b) mod n 会取遍 [0, n) 的所有整数, 形成一个排列.
考虑 T i = 1 的情况, 此时如果某个询问 p 在这一位有贡献, 也就是 S p+i ̸ = T i , 一定有
S p+i ∈ [0, c)
S p ∈ [0 − ai, c − ai)
T i = 0 的情况同理. 注意上述的区间是模意义下的, 实际上可能对应着一个或两个区间.
所以我们只需对每 T 的每一位分开预处理贡献即可. 时间复杂度 O(m log m).

debug:
1.需要离散化，mod注意一下，要弄个最大的上界
*/
