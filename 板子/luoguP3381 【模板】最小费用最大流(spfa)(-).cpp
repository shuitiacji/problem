#include<bits/stdc++.h>
using namespace std;
const int maxn=5010,maxm=101000;
#define next Next
int e,s,t,n,m;
int FLOW,COST;
struct cost_flow_spfa{
	int to[maxm],head[maxn],next[maxm],cap[maxm],cost[maxm],from[maxm],flow[maxm];
	int a[maxn],inq[maxn],dis[maxn],p[maxn];
	void add(int x,int y,int c,int C){
		to[++e]=y;
		next[e]=head[x];
		head[x]=e;
		cap[e]=c;
		cost[e]=C;
		from[e]=x;
	}
	int spfa(){
		memset(dis,0x3f,sizeof(dis));
		memset(inq,0,sizeof(inq));
		dis[s]=0;inq[s]=1;p[s]=0;a[s]=0x3f3f3f3f;
		queue<int> q;
		q.push(s);
		while(!q.empty()){
			int u=q.front();q.pop();
			inq[u]=0;
			for(int i=head[u];i!=-1;i=next[i]){
				int v=to[i];
				if(flow[i]<cap[i]&&dis[v]>dis[u]+cost[i]){
					dis[v]=dis[u]+cost[i];
					p[v]=i;
					a[v]=min(a[u],cap[i]-flow[i]);
					if(!inq[v])q.push(v),inq[v]=1;
				}
			}
		}
		if(dis[t]==0x3f3f3f3f)return 0;
		FLOW+=a[t];
/**/	COST+=dis[t]*a[t];
		int u=t;
		while(u!=s){
			flow[p[u]]+=a[t];
			flow[p[u]^1]-=a[t];
			u=from[p[u]];
		}
		return 1;
	}
}T;
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	e=-1;
	memset(T.head,-1,sizeof(T.head));
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1;i<=m;++i){
		int x,y,z,f;
		scanf("%d%d%d%d",&x,&y,&z,&f);
		T.add(x,y,z,f);T.add(y,x,0,-f);
	}
	while(T.spfa());
	printf("%d %d\n",FLOW,COST);
	return 0;
}
/*
debug:
6.2
1.39行+=写成=
*/
