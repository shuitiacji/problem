#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
using namespace std;
#define next Next
const int maxm=400005,maxn=100005;
int s,t;
struct Dinic{
	int e;
	int to[maxm],head[maxn],cur[maxn],cap[maxm],flow[maxm],d[maxn],vis[maxn],next[maxm];
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
		q.push(s);vis[s]=1;d[s]=0;
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=head[u];~i;i=next[i]){
				int v=to[i];
				if(!vis[v]&&cap[i]>flow[i]){
					q.push(v);
					vis[v]=1;
					d[v]=d[u]+1;
				}
			}
		}
		return vis[t];
	}
	int dfs(int x,int a){
		if(x==t||a==0)return a;
		int FLOW=0,f;
		for(int &i=cur[x];~i;i=next[i]){
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
		int ret=0;
		while(bfs()){
			for(int i=s;i<=t;++i)cur[i]=head[i];
			ret+=dfs(s,0x3f3f3f3f);
		}
		return ret;
	}
}T;
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int C;
	scanf("%d",&C);
	int cas=0;
	while(C--){
		++cas;
		T.e=-1;
		memset(T.flow,0,sizeof(T.flow));
		memset(T.head,-1,sizeof(T.head));
		int n,m;
		scanf("%d%d",&n,&m);
		s=0;t=n-1;
		for(int i=1;i<=m;++i){
			int x,y,z,d;
			scanf("%d%d%d%d",&x,&y,&z,&d);
			T.add(x,y,z);
			if(d==1)T.add(y,x,z);
		}
		T.gao();
		for(int i=0;i<=T.e;i+=2){
			if(T.cap[i]==T.flow[i])++T.cap[i];
			else T.cap[i]=0x3f3f3f3f;
		}
		printf("Case %d: %d\n",cas,T.gao());
	}
	return 0;
}
/*
题意：
求边数最小的最小割的边数。

思路：
1，在原图最小割不唯一的前提下，第一次求出的最小割的边数未必是最少的。在割边集的边权和相等的前提下，可能存在一个边数更少的最小割。
2，不管有多少个最小割，我们在原图跑一次最大流之后，残量网络里面满流的边一定是属于某个或多个最小割的，相应的没有满流的边一定不属于任何一个最小割。
3，这样问题就变成——在所有满流的边中破坏最少的边数来阻断0到N-1的路径，类似在最短路的边中破坏最少的边来阻断起点到终点的路径，只是多了对非最短路边（在本题中是非满流边）的处理。
4，将满流的边cap++，在跑一次最小割就可以达到上面的目的（遍历所有正向弧，若满流则更改边权为1，否则边权为无穷大）
*/
