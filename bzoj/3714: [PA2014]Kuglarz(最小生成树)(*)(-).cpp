#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 2010, maxm = maxn * maxn >> 1;
struct node
{
	int x, y, v;
	bool operator < (const node &b) const
	{
		return v < b.v;
	}
}edge[maxm];
LL ans;
int f[maxn];
int find(int x)
{
	int r = x;
	while(f[r] != r) r = f[r];
	int i = x, j;
	while(i != r){
		j = f[i];
		f[i] = r;
		i = j;
	}
	return r;
}
void uni(int x, int y, int z)
{
	int fx = find(x), fy = find(y);
	if(fx != fy)
	{
		ans += z;
		f[fx] = fy;
	}
}
int e;
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		for(int j = i; j <= n; ++j)
		{
			int x;
			scanf("%d", &x);
			edge[++e] = (node){i - 1, j, x};
		}
	sort(edge + 1, edge + e + 1);	
	for(int i = 0; i <= n; ++i) f[i] = i;
	for(int i = 1; i <= e; ++i) uni(edge[i].x, edge[i].y, edge[i].v);
	cout << ans << endl;
	return 0;
}
/*
题意：
魔术师的桌子上有n个杯子排成一行，编号为1,2,…,n，其中某些杯子底下藏有一个小球，如果你准确地猜出是哪些杯子，你就可以获得奖品。花费c_ij元，魔术师就会告诉你杯子i,i+1,…,j底下藏有球的总数的奇偶性。
采取最优的询问策略，你至少需要花费多少元，才能保证猜出哪些杯子底下藏着球？

思路：
观察性质
要求出i是否有球，必须要知道[1,i]和[1,(i−1)]的奇偶性
而对于知道[1,l-1],[l,r]，就能推出[1,r]
把询问看成连[l-1,r]的边，求最后联通的最小花费
最小生成树
*/
