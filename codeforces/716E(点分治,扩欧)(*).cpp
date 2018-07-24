#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace std;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
typedef long long LL;
const int maxn = 1e5 + 10, maxm = maxn << 1;
int mod, n, e;
int to[maxm], nxt[maxm], head[maxn], w[maxm], sz[maxn], vis[maxn];
LL fac[maxn];
__gnu_pbds::gp_hash_table<LL, int> hs;
void add(int x, int y, int z)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e; w[e] = z;
	to[++e] = x; nxt[e] = head[y]; head[y] = e; w[e] = z;
}
LL ans = 0;
int tmpsz, minsz, id;
void get_sz(int u, int fa)
{
	sz[u] = 1;
	for(int i = head[u]; i != -1; i = nxt[i])
	{
		int v = to[i];
		if(v == fa || vis[v]) continue;
		get_sz(v, u);
		sz[u] += sz[v];
	}
}
void get_root(int u, int fa)
{
	int maxsz = tmpsz - sz[u];
	for(int i = head[u]; i != -1; i = nxt[i])
	{
		int v = to[i];
		if(v == fa || vis[v]) continue;
		get_root(v, u);
		maxsz = max(maxsz, sz[v]);
	}
	if(maxsz < minsz) id = u, minsz = maxsz;
}
void ex_gcd(LL a, LL b, LL &x, LL &y)
{
	if(!b) x = 1, y = 0;
	else  ex_gcd(b, a % b, y, x), y -= a / b * x;
}
void dfs_calc(int u, int fa, LL d, int dep)
{
	LL x, y;
	ex_gcd(fac[dep], mod, x, y);
	x = (x % mod + mod) % mod;
	ans += hs[x * ((-d) % mod + mod) % mod];
	for(int i = head[u]; i != -1; i = nxt[i])
	{
		int v = to[i]; if(v == fa || vis[v]) continue;
		dfs_calc(v, u, (d * 10 % mod + w[i]) % mod, dep + 1);
	}
}
void dfs_set(int u, int fa, LL d, int dep)
{
	hs[d]++;
	for(int i = head[u]; i != -1; i = nxt[i])
	{
		int v = to[i]; if(v == fa || vis[v]) continue;
		dfs_set(v, u, (d + 1LL * fac[dep] * w[i] % mod) % mod, dep + 1);
	}
}
void gao(int u)
{
	get_sz(u, -1); tmpsz = sz[u]; minsz = 0x3f3f3f3f;
	get_root(u, -1); u = id; vis[u] = 1;
	hs.clear(); stack<pair<int, int> > s;
/**/hs[0] = 1;
	for(int i = head[u]; i != -1; i = nxt[i])
	{
		int v = to[i];
		if(vis[v]) continue;
		s.push(make_pair(v, w[i]));
		dfs_calc(v, u, w[i] % mod, 1); dfs_set(v, u, w[i] % mod, 1);
	}
/**/ans += hs[0] - 1;
	hs.clear();
	while(!s.empty())
	{
		dfs_calc(s.top().first, u, s.top().second % mod, 1); 
		dfs_set(s.top().first, u, s.top().second % mod, 1);
		s.pop();
	}
	for(int i = head[u]; i != -1; i = nxt[i])
	{
		int v = to[i]; 
		if(vis[v]) continue;
		gao(v);
	}
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	n = read(); mod = read();
	e = -1; memset(head, -1, sizeof(head));
	for(int i = 1; i < n; ++i)
	{
		int x = read(), y = read(), z = read();
		add(x, y, z);
	}
	if(mod == 1) { cout << 1LL * n * (n - 1) << endl; return 0; }
	fac[0] = 1;
	for(int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * 10 % mod;
/**/gao(0);
	cout << ans << endl;
	return 0;
}
/*
题意:
给你一棵树,每条边有一个权值[0,9],让你找出所有点对(u,v)使得u到v路径组成的数能被m整除(像字符串一样组成)

思路:
点分治即可.
每次分治时在dfs时记录下每个节点的d1(从该节点到根组成的数),d2(从根到该节点组成的数),并且我们用hash_table来存d1的个数,并且存d2和deep(该节点到根的距离即深度,这样我们可以通过d1*(10^deep)+d2来表示一个数,然后对d2,deep计算hash_table中有多少个d1使得d1*(10^deep)+d2==0, 用扩欧求出这个解,在hash中找一下即可

debug:
1.原先点分治时点对是无序的,但此题中(x,y)与(y,x)是不一样的,所以不能只算一遍所有子树v,正着一遍只能算出(x,y)这样的点对,还需要倒着搞一遍,算出所有的(y,x)
2.点分治时,一定要考虑到从当前点分重心下去的那条链,(不是只有端点在两颗不同的子树中的链要考虑,一个端点在点分重心上,一个在子树中的链也要考虑) (79, 87)
3.一定不要用费马小定理,只有p为质数才行,不是只要互质即可
*/
