#include<bits/stdc++.h>
using namespace std;
const int maxn=310,maxm=6000<<2;
int s,t;
struct Dinic{
	int e;
	int to[maxm],head[maxn],from[maxm],nxt[maxm],cap[maxm],flow[maxm],cur[maxn],vis[maxn],d[maxn];
	void add(int x,int y,int z){
		to[++e]=y;
		nxt[e]=head[x];
		head[x]=e;
		from[e]=x;
		cap[e]=z;
		to[++e]=x;
		nxt[e]=head[y];
		head[y]=e;
		from[e]=y;
		cap[e]=0;
	}
	int bfs(){
		memset(vis,0,sizeof(vis));
		queue<int> q;
		q.push(s);d[s]=0;vis[s]=1;
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=head[u];~i;i=nxt[i]){
				int v=to[i];
				if(cap[i]>flow[i]&&!vis[v]){
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
		for(int &i=cur[x];~i;i=nxt[i]){
			int v=to[i];
			if(d[v]==d[x]+1&&(f=dfs(v,min(cap[i]-flow[i],a)))>0){
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
int out[maxn],in[maxn];
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	T.e=-1;
	memset(T.head,-1,sizeof(T.head));
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		T.add(x,y+n,1);
	}
	s=0;t=2*n+1;
	for(int i=1;i<=n;++i)T.add(s,i,1);
	for(int i=n+1;i<=n*2;++i)T.add(i,t,1);
	int ans=n-T.gao();
	memset(out,-1,sizeof(out));
	for(int i=0;i<=T.e;i+=2){
		if(T.from[i]!=s&&T.to[i]!=t&&T.flow[i]==T.cap[i])in[T.to[i]-n]++,out[T.from[i]]=T.to[i]-n;
	}
	for(int i=1;i<=n;++i){
		if(!in[i]){
			printf("%d ",i);
			int u=i;
			while(~out[u]){
				u=out[u];
				printf("%d ",u);
			}
			cout<<endl;
		}
	}
	cout<<ans<<endl;
	return 0;
}
/*
题意：
最小路径覆盖。
思路：
最大流求最大匹配
*/
