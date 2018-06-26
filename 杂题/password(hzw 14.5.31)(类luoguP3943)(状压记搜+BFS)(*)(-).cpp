#include<bits/stdc++.h>
using namespace std;
const int maxn=10010,maxm=2000005;
int vis[maxn],dis[maxn],d[25][25],f[maxm],a[maxn],id[maxn],vs[maxm],sz[maxn];
int n,m,k,cnt;
void bfs(int x){
	memset(vis,0,sizeof(vis));
	vis[x]=1;dis[x]=0;
	queue<int> q;
	q.push(x);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=1;i<=m;++i){
			int t=sz[i];
			if(u+t<=n&&(!vis[u+t])){
				vis[u+t]=1;
				dis[u+t]=dis[u]+1;
				q.push(u+t);
			}
			if(u-t>0&&(!vis[u-t])){
				vis[u-t]=1;
				dis[u-t]=dis[u]+1;
				q.push(u-t);
			}
		}
	}
	for(int i=1;i<=n;++i){
		if(!id[i])continue;
		if(!vis[i])d[id[x]][id[i]]=0x3f3f3f3f;
		else d[id[x]][id[i]]=dis[i];
	}
}
int dfs(int s){
	if(s==0)return 0;
	if(vs[s])return f[s];
	vs[s]=1;f[s]=0x3f3f3f3f;
	int u=0;
	for(int i=1;i<=cnt;++i){
		if((1<<(i-1))&s){
			if(!u)u=i;
			else {
				if(d[u][i]!=0x3f3f3f3f){
					f[s]=min(f[s],dfs(s^(1<<(u-1))^(1<<(i-1)))+d[u][i]);
				}
			}
		}
	}
	return f[s];
}
int main(){
	freopen("password.in","r",stdin);
	freopen("password.out","w",stdout);
	scanf("%d%d%d",&n,&k,&m);
	for(int i=1;i<=k;++i){
		int x;
		scanf("%d",&x);
		a[x]=1;
	}
	for(int i=1;i<=m;++i)scanf("%d",&sz[i]);
	for(int i=n+1;i;--i)a[i]^=a[i-1];
	n++;
	cnt=0;
	for(int i=1;i<=n;++i){
		if(a[i])id[i]=++cnt;
	}
	for(int i=1;i<=n;++i){
		if(a[i])bfs(i);
	}
	dfs((1<<cnt)-1);
	if(f[(1<<cnt)-1]!=0x3f3f3f3f)printf("%d\n",f[(1<<cnt)-1]);
	else puts("-1");
	return 0;
}
/*
题意:hzwer 有一把密码锁,由 N 个开关组成。一开始的时候,所有开关都是关上的。当且仅
当开关 x1,x2,x3,...xk 为开,其他开关为关时,密码锁才会打开。
他可以进行 M 种的操作,每种操作有一个 size[i],表示,假如他选择了第 i 种的操作
的话,他可以任意选择连续的 size[i]个格子,把它们全部取反。(注意,由于黄金大神非常
的神,所以操作次数可以无限>_<)
你的任务很简单,求出最少需要多少步才能打开密码锁,或者如果无解的话,请输出-1。
思路：
注意到题目中的是区间修改，把沿途的位置取反，这个可以看做是在模2意义下，给区间的加一操作。在我们通常的思路中，对于区间的操作，原本是要修改区间长度个的位置的情况，我们都可以通过考虑它的差分序列，使得要修改的位置个数变成2个，我们要求最少的修改，使得原序列变成全0。

所以对原序列进行差分，那么每次修改就是要你对i号位置和i+size[]模2意义下的加1。

差分后的序列中，数值为1的个数是不会超过2k个，即不会超过20个。

考虑每次对i和i+x改动的过程，如果原序列中，i号位置和i+x号位置都是0的话，我们这么改，没有任何必要。所以任意时刻，数值为1的位置个数是不会增加的，那么我们可以把每一个的1看成一个的石子，那么每次我们可以把石子往某个方向移动size[]步，如果移动之后的位置存在石子的话，就对对碰，消掉了。

因为是对对碰，石子之间的关系肯定是一个匹配的关系，我们不妨求出Dist[i][j]表示，石子i要走到石子j的位置，至少需要移动多少步，那么我们可以枚举每一个石子，然后进行一遍的bfs即可，这一部分的复杂度是O(2kmn)。

现在问题转化为有一个大小不超过20的完全图，我们想要求它的最小权最大匹配。


100%的做法因为完全图的个数非常小，直接状压DP即可。对于一个状态，我们考虑其下标最小的那个位置和谁匹配了，就能递归成子问题了，复杂度是O(2kmn+2k*2^(2k))。
*/
