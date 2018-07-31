#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 100;
typedef long long LL;
#define pb push_back
#define hash HASH
/**/int mu[maxn], vis[maxn], prime[maxn], cnt, f[maxn], sz[maxn], Vis[maxn];
int top;
LL Ans, ans[maxn];
pair<int, int> sta[maxn];
pair<int, int> mdf[maxn];
vector<int> vec[maxn];
struct edge
{
	int u, v, w;
}e[maxn];
int n, m, q;	
int P[maxn];
int hash[maxn], now[maxn];
void mathinit()
{
	mu[1] = 1;
	for(int i = 2; i <= maxn - 10; ++i)
	{
		if(!Vis[i]) mu[i] = -1, prime[++cnt] = i;
		for(int j = 1; j <= cnt && 1LL * prime[j] * i <= maxn - 10; ++j)
		{
			Vis[prime[j] * i] = 1;
			if(i % prime[j]) mu[i * prime[j]] = -mu[i];
			else {
				mu[i * prime[j]] = 0;
				break;
			}
		}
	}
}
int find(int x)
{
	while(x != f[x]) x = f[x];
	return x;
}
void undo(int x)
{
	while(top > x)
	{
		f[sta[top].second] = sta[top].second;
		Ans -= 1LL * sz[sta[top].first] * (sz[sta[top].first] - 1) / 2;
		sz[sta[top].first] -= sz[sta[top].second];
		Ans += 1LL * sz[sta[top].first] * (sz[sta[top].first] - 1) / 2;
		Ans += 1LL * sz[sta[top].second] * (sz[sta[top].second] - 1) / 2;
		--top;
	}	
}
void uni(int u, int v)
{
	int f1 = find(u), f2 = find(v);
	if(f1 == f2) return ;
	Ans -= 1LL * sz[f1] * (sz[f1] - 1) / 2;
	Ans -= 1LL * sz[f2] * (sz[f2] - 1) / 2;
	if(sz[f1] < sz[f2]) swap(f1, f2);
	sz[f1] += sz[f2];
	f[f2] = f1;
	sta[++top] = make_pair(f1, f2);
	Ans += 1LL * sz[f1] * (sz[f1] - 1) / 2;	
}
int main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	mathinit();
	scanf("%d", &n);
	for(int i = 1; i <= n - 1; ++i)
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
	scanf("%d", &q);
	for(int i = 1; i <= q; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		mdf[i] = make_pair(a, b);
		vis[a] = 1;
		hash[i] = a;
		for(int j = 1; j * j <= b; ++j)
		{
			if(b % j) continue;
			if(mu[j]) P[j] = 1;
			if(mu[b / j]) P[b / j] = 1;
		}
	}
	sort(hash + 1, hash + q + 1);
	int len = unique(hash + 1, hash + q + 1) - hash -1;
	for(int i = 1; i <= n - 1; ++i)
	{
		for(int j = 1; j * j <= e[i].w; ++j)
		{
			if(e[i].w % j) continue;
			if(mu[j])
			{
				if(!vis[i]) vec[j].pb(i);
				else P[j] = 1;
			}
			if(j * j != e[i].w && mu[e[i].w / j])
			{
				if(!vis[i]) vec[e[i].w / j].pb(i);
				else P[e[i].w / j] = 1;
			}
		}
	}
	for(int i = 1; i <= n; ++i) f[i] = i, sz[i] = 1;
	for(int d = 1; d <= 1000000; ++d)
	{
		if(!mu[d]) continue;
		int tmp = top;
		for(int i = 0; i < vec[d].size(); ++i)
			uni(e[vec[d][i]].u, e[vec[d][i]].v);   
		int TMP = top;
		for(int i = 0; i <= q; ++i)
		{
			if(P[d]){
				for(int j = 1; j <= len; ++j) now[hash[j]] = e[hash[j]].w;
				for(int j = 1; j <= i; ++j) now[mdf[j].first] = mdf[j].second;
				for(int j = 1; j <= len; ++j)
				{
/**/				if(!(now[hash[j]] % d))
						uni(e[hash[j]].u, e[hash[j]].v);
				}
			}
			ans[i] += 1LL * mu[d] * Ans;
			undo(TMP);
		}
		undo(tmp);
	}
	for(int i = 0; i <= q; ++i) printf("%lld\n", ans[i]);
	return 0;
}
/*
题意：
给定一棵 n 个点的树,每条边有个正整数边权。有 q 次修改操作,每次会修
改一条边的边权。
在所有修改前以及每次修改后,你需要求出有多少个无序点对满足它们之间
的最短路径上所有边权的最大公约数=1。

思路：
考虑莫比乌斯反演，按之前在序列上的套路：
设F[n]表示gcd为n的倍数的点对，f[n]为gcd为n的点对
f[n] = sigma(F[i] * mu[i / n]) (n | i)
ans = f[1]
但不同于序列上的是，这里的F[n]并不是很好求
考虑若一条路径上的所有边若都是d的倍数，则肯定可以为F[d]作出贡献
则枚举d(mu[d] != 0)，把是d倍数的边加到并查集中，并计算答案。

对于修改操作，由于修改较小，可以对于修改涉及的边,我们一开始不将它们加入并查集。然后我们枚举 q+1 个时刻,再将这些边加入,统计答案,再删去即可。

debug:
1.123行，!要打在括号外
2.7行，vis重名
*/
