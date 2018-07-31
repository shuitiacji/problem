#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int maxn = 2e5 + 10000, maxm = maxn << 1;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar();}
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
int to[maxm], nxt[maxm], head[maxn], dfn[maxn], low[maxn], tot, totp, cnt, isb[maxm], bel[maxn], vis[maxn];
vector<int> node[maxn];
int hs[maxm], HS[maxm];
int Vis[maxm];
int FG[maxm], fg[maxm];
int n, m, e;
void add(int x, int y)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e; fg[e] = 1;
	to[++e] = x; nxt[e] = head[y]; head[y] = e; fg[e] = -1;
}
void dfs1(int u, int fa)
{
	dfn[u] = low[u] = ++tot;
	for(int i = head[u]; i != -1; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		if(!dfn[v]) {
			dfs1(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] > dfn[u])
				isb[i] = 1, isb[i ^ 1] = 1;
		}
		else if(dfn[v] < low[u])
			low[u] = dfn[v];
	}
}
void dfs2(int u, int fa)
{
	bel[u] = cnt; node[cnt].pb(u);
	vis[u] = 1;
	for(int i = head[u]; i != -1; i = nxt[i])
	{
		if(isb[i]) continue;
		int v = to[i];
		if(vis[v]) continue;
		dfs2(v, fa);
	}
}
#define ls o << 1, l, mid
#define rs o << 1 | 1, mid + 1, r
namespace HLD
{
	int sz[maxn], son[maxn], dep[maxn], f[maxn], top[maxn], p[maxn], t[maxn << 2], tag[maxn << 2];
	void dfs1(int u, int fa)
	{
		sz[u] = 1; son[u] = 0; dep[u] = dep[fa] + 1; f[u] = fa;
		for(int i = head[u]; i != -1; i = nxt[i])
		{
			int v = to[i];
			if(v == fa) continue;
			if(i & 1) fg[i] = -fg[i], fg[i ^ 1] = -fg[i ^ 1];
			HS[i] = v;
			dfs1(v, u);
			if(!son[u] || sz[v] > sz[son[u]]) son[u] = v;
			sz[u] += sz[v];
		}
	}
	void dfs2(int u, int tp)
	{
		top[u] = tp; p[u] = ++totp;
		if(son[u]) dfs2(son[u], tp);
		for(int i = head[u]; i != -1; i = nxt[i])
		{
			int v = to[i];
			if(v == f[u] || v == son[u]) continue;
			dfs2(v, v);
		}
	}
	void pushdown(int o)
	{
		if(!tag[o]) return ;
		t[o << 1] = tag[o]; tag[o << 1] = tag[o];
		t[o << 1 | 1] = tag[o]; tag[o << 1 | 1] =tag[o];
		tag[o] = 0;
	}
	void upt(int o, int l, int r, int x, int y, int c)
	{
		if(x <= l && r <= y)
		{
			tag[o] = c; t[o] = c;
			return ;
		}
		pushdown(o);
		int mid = (l + r) >> 1;
		if(x <= mid) upt(ls, x, y, c);
		if(y > mid) upt(rs, x, y, c);
	}
	int que(int o, int l, int r, int x)
	{
		if(l == r) 
/**/		return t[o];
		pushdown(o);
		int mid = (l + r) >> 1;
		if(x <= mid) return que(ls, x);
		else return que(rs, x);
	}
	void find(int u, int v, int colu, int colv)
	{
		int f1 = top[u], f2 = top[v];
		while(f1 != f2)
		{
			if(dep[f1] < dep[f2]) swap(u, v), swap(f1, f2), swap(colu, colv);
/**/		upt(1, 1, totp, p[f1], p[u], colu);
			u = f[f1]; f1 = top[u];
		}
		if(u == v) return ;
		if(dep[u] < dep[v]) swap(colu, colv), swap(u, v);
		upt(1, 1, totp, p[v] + 1, p[u], colu);	
	}
}
int main()
{
	freopen("olddoc.in", "r", stdin);
	freopen("olddoc.out", "w", stdout);
	n = read(); m = read();
	e = -1;
	memset(head, -1, sizeof(head));
	for(int i = 1; i <= m; ++i)
	{
		int u = read(), v = read();
		add(u, v);
	}
	for(int i = 1; i <= n; ++i)
		if(!dfn[i])
			dfs1(i, 0);
	cnt = n;
	int M = e;
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
		{
			++cnt;
			dfs2(i, 0);
		}
	for(int i = n + 1; i <= cnt; ++i)
	{
		for(int j = 0; j < node[i].size(); ++j)
		{
			for(int k = head[node[i][j]]; k != -1; k = nxt[k])
			{
				int v = bel[to[k]];
				if(v == i) continue;
				if(Vis[k ^ 1] || Vis[k]) continue;
				Vis[k ^ 1] = Vis[k] = 1;
				add(i, v);
				FG[k] = 1;
				hs[k] = e - 1;
			}
		}
	}
	for(int i = n + 1; i <= cnt; ++i)
		if(!HLD::top[i])
			HLD::dfs1(i, 0),HLD::dfs2(i, i);
	int P = read();
	for(int i = 1; i <= P; ++i)
	{
		int x = read(), y = read();
		HLD::find(bel[x], bel[y], -1, 1);
	}
	for(int i = 0; i <= M; i += 2)
	{
		if(!HS[hs[i ^ 1]] && !HS[hs[i]] && !HS[hs[i ^ 1] ^ 1] && !HS[hs[i] ^ 1])
			printf("B");
		else
		{
			int tmp = 0;
			if(HS[hs[i ^ 1]]) tmp = HLD::que(1, 1, totp, HLD::p[HS[hs[i ^ 1]]]);
			if(HS[hs[i]]) tmp = HLD::que(1, 1, totp, HLD::p[HS[hs[i]]]);
			if(HS[hs[i ^ 1] ^ 1]) tmp = HLD::que(1, 1, totp, HLD::p[HS[hs[i ^ 1] ^ 1]]);
			if(HS[hs[i] ^ 1]) tmp = HLD::que(1, 1, totp, HLD::p[HS[hs[i] ^ 1]]);
			if(FG[i ^ 1]) tmp *= -1, tmp *= fg[hs[i ^ 1]];
			else tmp *= fg[hs[i]];
			if(tmp == 1) printf("R");
			if(tmp == -1) printf("L");
			if(tmp == 0) printf("B");
		}
	}
	return 0;
}
/*
题意：
世界线变动率 0.14934034
本来预定月亮中学的老中医 (lzy,并非出题人) 同学在中考时不小心考
挂了,拿了 5A1B,这样他就进入不了月亮中学了。他非常的伤心,思来想
去觉得他必须拯救自己,于是找到了他曾经发明的 D-mail,决定改变这个
悲惨的世界线,于是他需要发送数学压轴题的答案给但是考场上的自己,所
以他决定构造一台 Time Leap Machine
他现在有一台 Time Leap Machine 的原型,也就是一个 n 个点 m 条
边的无向图,他需要为每条边定向,同时为了精确跳转到考场上,他需要满
足一些限制,即定向后的图需要满足可以从 x 沿着有向边走到 y,现在为了
精确构造 Time Leap Machine,你必须确定每条边为了满足所有限制是只能
定某一个方向还是对任意方向都有合法方案存在
一行 m 个字符,其中第 i 个字符是:
如果只有 u i → v i 存在合法方案时,输出’R’
如果只有 u i ← v i 存在合法方案时,输出’L’
如果这条边不论如何定向都存在合法方案时,输出’B’


思路：
考虑对原图的边双缩点，发现只要是在边双内的边，由于都有两条路径，绝对是B。则问题转化成，给你一个树，选定几个路径，把树边染色。
树剖即可。

debug:
1.104行，写成t[l]
2.116行，不应该写成p[f1] + 1，因为一定要从一条链跳到另一条链，一定会走一条边，但最后uv在一条链上时，要加1,不然会跳出去
*/
