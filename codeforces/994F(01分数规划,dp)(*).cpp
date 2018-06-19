#include<bits/stdc++.h>
using namespace std;
#define min Min
typedef double db;
typedef long long LL;
struct node{
	db x,y;
	bool operator < (const node &b) {
		return x>b.x;
	}
}a[60];
db mid;
db d[60][60][60];
int vis[60][60][60];
int n;
db Min(db X,db Y){return X<Y?X:Y;}
db dp(int x,int take,int now){
	if(x>n)return 0;
	if(vis[x][take][now])return d[x][take][now];
	vis[x][take][now]=1;
	db tmp=1e18;
	if(x<n&&a[x].x==a[x+1].x){
		if(take>0)tmp=min(tmp,dp(x+1,take-1,now));
		tmp=min(tmp,dp(x+1,take,now+1)+a[x].x-mid*a[x].y);
	}
	else {
		if(take>0)tmp=min(tmp,dp(x+1,take+now-1,0));
		tmp=min(tmp,dp(x+1,take+now+1,0)+a[x].x-mid*a[x].y);
	}
	return d[x][take][now]=tmp;
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%lf",&a[i].x);
	for(int i=1;i<=n;++i)scanf("%lf",&a[i].y);
	sort(a+1,a+n+1);
	db l=0,r=1e10;
	for(int i=1;i<=100;++i){
		mid=(l+r)/2.;
		memset(vis,0,sizeof(vis));
		if(dp(1,0,0)>=0)l=mid;
		else r=mid;
	}
/**/printf("%.0lf",(ceil)(l*1000));
	return 0;
}	
/*
题意：
给n个任务，每个任务有x值与y值，同时有无限台机器，机器可以处理两个任务，其中第二个任务x值必须小于第一个x值，代价是所有机器上的第一个任务x值之和除以y值之和，求最小代价。

思路：
求分数最小，想到01分数规划。
二分求一下即可。
先排序满足x2<x1的约束，但因为相等的数存在，还要多一位状态记一下与当前x值重复的，dp(i,j,k)表示当前放到i（从后往前放），在i之前有j个x值比i大的，且没有第2个任务的机器数目（就是可以将i作为第二个任务的数目），在i之前有k个x值与i相等的（之所以记这个，是因为只有严格小于才能成为第二任务，等于不行，要先缓缓），在这种情况下(答案为r)求出的分数规划的f值(f(r)=∑valuei⋅Xi−r∗⋅∑costi⋅Xi)(Xi={0,1},01表示是否属于第一个任务)(value=x,cost=y)

debug:
46行不能用cout输出实数（会转成科学计数法）
*/

