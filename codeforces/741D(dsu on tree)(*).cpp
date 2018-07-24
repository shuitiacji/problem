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
int e, n;
int to[maxm], nxt[maxm], head[maxn], w[maxm], dep[maxn], sz[maxn], son[maxn], ans[maxn], a[maxn],t[(1 << 22) + 10];
void add(int x, int y, int z)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e; w[e] = z;
	to[++e] = x; nxt[e] = head[y]; head[y] = e; w[e] = z;
}
void dfs_init(int u, int fa)
{
	sz[u] = 1; son[u] = 0; dep[u] = dep[fa] + 1;
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
/**/	a[v] = a[u] ^ w[i];
		dfs_init(v, u);
		if(son[u] == 0 || sz[v] > sz[son[u]]) son[u] = v;
		sz[u] += sz[v]; 
	}
}
int cur, now;
void dfs_calc(int u, int fa)
{
	cur = max(cur, t[a[u]] + dep[u] - 2 * dep[now]);
	for(int i = 0; i < 22; ++i)
		cur = max(cur, t[a[u] ^ (1 << i)] + dep[u] - 2 * dep[now]);
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i]; if(v == fa) continue;
		dfs_calc(v, u);
	}
}
void dfs_set(int u, int fa, int keep)
{
	if(keep) t[a[u]] = max(dep[u], t[a[u]]);
	else t[a[u]] = -0x3f3f3f3f;
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i]; if(v == fa) continue;
		dfs_set(v, u, keep);
	}
}
void dsu(int u, int fa, int keep)
{
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa || v == son[u]) continue;
		dsu(v, u, 0); ans[u] = max(ans[u], ans[v]);
	}
/**/if(son[u]) dsu(son[u], u, 1), ans[u] = max(ans[u], ans[son[u]]);
	now = u;
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa || v == son[u]) continue;
		cur = 0;
		dfs_calc(v, u); dfs_set(v, u, 1);
		ans[u] = max(ans[u], cur);
	}
	ans[u] = max(ans[u], t[a[u]] - dep[u]);
	for(int i = 0; i < 22; ++i) ans[u] = max(ans[u], t[a[u] ^ (1 << i)] - dep[u]);
	t[a[u]] = max(t[a[u]], dep[u]);
	if(keep == 0) dfs_set(u, fa, 0);
}
int main()
{	
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	n = read();
	for(int i = 2; i <= n; ++i)
	{
		char A[3];
		int x = read(); scanf("%s", A);
		int z = 1 << (A[0] - 'a');
		add(x, i, z);
	}
	dfs_init(1, 0);
	memset(t, -0x3f, sizeof(t));
	dsu(1, 0, 1);
	for(int i = 1; i <= n; ++i) cout << ans[i] << ' ';
	return 0;
}
/*
题意:一棵根为1 的树，每条边上有一个字符（a-v共22种）。 一条简单路径被称为Dokhtar-kosh当且仅当路径上的字符经过重新排序后可以变成一个回文串。 求每个子树中最长的Dokhtar-kosh路径的长度。

思路:
dsu on tree 还可以处理树上路径问题
主要还是利用点分治的思想,把路径分为过当前根的和不过根的.
令s(i)表示1到i的路径的状态，状态是一个22位2进制数，每一位表示这个字符在路径上出现次数（偶数/奇数）。f(i)表示状态为i的当前可以统计的点的最大深度。并且显然如果能是回文串的话所有的字符数量为奇数个的最多只有一个。
用dsu on tree维护这个桶就可以了.
先继承重儿子的桶,再暴力扫轻儿子,每次在桶里找可以使当前为回文串的状态(一共23种)

这种奇偶可以转化成二进制,异或处理
一开始想的桶存的是到当前父亲路径上的值,不好继承,其实可以定一个总的即到根的路径上的值

debug:
1.25行,要写在dfs之前
2.61,忘记那个if了
*/
