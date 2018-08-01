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
const int maxn = 3e5 + 10, maxm = maxn << 1;
int to[maxm], nxt[maxm], head[maxn], e;
void add(int x, int y)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e;
	to[++e] = x; nxt[e] = head[y]; head[y] = e;
}
LL s1[maxn * 100], s2[maxn * 100]; int ls[maxn * 100], rs[maxn * 100], rt[maxn * 100]; LL val[maxn];
int tot, n, m, a[maxn];
void maintain(int o) { s1[o] = s1[ls[o]] + s1[rs[o]]; s2[o] = s2[ls[o]] + s2[rs[o]]; }
void upt(int &o, int l, int r, int p, int x1, int x2)
{
	if(!o) o = ++tot;
	if(l == r) { s1[o] += x1; s2[o] += x2; return ; }
	int mid = (l + r) >> 1;
	if(p <= mid) upt(ls[o], l, mid, p, x1, x2);
	else upt(rs[o], mid + 1, r, p, x1, x2);
	maintain(o);
}
LL ANS;
int merge(int x, int y, int l, int r)
{
	if(!x || !y) return x | y;
	if(l == r) { s1[x] += s1[y]; s2[x] += s2[y]; return x; }
	ANS += 1LL * s1[rs[x]] * s2[ls[y]];
	ANS += 1LL * s1[rs[y]] * s2[ls[x]];
	int mid = (l + r) >> 1;
	ls[x] = merge(ls[x], ls[y], l, mid);
	rs[x] = merge(rs[x], rs[y], mid + 1, r);
	maintain(x);
	return x;
}
void dfs(int u, int fa)
{
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs(v, u);
		ANS = 0;
		rt[u] = merge(rt[u], rt[v], 0, m);
		//cout << rt[u] << endl;
		val[u] += ANS;
	}
}
int main()
{
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	n = read(); m = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= n; ++i)
		if(a[i]) upt(rt[i], 0, m, 0, 0, i);
	for(int i = 1; i <= n - 1; ++i)
	{
		int x = read(), y = read();
		add(x, y);
	}
	for(int i = 1; i <= m; ++i)
	{
		int opt = read(), x = read();
		if(opt == 1)
		{
			upt(rt[x], 0, m, i, 1, 0);
			if(a[x]) val[x] += 1LL * x;
		}
		else 
		{
			a[x] ^= 1;
			if(a[x]) upt(rt[x], 0, m, i, 0, x);
			else upt(rt[x], 0, m, i, 0, -x);
		}
	}
	dfs(1, 0);
	for(int i = 1; i <= n; ++i) printf("%lld\n", val[i]);
	return 0;
}
/*
题意:
给出一颗 n 个节点的以 1 为根的有根树,树的节点从 1 到 n 编号,每个节点的初始权值即为节点的编号,同时每个节点有一个 ans 值,初始时均为 0 。树上有一些关键点。有 m 个操作,每个操作有如下两种:
1 x 对于树中的每一个关键点,在它与节点 x 的 lca 的 ans 值上加上该关键点的权值。
2 x 修改节点 x 的状态。如果节点 x 原来是一个关键点,则改为不是关键点;如果节点 原来不是一个关键点,则让它成为关键点。
现在,请你求出在执行完所有的 m 个操作之后,求每个节点的 ans 值。

思路：
首先我们直接考虑对每个节点记录操作1的次数以及关键点的权值和，然后dfs一次从底向上合并
但是显然这样会有问题，因为每一个修改状态会对之后的操作1产生影响
那么考虑对每个节点都建一颗时间线段树，动态开点
对于线段树每个节点同样维护val1(操作1的次数)以及val2(关键点的权值和)
自底向上进行线段树合并，只有前面的时间修改操作会对后面的操作1产生影响
在合并时，我们有Ans+=val1[rs[x]]∗val2[ls[y]]+val1[rs[y]]∗val2[ls[x]]
(ls,rs表示左右子树, xy表示两颗线段树当前节点)
那么这样就保证了时间顺序，而dfs自底向上合并又保证了树形结构顺序
时间复杂度O(nlogn)
*/
