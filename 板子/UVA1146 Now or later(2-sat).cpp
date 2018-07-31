#include<bits/stdc++.h>
using namespace std;
const int maxn = 4100, maxm = maxn * maxn * 8;
int to[maxm], nxt[maxm], head[maxn], e, sta[maxn], dfn[maxn], low[maxn], sccno[maxn], a[maxn];
int fg;
void add(int x, int y)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e;
}
int tot, scc_cnt, top, n;
void tarjan(int u)
{
	low[u] = dfn[u] = ++tot; sta[++top] = u;
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(!dfn[v]) { tarjan(v); low[u] = min(low[u], low[v]); }
		else if(!sccno[v]) { low[u] = min(low[u], dfn[v]); }
	}
	if(low[u] == dfn[u])
	{
		++scc_cnt;
		while(1)
		{
			int now = sta[top--];
			sccno[now] = scc_cnt;
			if(now == u) break;
		}
	}
}
int ck(int x)
{
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(sccno, 0, sizeof(sccno));
	memset(head, 0, sizeof(head));
	e = 0; scc_cnt = 0; tot = 0; top = 0;
	if(x == 3) fg = 1;
	for(int i = 1; i < n; ++i)
		for(int j = i + 1; j <= n; ++j)
		{
			if(abs(a[i << 1] - a[j << 1]) < x) { add(j << 1, i << 1 | 1), add(i << 1, j << 1 | 1); }
			if(abs(a[i << 1] - a[j << 1 | 1]) < x) { add(i << 1, j << 1), add(j << 1 | 1, i << 1 | 1); }
			if(abs(a[i << 1 | 1] - a[j << 1]) < x) { add(i << 1 | 1, j << 1 | 1), add(j << 1, i << 1); }
			if(abs(a[i << 1 | 1] - a[j << 1 | 1]) < x) { add(i << 1 | 1, j << 1), add(j << 1 | 1, i << 1); }
		}
	fg = 0; 
	for(int i = 1; i <= n; ++i)
	{
		if(!dfn[i << 1]) tarjan(i << 1);
		if(!dfn[i << 1 | 1]) tarjan(i << 1 | 1);
	}
	for(int i = 1; i <= n; ++i)
		if(sccno[i << 1] == sccno[i << 1 | 1]) return 0;
	return 1;
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	while(scanf("%d", &n) != EOF)
	{
		for(int i = 1; i <= n; ++i) scanf("%d%d", &a[i << 1], &a[i << 1 | 1]);
		int l = 0, r = 1e7, ans;
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			if(ck(mid)) { ans = mid; l = mid + 1; }
			else r = mid - 1;
		}
		cout << ans << endl;
	}	
	return 0;
}
/*
debug:
7.30
1.建图时边是单向的
*/
