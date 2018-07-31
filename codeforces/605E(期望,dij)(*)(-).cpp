#include<bits/stdc++.h>
using namespace std;
typedef double db;
db p[1010][1010],d[1010],a[1010],b[1010];
int vis[1010];
int main() {
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j) {
			scanf("%lf", &p[i][j]);
			p[i][j] /= 100.;
		}
	for(int i=1;i<=n;++i) d[i]=1e30,  a[i]=1,  b[i]=1;
	d[n]=0;
	for(int t=1;t<=n;++t) {
		db tmp=1e28;int id;
		for(int i=1;i<=n;++i) {
			if(vis[i]==0&&tmp>d[i]) {
				tmp=d[i];id=i;
			}
		}
		vis[id]=1;
		for(int i=1;i<=n;++i) {
			if(vis[i]==0&&p[i][id]>0) {
				b[i]+=a[i]*p[i][id]*d[id];
				a[i]*=1.-p[i][id];
				d[i]=b[i]/(1.-a[i]);
			}
		}
	}
	printf("%.15lf\n",d[1]);
	return 0;
}
/*
题意：
有n个点，每天i号点到j号点的有向道路有pij的概率开放。每天可以走一条开放的道路或者留在原地，求从1号点走到n号点的最优期望时间。

思路：
因为是要求最优的期望时间，所以如果决策不能使时间更优的话就还不如留在原地。
设di表示i点到n点的最优期望时间，xi表示所有点d值第i大的点。
所以dxi只能转移到dxi-1,dxi-2,...
问题是xi如何求
这里显然应该从终点考虑了，冥冥之中得到这样一个顺序，我用终点去更新，get一个离终点最近（期望最小）的点，然后这个点会纳入其他和它相连没有它的优的点的考虑范围，然后拿这个点更新一下，get下一个优的点，你们想到了啥，dijsktra！没错就是这个玩意！
同样由dij的证明，我们可以显然的发现这个算法的正确性。
*/

