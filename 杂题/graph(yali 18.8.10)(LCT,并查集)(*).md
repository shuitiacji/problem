### Description

小G喜欢四处旅游, 但是由于城市发展速度太快, 小G去旅游时经常计划赶不上变化.

小G发现自己的旅行计划一共涉及 NN 个城市, 每个城市初始时有一个欢乐度 WiWi, 一共有三种影响旅行计划的事件可能发生:

`1 a b` 新建一条连接 a, b 两座城市的边.

`2 a b` 将 a 城市的欢乐度改为 b.

`3 a b` 进行一次 a 城市到 b 城市的旅行.

对于每次旅行, 小G会将每一条边任意定向, 然后从 a 出发经过一些点到达 b, 在这个过程中, 小G可以经过一个城市多次, 小G想知道自己经过的所有城市的欢乐度之和的最大值是多少; 若 a 城市无法到达 b 城市, 输出 `-1`.

<!--more-->

### Solution

考虑怎样定向, 那么一定至少需要一条链能够从 a 到达 b. 对于链之外的点,则需要形成环才能够绕回主链上, 不难发现当边形成环时,可以将环上的点缩起来,而且不会影响其他点的联通情况.

具体实现可以用LCT，用并查集维护缩起来的编号

LCT维护边双的基本操作

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define ls(x) (t[x].ch[0])
#define rs(x) (t[x].ch[1])
const int maxn = 150010;
int read()
{
	int x = 0, f = 1; char c = getchar(); 
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
int f[maxn];
int get_fa(int x) { return x == f[x] ? x : f[x] = get_fa(f[x]); }
void uni(int x, int y)
{
	x = get_fa(x); y = get_fa(y);
	f[x] = y;
}
namespace LCT
{
	struct node
	{
		int ff, ch[2], v, s, rev;
	}t[maxn];
	int bel[maxn], s[maxn], top;
	int getb(int x) { return x == bel[x] ? x : bel[x] = getb(bel[x]); }
	int isroot(int x) { return (t[getb(t[x].ff)].ch[0] != x && t[getb(t[x].ff)].ch[1] != x); }
/**/void pushup(int x) { t[x].s = t[ls(x)].s + t[rs(x)].s + t[x].v; }
	void rotate(int x)
	{
		int y = getb(t[x].ff), z = getb(t[y].ff);
		int d = (t[y].ch[1] == x);
		if(!isroot(y)) t[z].ch[t[z].ch[1] == y] = x; t[x].ff = z;
		t[y].ch[d] = t[x].ch[d ^ 1]; t[t[x].ch[d ^ 1]].ff = y;
		t[x].ch[d ^ 1] = y; t[y].ff = x;
		pushup(y); pushup(x);
	}
	void pushdown(int x)
	{
		if(!t[x].rev) return ;
		t[x].rev ^= 1;
		swap(ls(x), rs(x));
/**/	if(ls(x)) t[ls(x)].rev ^= 1; 
/**/	if(rs(x)) t[rs(x)].rev ^= 1;
	}	
	void splay(int x)
	{
		s[top = 1] = x;
/**/	for(int i = x; !isroot(i); i = getb(t[i].ff)) s[++top] = getb(t[i].ff);
		while(top) pushdown(s[top--]);
		while(!isroot(x))
		{
			int y = getb(t[x].ff), z = getb(t[y].ff);
			if(!isroot(y))
				(ls(y) == x) ^ (ls(z) == y) ? rotate(x) : rotate(y);
			rotate(x);
		}
	}
	void access(int x) { for(int y = 0; x; y = x, x = getb(t[x].ff)) splay(x), rs(x) = y, pushup(x); }
	void makeroot(int x) { access(x); splay(x); t[x].rev ^= 1; }
	void dfs(int x, int tmp)
	{
		bel[x] = tmp; t[tmp].v += t[x].v;
		if(ls(x)) dfs(ls(x), tmp);
		if(rs(x)) dfs(rs(x), tmp);
	}
	void link(int x, int y)
	{
		x = getb(x); y = getb(y);
		if(x == y) return ;
		if(get_fa(x) != get_fa(y))
		{
			makeroot(x); t[x].ff = y;
			uni(x, y);
		}
		else 
		{
			makeroot(x); access(y); splay(y);
			dfs(ls(y), y);
		}
	}
	void split(int x, int y)
	{
		x = getb(x); y = getb(y);
		makeroot(x); access(y); splay(y);
		printf("%d\n", t[y].s);
	}
}
int main()
{
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
	int n = read(), m = read();
	for(int i = 1; i <= n; ++i) LCT::t[i].v = read();
	for(int i = 1; i <= n; ++i) f[i] = i, LCT::bel[i] = i;
	for(int i = 1; i <= m; ++i)
	{
		int opt = read(), a = read(), b = read();
		if(opt == 1) LCT::link(a, b);
		if(opt == 2) { LCT::makeroot(LCT::getb(a)); LCT::t[LCT::getb(a)].v = LCT::getb(b); LCT::pushup(LCT::getb(a)); }
		if(opt == 3) { if(get_fa(a) != get_fa(b)) { puts("-1"); continue; } LCT::split(a, b); }
	}
	return 0;
}
```



### Debug

1.30行，不要把s写成v

2.45行，46行，要写if

3.!isroot(i)不要写成i