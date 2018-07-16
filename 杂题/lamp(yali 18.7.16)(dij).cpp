#include<bits/stdc++.h>
using namespace std;
const int maxn = 251001 << 2, maxm = maxn << 2;
int n, m;
int e;
int to[maxm], nxt[maxm], head[maxn], w[maxm], d[maxn];
char a[1000];
int mp(int i, int j)
{
	return (i - 1) * (m + 1) + j;
}
void add(int x, int y, int z)
{
	to[++e] = y; nxt[e] = head[x]; head[x] = e; w[e] = z;
	to[++e] = x; nxt[e] = head[y]; head[y] = e; w[e] = z;
}
struct node
{
	int x, y;
	bool operator > (const node &b) const 
	{
		return y > b.y;
	}
};
void dij()
{
	priority_queue<node, vector<node>, greater<node> > q;
	memset(d, 0x3f, sizeof(d));
	q.push((node){1, 0}); d[1] = 0;
	while(!q.empty())
	{
		int u = q.top().x; q.pop();
		for(int i = head[u]; i; i = nxt[i])
		{
			int v = to[i];
			if(d[v] > d[u] + w[i])
			{
				d[v] = d[u] + w[i];
				q.push((node){v, d[v]});
			}
		}
	}
}
int main()
{
	freopen("lamp.in", "r", stdin);
	freopen("lamp.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%s", a);
		for(int j = 0; j < m; ++j)
		{
			if(a[j] != '/')
				add(mp(i, j + 1), mp(i + 1 ,j + 2), 0), add(mp(i, j + 2), mp(i + 1, j + 1) ,1);
			else
				add(mp(i, j + 1), mp(i + 1 ,j + 2), 1), add(mp(i, j + 2), mp(i + 1, j + 1) ,0);
		}
	}
	dij();
	if(d[(n + 1) * (m + 1)] == 0x3f3f3f3f) puts("NO SOLUTION");
	else cout << d[(n + 1) * (m + 1)] << endl;
	return 0;
}
/*
题意：
luoguP2243

思路：
转化一下，若为\，则左上角连一条长度为0的边到右下角，且右上角连一条长度为1的边到左下角，反之亦然
建图跑dij即可
*/
