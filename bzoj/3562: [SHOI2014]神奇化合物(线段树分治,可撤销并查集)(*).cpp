#include<bits/stdc++.h>
using namespace std;
struct edge
{
	int u, v;
	bool operator < (const edge &b) const 
	{
/**/	if(min(u, v) == min(b.u, b.v)) return max(u, v) < max(b.u, b.v);
/**/	else return min(u, v) < min(b.u, b.v);
	}
};
const int maxn = 400010;
int f[maxn], sz[maxn], top, fg[maxn], beg[maxn], fin[maxn], tot, m, n, q, ans[maxn], que[maxn], num;
pair<int, int> sta[maxn]; 
vector<edge> t[maxn << 2];
map<edge, int> S;
edge e[maxn];
int Sum[maxn << 2];
int find(int x)
{
	while(f[x] != x) x = f[x];
	return x;
}
void undo(int tmp)
{
	while(top > tmp)
	{
		sz[sta[top].first] -= sz[sta[top].second];
		f[sta[top].second] = sta[top].second;
		if(fg[top]) fg[top] = 0, num++;
		--top;
	}
}
void uni(edge E)
{
	int u = E.u, v = E.v;
	int f1 = find(u), f2 = find(v);
	if(f1 == f2) return ;
	num--;
	if(sz[f1] < sz[f2]) swap(f1, f2);
	f[f2] = f1;
	sz[f1] += sz[f2];
	sta[++top] = make_pair(f1, f2);
	fg[top] = 1;
}
void build(int o, int l, int r)
{
	if(l == r)
	{
		Sum[o] = que[l];
		return ;
	}
	int mid = (l + r) >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
	Sum[o] = Sum[o << 1] + Sum[o << 1 | 1];
}
void upt(int o, int l, int r, int x, int y, edge E)
{
	if(x <= l && r <= y)
	{
		t[o].push_back(E);
		return ;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) upt(o << 1, l, mid, x, y, E);
	if(y > mid) upt(o << 1 | 1, mid + 1, r, x, y, E);
}
void dfs(int o, int l, int r)
{
	int tmp = top;
	for(int i = 0; i < t[o].size(); ++i)
		uni(t[o][i]);
	int mid = (l + r) >> 1;
	if(l == r)
	{
		ans[l] = num;
		goto nxt;
	}
	if(Sum[o << 1]) dfs(o << 1, l, mid);
	if(Sum[o << 1 | 1]) dfs(o << 1 | 1, mid + 1, r);
	nxt:;
	undo(tmp);
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out" ,"w", stdout);
	scanf("%d%d", &n, &m);
	tot = 0;
	for(int i = 1; i <= m; ++i)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		beg[++tot] = 1;
		e[tot] = (edge){a, b};
		S[e[tot]] = tot;
	}
	scanf("%d", &q);
	for(int i = 1; i <= q; ++i)
	{
		char A[3];
		int a, b;
		scanf("%s", A);
		if(A[0] == 'Q')
			que[i] = 1;
		if(A[0] == 'A')
		{
			scanf("%d%d", &a, &b);
			beg[++tot] = i;
			e[tot] = (edge){a, b};
			S[e[tot]] = tot;
		}
		if(A[0] == 'D')
		{
			scanf("%d%d", &a, &b);
			int tmp = S[(edge){a, b}];
			fin[tmp] = i;
			S[(edge){a, b}] = 0;
		}
	}
	for(int i = 1; i <= tot; ++i)
		if(!fin[i]) fin[i] = q;
	build(1, 1, q);
	for(int i = 1; i <= tot; ++i)
		upt(1, 1, q, beg[i], fin[i], e[i]);
	for(int i = 1; i <= n; ++i) f[i] = i, sz[i] = 1;
	num = n;
	dfs(1, 1, q);
	for(int i = 1; i <= q; ++i)
		if(que[i]) printf("%d\n", ans[i]);
	return 0;
}
/*
题意：
给定一个无向图，有删边、添边两种操作，还有询问当前图中连通块个数。

思路：
考虑离线做法，发现并不好搞，因为涉及到删边操作，那么加边操作的贡献是一段段的，我们并不能很方便的知道一个询问被几个加边操作贡献.
这种存在撤销操作的题目，我们可以用线段树分治离线解决．
考虑一个加边操作的贡献是区间性的，我们为什么不用擅长区间修改的线段树解决．
考虑建一个时间线段树，每个叶子节点表示一个时刻．我们求出每一条边在整个过程中出现的连续时间段。将这些边加入线段树中。每一条边至多在线段树的log个区间中出现。
再dfs向所有存在询问的叶子节点，像标记永久化一样把路上的所有边加入可撤销并查集，离开节点时，在并查集中撤销这个节点的所有边．

debug:
8,9行，b.u, b.v写成u,v
*/
