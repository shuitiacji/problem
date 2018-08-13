#include<bits/stdc++.h>
using namespace std;
#define debug(...) fprintf(stderr, __VA_ARGS__)
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
const int maxn = 3e5 + 10;
#define ls (t[x].ch[0])
#define rs (t[x].ch[1])
namespace LCT
{
	struct node
	{
		int ff, ch[2];
		int v, s, rev;
	}t[maxn];
	int isroot(int x) {return (t[t[x].ff].ch[0] != x && t[t[x].ff].ch[1] != x); }
	void pushup(int x) { t[x].s = t[ls].s ^ t[rs].s ^ t[x].v; }
	void pushdown(int x)
	{
		if(!t[x].rev) return ;
		swap(ls, rs);
		if(ls) t[ls].rev ^= 1; if(rs) t[rs].rev ^= 1;
		t[x].rev = 0;
	}
	void rotate(int x)
	{
		int y = t[x].ff, z = t[y].ff;
		int d = (t[y].ch[1] == x);
/**/	if(!isroot(y)) t[z].ch[t[z].ch[1] == y] = x; t[x].ff = z;
		t[y].ch[d] = t[x].ch[d ^ 1]; t[t[x].ch[d ^ 1]].ff = y;
		t[x].ch[d ^ 1] = y; t[y].ff = x;
		pushup(y); pushup(x);
	}
	int s[maxn], top;
	void splay(int x)
	{
/**/	s[top = 1] = x;
		for(int i = x; !isroot(i); i = t[i].ff) s[++top] = t[i].ff;
		while(top) pushdown(s[top--]);
		while(!isroot(x))
		{
			int y = t[x].ff, z = t[y].ff;
			if(!isroot(y))
				(t[y].ch[0] == x) ^ (t[z].ch[0] == y) ? rotate(x) : rotate(y);
			rotate(x);
		}
	}
	void access(int x) { for(int y = 0; x; y = x, x = t[x].ff) splay(x), rs = y, pushup(x); }
	void makeroot(int x) { access(x); splay(x); t[x].rev ^= 1; }
	void split(int x, int y) { makeroot(x); access(y); splay(y); }
	void link(int x, int y) { makeroot(x); t[x].ff = y; }
	void cut(int x, int y) { split(x, y); if(t[y].ch[0] == x) t[x].ff = t[y].ch[0] = 0; }
	int findroot(int x) { access(x); splay(x); while(ls) x = ls; return x; }
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	int n = read(), m = read();
	for(int i = 1; i <= n; ++i) LCT::t[i].v = read();
	for(int i = 1; i <= m; ++i)
	{
		int opt = read(), x = read(), y = read();
		if(opt == 0) { LCT::split(x, y); printf("%d\n", LCT::t[y].s); }
		if(opt == 1) { if(LCT::findroot(x) != LCT::findroot(y)) LCT::link(x, y); }
		if(opt == 2) LCT::cut(x, y);
		if(opt == 3) { LCT::makeroot(x); LCT::t[x].v = y; LCT::pushup(x); }
	}
	return 0;
}
/*
debug:
18.8.10
1.34行,不要写成!isroot(z)
2.43，写成==
*/
