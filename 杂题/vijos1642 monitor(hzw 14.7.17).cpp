#include<bits/stdc++.h>
using namespace std;
#define next Next
const int maxn=1010,maxm=maxn;
int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int e,n,m;
int to[maxm],next[maxm],head[maxn],dp[maxn][maxn],a[maxn],sz[maxn];
void add(int x,int y){
	to[++e]=y;
	next[e]=head[x];
	head[x]=e;
}
void dfs(int u){
	sz[u]=1;
	dp[u][1]=a[u];
	for(int i=head[u];i;i=next[i]){
		int v=to[i];
		dfs(v);
/**/	for(int j=sz[u];j>=1;--j){
			for(int k=sz[v];k>=1;--k){
				dp[u][j+k]=max(dp[u][j+k],dp[u][j]+dp[v][k]);
			}
		}
		sz[u]+=sz[v];
	}
}
int main(){
	freopen("monitor.in","r",stdin);
	freopen("monitor.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;++i){
		a[i]=read();int X=read();
	//	cout<<i<<' '<<a[i]<<endl;
		for(int j=1;j<=X;++j){
			int x=read();
			add(i,x);//add(x,i);
		}
	}
/**/memset(dp,-0x3f,sizeof(dp));
	dfs(1);
	int ans=0;
/**/for(int i=0;i<=m;++i)ans=max(ans,dp[1][i]);
	cout<<ans<<endl;
	return 0;
}
/*
题意:福州时代中学2009届十班同学毕业了，于是班长PRT开始筹办毕业晚会，但是由于条件有限，可能每个同学不能都去，但每个人都有一个权值，PRT希望来的同学们的权值总和最大。

十班有一个周密的电话通知网络，它其实就是一棵树，根结点为班长PRT，由她来负责通知她的下线（也就是儿子节点），下线们继续通知自己的下线（不一定每个下线都要通知），任何人都可以不去：”
为了使权值总和最大，班长想安排一下人，但是人数很多，人脑是难以应付的，所以她找到十八居士，让他编程用电脑解决。

思路：树形dp，泛化背包

debug:
1.24行，dp的顺序要倒序
2.44行，因为有负的权值不能只置成0，还要置成负无穷
3.47行，只是至多要m个人，可以<=m
*/
