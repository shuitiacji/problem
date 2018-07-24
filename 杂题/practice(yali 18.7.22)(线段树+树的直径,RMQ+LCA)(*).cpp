#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
const int maxn = 5e5 + 10, maxm = maxn << 1;
int e, tot1, tot2, n, m;
int to[maxm], nxt[maxm], head[maxn], dep[maxn], First[maxn], dfn[maxn], End[maxn], idfn[maxn], col[maxn];
pair<int, int> st[maxn << 2][24], now;
void add(int x, int y)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e;
	to[++e] = x; nxt[e] = head[y]; head[y] = e;
}
void dfs(int u, int fa)
{
	dfn[u] = ++tot1; idfn[tot1] = u; First[u] = ++tot2; dep[u] = dep[fa] + 1;
	st[tot2][0] = make_pair(dep[u], u);
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs(v, u);
		st[++tot2][0] = make_pair(dep[u], u);
	}
	End[u] = tot1;
}
int Log[maxn << 2];
void RMQ()
{
	for(int i = 2; i <= tot2; ++i) Log[i] = Log[i >> 1] + 1;
	for(int i = 1; i <= Log[tot2]; ++i)
		for(int j = 1; j + (1 << i) <= tot2; ++j)
/**/		st[j][i] = min(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
}
int Lca(int x, int y)
{
	x = First[x]; y = First[y];
	if(x > y) swap(x, y);
	return min(st[x][Log[y - x + 1]], st[y - (1 << Log[y - x + 1]) + 1][Log[y - x + 1]]).second;
}
int dist(int x, int y)
{
	if(y == -1 && x == -1) return -1;
	if(x == -1 || y == -1) return 0;
	int tmp = Lca(x, y);
	return dep[x] + dep[y] - 2 * dep[tmp];
}
#define ls o << 1, l, mid
#define rs o << 1 | 1, mid + 1, r
namespace SGT
{
	pair<int, int> t[maxn << 2];
	pair<int, int> merge(const pair<int, int> &a, const pair<int, int> &b)
	{
		pair<int, pair<int, int> > tmp1 = make_pair(dist(a.first, a.second), make_pair(a.first, a.second));
		pair<int, pair<int, int> > tmp2 = make_pair(dist(a.first, b.second), make_pair(a.first, b.second));
		pair<int, pair<int, int> > tmp3 = make_pair(dist(b.first, a.second), make_pair(b.first, a.second));
		pair<int, pair<int, int> > tmp4 = make_pair(dist(b.first, b.second), make_pair(b.first, b.second));
		pair<int, pair<int, int> > tmp5 = make_pair(dist(b.first, a.first), make_pair(b.first, a.first));
		pair<int, pair<int, int> > tmp6 = make_pair(dist(a.second, b.second), make_pair(a.second, b.second));
		return max(tmp1, max(tmp2, max(tmp3, max(tmp4, max(tmp5, tmp6))))).second;
	}
	void build(int o, int l, int r)
	{
		t[o].first = t[o].second = -1;
		if(l == r)
		{
			t[o].first = idfn[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(ls); build(rs);
		t[o] = merge(t[o << 1], t[o << 1 | 1]);
	}
	void upt(int o, int l, int r, int x, int fg)
	{
		if(l == r)
		{
			t[o].first = t[o].second = -1;
			if(fg) t[o].first = idfn[l];
			return ;
		}
		int mid = (l + r) >> 1;
		if(x <= mid) upt(ls, x, fg);
		else upt(rs, x, fg);
		t[o] = merge(t[o << 1], t[o << 1 | 1]);
	}
	void que(int o, int l, int r, int x, int y)
	{
		if(x <= l && r <= y) 
		{
			now = merge(now, t[o]);
			return ;
		}
		int mid = (l + r) >> 1;
		if(x <= mid) que(ls, x, y);
		if(y > mid) que(rs, x, y);
	}
}	
int main()
{
	freopen("practice.in", "r", stdin);
	freopen("practice.out", "w", stdout);
	n = read();
	for(int i = 1; i < n; ++i)
	{
		int x = read(), y = read();
		add(x, y);
	}
	dfs(1, 0);
	RMQ();
	SGT::build(1, 1, tot1);
	m = read();
	for(int i = 1; i <= m; ++i)
	{
		char A[3]; int x;
		scanf("%s", A); x = read();
		if(A[0] == 'C')
		{
			col[x] ^= 1;
			if(col[x] == 0) SGT::upt(1, 1, tot1, dfn[x], 1);
			else SGT::upt(1, 1, tot1, dfn[x], 0);
		}
		else 
		{
			now = make_pair(-1, -1);
			SGT::que(1, 1, tot1, dfn[x], End[x]);
			printf("%d\n", dist(now.first, now.second));
		}
	}
	return 0;
}
/*
题意:Rudy Brave Gay 是一名刻苦训练的运动员,为了夺得总冠军,Rudy Brave Gay 开始了
夏季集训。科尔给 Rudy Brave Gay 准备了一棵以 1 为根的树,这棵树上有黑色、白色两种节
点。科尔每次会给 Rudy Brave Gay 划分一个子树出来让他在上面练习运球。由于 Rudy Brave
Gay 太 Brave 了,他只愿意以黑色节点为起点和终点运球,于是他想知道划分区域内满足条
件的路径最长是多少。一开始全部都是黑点,为了考验 Rudy Brave Gay,科尔还会修改点的
颜色。

思路:
有一种很套路的线段树维护树的直径的方法
先把树上节点dfs序映射到线段树上
此时线段树上的节点维护的是自己这段区间内的点,所组成的直径的两个端点.
考虑两个区间合并时,假设我们已知两个子节点的直径和直径的两个端点,那么父节点的直径的两个端点一定是这四个端点的其中两个
由于是按dfs序来的,可以很方便的处理出子树内的直径
由于是线段树,还可以支持修改

debug:
38行,st[i][j],ij写反

BF 时的错误
1.在暴力dfs时,在判不能超出一个子树的区间时,我写的这个:
if(dfn[x] >= dfn[u] || End[x] <= dfn[u]) continue;
应该把等号去掉
2.在查询set中的末尾元素时,我用了这个:
*(SET.end() - 1)
应用 *(--SET.end())
*/
