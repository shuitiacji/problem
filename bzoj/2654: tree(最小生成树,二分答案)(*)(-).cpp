#include<bits/stdc++.h>
using namespace std;
const int maxn = 50010, maxm = 100100;
int f[maxn], n, m, Need;
struct node{
	int s, t, v, c;
	bool operator < (const node &B) const
	{
/**/	if(v == B.v) return c > B.c;
		return v < B.v;
	}
}E[maxm], e[maxm];
int find(int x)
{
	int r = x;
	while(r != f[r]) r = f[r];
	int i = x, j;
	while(i != r)
	{
		j = f[i];
		f[i] = r;
		i = j;
	}	
	return r;
}
int ans, cnt;
void uni(int x, int y, int v, int c)
{
	int fx = find(x), fy = find(y);
	if(fx != fy)
	{
		ans += v; cnt += c;
		f[fx] = fy;
	}
}
int ck(int x)
{
	for(int i = 1; i <= m; ++i)
	{
		E[i]=e[i]; 
		if(E[i].c == 1) E[i].v -= x;
	}
	sort(E + 1, E + m + 1);
	for(int i = 0; i < n; ++i) f[i] = i;
	ans = 0; cnt = 0;
	for(int i = 1; i <= m; ++i) uni(E[i].s, E[i].t, E[i].v, E[i].c);
	if(cnt >= Need) return 1;
	return 0;
}
int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d%d", &n, &m, &Need);
	for(int i = 1; i <= m; ++i)
	{
		scanf("%d%d%d%d", &e[i].s, &e[i].t, &e[i].v, &e[i].c), e[i].c ^= 1;
	}
	int l = -200, r = 200;
	int x;
	while(l <= r)
	{
		int mid = (l+r) >> 1;
		if(ck(mid))
		{
			r = mid - 1;
			x = ans + Need * mid;
		}
		else l = mid + 1;
	}	
	printf("%d\n", x);
	return 0;
}
/*
题意：
给你一个无向带权连通图，每条边是黑色或白色。让你求一棵最小权的恰好有need条白色边的生成树。
题目保证有解。

思路：
如果我们给所有白色边增加边权(减少也行)，那么所选的白色边一定越来越少（反之同理）。所以我们二分给白色边增加多少边权，跑kruskal，最后再将增加的边权减去即可。

但是你可能怀疑二分的正确性？即如果给白色边边权加上mid，则所选白色边>need，如果加上mid+1，则所选白色边<need。解决方法是，在排序的时候，我们将白色边放在相同长度的黑色边之前。这样，因为mid+1时白边<mid，所以一定有若干=mid的黑边。在mid时，我们多选的白边就可以被黑边替换掉。所以在最后统计答案的时候，只需要ans-=mid*need即可。
可以每次二分一个答案，搞一次sort，也可以一开始分别对黑边与白边排序，二分一个答案时将两个排序合并。

据说还可以将白边的权值变为-inf，跑一遍最小生成树，求出必须要选的黑边，同理求出必须要选的白边，将白边贪心加满Need个，再贪心去加黑边。

据说这种求在恰好条件下的最值，可以使用这种奇妙的二分

debug：
9行
*/
