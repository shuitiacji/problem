#include<bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long LL;
const int maxn = 3e5 + 10, maxm = maxn << 1;
int e;
int to[maxm], nxt[maxm], head[maxn];
int sz[maxn], dep[maxn], p[maxn], End[maxn], totp;
struct Node{
	int x, y;
};
struct node{
	int x, y, z;
};
vector<Node> Poi[maxn];
vector<node> Q[maxn];
LL Sum[maxn], ans[maxn];
void add(int x, int y)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e;
}
int depmax = 0;
void dfs(int u, int fa)
{
	sz[u] = 1; dep[u] = dep[fa] + 1; p[u] = ++totp; 
	depmax = max(dep[u], depmax);
	for(int i = head[u]; i; i=nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dfs(v, u);
		sz[u] += sz[v];
	}
	End[u] = totp;
}
namespace BIT{
	LL c[maxn];
	int lowbit(int x) {return x & (-x);}
	void upt(int x, int v)
	{
/**/	while(x <= depmax)
		{
	 		c[x] += (LL)v; x += lowbit(x);
		}
	}
	LL que(int x){
		LL ret = 0;
		while(x)
		{
			ret += c[x]; x -= lowbit(x);
		}
		return ret;
	}
}
int main()
{
	freopen("laugh.in", "r", stdin);
	freopen("laugh.out", "w", stdout);
	int n, q;
	scanf("%d%d", &n, &q);
/**/for(int i = 1; i < n; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y); add(y, x);
	}
	dfs(1, 0);
	for(int i = 1; i <= n; ++i)
	{
/**/	Poi[p[i]].pb((Node){dep[i], sz[i] - 1});
	}
	for(int i = 1; i <= q; ++i)
	{
		int x, k;
		scanf("%d%d", &x, &k);
/**/	ans[i] += 1LL * min(dep[x] - 1, k) * (sz[x] - 1);
/**/	Q[p[x]].pb((node){min(depmax, dep[x] + 1), min(depmax, dep[x] + k), i});
		Q[End[x]].pb((node){min(depmax, dep[x] + 1), min(depmax, dep[x] + k), i});
	}
	for(int i = 1; i <= q; ++i) Sum[i] = -1;
	for(int i = 0; i <= totp; ++i)
	{
		for(int j = 0; j < Poi[i].size(); ++j)
		{
			BIT::upt(Poi[i][j].x, Poi[i][j].y);
		}
		for(int j = 0; j < Q[i].size(); ++j)
		{
			if(Sum[Q[i][j].z] == -1)
			{
				Sum[Q[i][j].z] =BIT::que(Q[i][j].y) - BIT::que(Q[i][j].x - 1);
			}
			else 
			{
				ans[Q[i][j].z] += BIT::que(Q[i][j].y) - BIT::que(Q[i][j].x - 1) - Sum[Q[i][j].z];
			}
		}
	}
	for(int i = 1; i <= q; ++i) printf("%lld\n", ans[i]);
	return 0;
}
/*
题意：
题目大意：给一棵树，每次询问给定a,k，求三元组（a,b,c）的数量满足：
1.a和b都是c的祖先
2.a和b在树上距离不超过k
3.a,b,c互不相同

思路：
这个三元组肯定是个链，分两种情况讨论：
1.a是深度中间那个点，这种情况很好搞，此时可能的b只能有min(dep[a] - 1, k)个，c只有sz[a] - 1个
2.a是深度最高那个点，这种情况下，可能的b是dep[a] < dep[b] <= dep[a] + k，c个数为sz[b] - 1
发现b满足dfs序在a的子树中，且b的深度满足一定范围，把sz[b] - 1作为权值，二维数点即可。

debug：
1.61行，<打成<=
2.70行，dep[i]打成dep[i] - 1
3.76行，longlong
4.77,78一定要和depmax取min，因为如果查询的范围超过了BIT的范围，会因为树的形态的问题，查出错的前缀和

*/
