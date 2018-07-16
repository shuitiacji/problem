#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 10000;
const int N = 1e7 + 10;
#define odd xzakioi
#define even hkakioi
int n;
int vis[N], prime[N]; 
int a[maxn];
const int maxm = maxn << 1;
vector<int> odd, even;
int vec[maxn];
void mathinit()
{
	int CNT = 0;
	vis[1] = 1;
	for(int i = 2; i <= N - 10; ++i)
	{
		if(!vis[i]) prime[++CNT] = i;
		for(int j = 1; j <= CNT && 1LL * prime[j] * i <= N - 10; ++j)
		{
			vis[prime[j] * i] = 1;
			if(i % prime[j] == 0) break;
		}
	}
}
int s, t;
namespace dinic
{
	int e, head[maxn], to[maxm], flow[maxm], cap[maxm], nxt[maxm], d[maxn], vis[maxn], cur[maxn];
	void add(int x, int y, int z)
	{
		to[++e] = y; nxt[e] = head[x]; head[x] = e; cap[e] = z;
		to[++e] = x; nxt[e] = head[y]; head[y] = e; cap[e] = 0;
	}
	int bfs()
	{
		memset(vis, 0, sizeof(vis));
		queue<int> q;
		q.push(s); d[s] = 0;
/**/	vis[s] = 1;
		while(!q.empty())
		{
			int u = q.front(); q.pop();
			for(int i = head[u]; i != -1; i = nxt[i])
			{
				int v = to[i];
				if(!vis[v] && cap[i] > flow[i])
				{
					d[v] = d[u] + 1;
					vis[v] = 1;
					q.push(v);
				}
			}
		}
		if(!vis[t]) return 0;
		return 1;
	}
	int dfs(int x, int a)
	{
		if(x == t || a == 0) return a;
		int FLOW = 0, f;
		for(int &i = cur[x]; i != -1; i = nxt[i])
		{
			int v = to[i];
			if(d[v] == d[x] + 1 && (f = dfs(v, min(cap[i] - flow[i], a))) > 0)
			{
				flow[i] += f; flow[i ^ 1] -= f;
				FLOW += f; a -= f;
				if(a == 0) break;
			}
		}
		return FLOW;
	}
	int gao()
	{
		int ret = 0;
		while(bfs())
		{
			for(int i = 1; i <= t; ++i) cur[i] = head[i];
			ret += dfs(s, 0x3f3f3f3f);
		}
		return ret;
	}
}
int main()
{
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
	dinic::e = -1;
	memset(dinic::head, -1, sizeof(dinic::head));
	memset(dinic::nxt, -1, sizeof(dinic::nxt));
	mathinit();
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	n = unique(a + 1, a + n + 1) - a - 1;
	int beg = a[1]; 
	int cnt = 0;
	for(int i = 2; i < n; ++i)
	{
		if(a[i] - a[i - 1] > 1)
			vec[++cnt] = beg, vec[++cnt] = a[i - 1] + 1, beg = a[i];
	}
	if(a[n] - a[n - 1] > 1 && n > 1) vec[++cnt] = beg, vec[++cnt] = a[n - 1] + 1, vec[++cnt] = a[n], vec[++cnt] = a[n] + 1;
	else vec[++cnt] = beg, vec[++cnt] = a[n] + 1;
	for(int i = 1; i <= cnt; ++i)
	{
		if(vec[i] & 1) odd.push_back(vec[i]);
		else even.push_back(vec[i]);
	}
	s = cnt + 1; t = cnt + 2;
	int tmp = odd.size();
	for(int i = 0; i < odd.size(); ++i)
	{
		dinic::add(s, i + 1, 1);
		for(int j = 0; j < even.size(); ++j)
			if(!vis[abs(odd[i] - even[j])]) 
				dinic::add(i + 1, j + tmp + 1, 1);
	}
	for(int j = 0; j < even.size(); ++j) dinic::add(j + tmp + 1, t, 1);
	tmp = dinic::gao();	
	int tmp1 = (int)odd.size() - tmp, tmp2 = (int)even.size() - tmp;
	int ans = 0;
	ans += tmp;
	ans += tmp1 / 2 * 2; 
	ans += tmp2 / 2 * 2;
	if(tmp1 & 1) ans += 3;
	cout << ans << endl;
	return 0;
}
/*
题意：
给你一个自然数列，把其中一些数的状态设为1,其他为零，有一种操作可以选择一段连续的长度为奇质数的数列反转状态，求最少几次操作可以把所有数变为0

思路：
这种01串反转一段区间，差分后，对所有的1两两匹配消除。
考虑任意两个数 i, j 之间需要的操作数.
1当 |i − j| 为奇质数时, 需要一次操作.
2当 |i − j| 为偶数时, 需要两次操作. (哥德巴赫猜想)
3当 |i − j| 为奇非质数时, 需要三次操作. (分解为偶数减奇质数之差)

贪心的尽量选1,实在不行选2,再不行就3。
考虑实现，因为这个与奇偶相关，又是匹配，容易想到把所有差分中的1按位置的奇偶分成二分图，并且n^2暴力建满足1情况的边，先跑一遍二分图匹配。
接下来是2情况，除去已经匹配的，分别在两个部分，同一个部分内两两匹配
最后有可能两边都剩下了一个，再按3情况匹配。

debug：
1.42行
*/
