#include<bits/stdc++.h>
using namespace std;
#define pb push_back
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
const int maxn = 1e5 + 10, maxm = maxn << 1;
int to[maxm], nxt[maxm], head[maxn], w[maxm], dep[maxn], maxdep, ansdep, tmpl, tmpr, maxson[maxn];
int n, k;
int e;
struct node
{
	int x, y;
};	
vector<int> a;
void add(int x, int y, int z)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e; w[e] = z;
	to[++e] = x; nxt[e] = head[y]; head[y] = e; w[e] = z;
}
void dfs1(int u, int fa)
{
	if(dep[u] > maxdep)
		maxdep = dep[u], ansdep = u;
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		dep[v] = dep[u] + w[i];
		dfs1(v, u);	
	}
}
int dfs2(int u, int fa)
{
	if(u == tmpr)
	{
		a.pb(u); return 1;	
	}
	int FG = 0;
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(v == fa) continue;
		int fg = dfs2(v, u);
		FG = max(FG, fg);
		if(!fg){
			maxson[u] = max(maxson[u], maxson[v] + w[i]);
		}
	}
	if(FG) { a.pb(u); return 1;}
/**/return 0;
}
deque<node> q;
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	n = read(); k = read();
	for(int i = 1; i < n; ++i)
	{
		int x = read(), y = read(), z = read();
		add(x, y, z);
	}
	dfs1(1, 0);
	tmpl = ansdep; ansdep = 0; maxdep = 0; dep[tmpl] = 0;
	dfs1(tmpl, 0); 
	tmpr = ansdep;
	dfs2(tmpl, 0);
	int ans = 0x3f3f3f3f;
	int len = dep[tmpr];
/**/k = min(k, (int)a.size());
	for(int i = 0, j = 0; i + k <= a.size(); ++i)
	{
		while(j < i + k)
		{
			while(!q.empty() && q.back().x < maxson[a[j]]) q.pop_back();
			q.pb((node){maxson[a[j]], j}); ++j;
		}
		while(q.front().y < i) q.pop_front();
		ans = min(ans, max(max(len - dep[a[i]], maxson[tmpl] + dep[a[i + k - 1]]), q.front().x));
	}
	cout << ans << endl;
	return 0;
}
/*
题意：
给你一棵树，找出一条长度不超过k的链，使得其他所有点到这条链的最短距离的最大值最小。

思路：
这种什么跟树上距离最大最小有关的，往树的直径上想。
先求出树的直径，可以利用一个性质，一个点的最远点一定是直径的两端点之一，先随便找个点dfs到最远点，再从找到的这个直径的一端，再dfs一遍到最远点，即是另一个端点。
然后我们发现，题目要求的这条链一定在树的直径上，证明：至少有1个点会在直径上，接下来选1个点，相邻的直径点还是其他分支的点？那么必定是相邻的直径点，因为如果是选分支点，必定是这个分支中存在一个最深点到当前这个直径点的距离比它左边或右边的一截直径要大（因为选了这个分支点后，为保证这是条链，那么必定无法同时往直径上左扩张或右扩张，就会剩下半截直径），那么这个分支便可以构成一个更优的直径，矛盾。
所以只要在直径上选最优的k个连续的点，这个显然是个滑动窗口优先队列，最优化直径两个端点到k个连续区间的两个端点，还有以k-2个点为根节点的最大距离。

debug:
1.55行
2.75行
3.66行不能写成add(read(), read(), read()), 因为函数从后往前处理，会把边读反
*/
