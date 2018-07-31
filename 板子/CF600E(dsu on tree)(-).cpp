#include<bits/stdc++.h>
using namespace std;
int e, tot, n;
const int maxn = 1e5 + 10, maxm = maxn << 1;
typedef long long LL;
int dfn[maxn], nxt[maxm], to[maxm], head[maxn], sz[maxn], son[maxn], End[maxn], cnt[maxn], col[maxn], idfn[maxn];
LL ans[maxn];
void add(int x, int y)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e;
	to[++e] = x; nxt[e] = head[y]; head[y] = e;
}
void dfs(int u, int fa)
{
	sz[u] = 1; son[u] = 0;
	dfn[u] = ++tot; idfn[tot] = u;
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs(v, u);
		if(son[u] == 0 || sz[v] > sz[son[u]]) son[u] = v;
		sz[u] += sz[v];
	}
	End[u] = tot;
}
LL maxsum, sum;
void dsu(int u, int fa, int keep)
{
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa || v == son[u]) continue;
		dsu(v, u, 0);
	}
	if(son[u]) dsu(son[u], u, 1);
/**/cnt[col[u]]++;
	if(cnt[col[u]] == maxsum) sum += col[u];
	else if(cnt[col[u]] > maxsum) maxsum = cnt[col[u]], sum = col[u];
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa || v == son[u]) continue;
		for(int j = dfn[v]; j <= End[v]; ++j)
		{
			cnt[col[idfn[j]]]++;
			if(cnt[col[idfn[j]]] == maxsum) 
				sum += col[idfn[j]];
			else if(cnt[col[idfn[j]]] > maxsum)
				maxsum = cnt[col[idfn[j]]], sum = col[idfn[j]];
		}
	}
	ans[u] = sum;
	if(keep == 0)
	{
		maxsum = 0; sum = 0;
/**/	for(int i = dfn[u]; i <= End[u]; ++i) cnt[col[idfn[i]]]--;
	}
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", &col[i]);
	for(int i = 1; i < n; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	dfs(1, 0);
	dsu(1, 0, 1);
	for(int i = 1; i <= n; ++i) cout << ans[i] << endl;
	return 0;
}
/*
题意：一棵树，每一个点有一个颜色，统计以每一个节点为根的子树中出现次数最多的颜色的编号和。

debug:
18.7.23
1.37,38一定要记得算上自己
2.57,是整个子树都清空,而非还保留重儿子
*/
