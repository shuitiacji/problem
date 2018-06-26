#include<bits/stdc++.h>
using namespace std;
#define next Next
#define map Map
const int Maxn=100,maxn=10000,maxm=maxn<<2;
int A[Maxn][Maxn],B[Maxn][Maxn],C[Maxn],num[Maxn];
int s,t;
struct Dinic{
	int e,sum;
	int to[maxm],head[maxn],mak[maxn],vis[maxn],d[maxn],cap[maxm],flow[maxm],next[maxm],cur[maxm];
	void add(int x,int y,int z){
		to[++e]=y;
		next[e]=head[x];
		head[x]=e;
		cap[e]=z;
		to[++e]=x;
		next[e]=head[y];
		head[y]=e;
		cap[e]=0;
	}
	int bfs(){
		memset(vis,0,sizeof(vis));
		queue<int> q;
		vis[s]=0;d[s]=0;vis[s]=1;q.push(s);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=head[u];i!=-1;i=next[i]){
				int v=to[i];
				if(!vis[v]&&cap[i]>flow[i]){
					vis[v]=1;
					d[v]=d[u]+1;
					q.push(v);
				}
			}
		}
		return vis[t];
	}
	int dfs(int x,int a){
		if(x==t||a==0)return a;
		int FLOW=0,f;
		if(!mak[x])cur[x]=head[x],mak[x]++;
		for(int &i=cur[x];i!=-1;i=next[i]){
			int v=to[i];
			if(d[v]==d[x]+1&&(f=dfs(v,min(a,cap[i]-flow[i])))>0){
				FLOW+=f;
				flow[i]+=f;
				flow[i^1]-=f;
				a-=f;
				if(a==0)break;
			}
		}
		return FLOW;
	}
	int gao(){
		while(bfs()){
			memset(mak,0,sizeof(mak));
			sum+=dfs(s,0x3f3f3f3f);
		}
		return sum;
	}
}T;
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	T.e=-1;s=1;t=0;
	memset(T.head,-1,sizeof(T.head));
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;++i){
		int x,tmp1,tmp2;
		scanf("%d%d",&C[i],&x);
		scanf("%d",&tmp1);
		int tmp3=tmp1;
		for(int j=2;j<=x;++j){
			scanf("%d",&tmp2);
			A[i][j-1]=tmp1;B[i][j-1]=tmp2;
			if(j==x)A[i][0]=tmp2,B[i][0]=tmp3;
			tmp1=tmp2;
		}
		num[i]=x;
	}
	int now=0,tot=1,TOT=1;
	T.add(s,3,0x3f3f3f3f);
	T.add(2,t,0x3f3f3f3f);
	while(1){
		now++;
		tot=TOT+n+2;
		for(int i=0;i<=n+1;++i){
			++tot;++TOT;
			if(i==0)T.add(tot,t,0x3f3f3f3f);
			else if(i==1)T.add(s,tot,0x3f3f3f3f);
			else if(TOT!=1)T.add(TOT,tot,0x3f3f3f3f);
		}
		for(int i=1;i<=m;++i){
			int t=now%num[i];
			T.add((now-1)*(n+2)+1+A[i][t]+2,now*(n+2)+1+B[i][t]+2,C[i]);
		}
		if(T.gao()>=k){printf("%d\n",now);return 0;}
		if(now>=2000)break;
	}
	puts("0");
	return 0;
}
/*
题意
现有 n 个太空站位于地球与月球之间，且有 m 艘公共交通太空船在其间来回穿梭。每个太空站可容纳无限多的人，而每艘太空船 i 只可容纳 H[i]个人。每艘太空船将周期性地停靠一系列的太空站，例如：(1，3，4)表示该太空船将周期性地停靠太空站 134…。每一艘太空船从一个太空站驶往任一太空站耗时均为 1。人们只能在太空船停靠太空站(或月球、地球)时上、下船。
初始时所有人全在地球上，太空船全在初始站。试设计一个算法，找出让所有人尽快地全部转移到月球上的运输方案。

思路：
一开始想的是最小费用最大流，费用想的是时间，发现不好处理。
换一个思路，枚举答案，按时间建点，跑最大流看大不大于k。（无解可以用并查集预判，也可以自己定个数break）
*/
