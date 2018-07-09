#include<bits/stdc++.h>
using namespace std;
const int maxn = 510, maxm = maxn * maxn / 2;
typedef long long LL;
struct node
{
	int u, v;
	LL w;
}e[maxm];
LL ret;
int n, m, root;
LL in[maxn];
int pre[maxn], vis[maxn], id[maxn]; 
void gao()
{
	while(1)
	{
		for(int i = 1; i <= n; ++i) in[i] = LLONG_MAX;
		for(int i = 1; i <= m; ++i)
		{
			if(in[e[i].v] > e[i].w && e[i].v != e[i].u)
			{
				in[e[i].v] = e[i].w;
				pre[e[i].v] = e[i].u;
			}
		}
		for(int i = 1; i <= n; ++i)
		{
			if(i == root) continue;
			if(in[i] == LLONG_MAX)
			{
				ret = -1; return ;
			}
		}
		int cnt = 0;
		in[root] = 0;
		memset(id, -1, sizeof(id));
		memset(vis, -1, sizeof(vis));
		for(int i = 1; i <= n; ++i)
		{
			ret += in[i];
			int v = i;
			while(vis[v] != i && v != root && id[v] == -1)
			{
				vis[v] = i; v = pre[v];
			}
			if(v != root && id[v] == -1)
			{
				++cnt;
				for(int u = pre[v]; u != v; u = pre[u]) id[u] = cnt;
				id[v] = cnt; 
			}
		}
		if(cnt == 0)break;
		for(int i = 1; i <= n; ++i) if(id[i] == -1) id[i] = ++cnt;
		for(int i = 1; i <= m; ++i)
		{
			int v = e[i].v;
			e[i].u = id[e[i].u];
			e[i].v = id[e[i].v];
			if(e[i].u != e[i].v) e[i].w -= in[v];
		}
		n = cnt; root = id[root];
	}
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	LL sum = 0;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i)
	{
		int x, y; LL z;
		scanf("%d%d%lld", &x, &y, &z);
		e[i] = (node){x, y, z};
		sum += z;
	}
	sum++;
	for(int i = 1; i <= n; ++i)
/**/	e[++m] = (node){n + 1, i, sum};
	n++;
	root = n;
	gao();
	if(ret - sum >= sum - 1) puts("-1");
	else cout << ret - sum << endl;
	return 0; 
}
/*
题意：
给定一个n个点m条边的带权有向图，不存在自环，可能存在重边。求出一个权值和最小的边集的子集，使得存在至少一个点可以通过这些边到达所有点。

思路：
无定根的最小树形图，可以设1个超级源，对所有点连一条权值比所有边总和都大的边，这样保证在有解的情况下，只会选一个根。但无解的情况，不是没有in的，因为超级源对每个点都有一条边，所以当选了两条超级源连出的边，即最后的答案>所有边的总和时，就是无解。

debug:
1.81行，++m写成i
*/
