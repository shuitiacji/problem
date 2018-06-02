#include<bits/stdc++.h>
using namespace std;
#define next Next
const int maxn=10010,maxm=200010;
int e,s,t,n,m;
struct dinic{
	int to[maxm],next[maxm],head[maxn],cur[maxn],cap[maxm],flow[maxm],d[maxn];
	int vis[maxn];
	void add(int x,int y,int z){
		to[++e]=y;
		next[e]=head[x];
		head[x]=e;
		cap[e]=z;
	}
	int bfs(){
		memset(vis,0,sizeof(vis));
		queue<int> q;
		q.push(s);
		d[s]=0;
/**/	vis[s]=1;
		while(!q.empty()){
			int u=q.front();q.pop();
	//		cout<<u<<endl;
			for(int i=head[u];i!=-1;i=next[i]){
				int v=to[i];
				if(!vis[v]&&flow[i]<cap[i]){
					vis[v]=1;
					d[v]=d[u]+1;
					q.push(v);
				}
			}
		}
/**/	return vis[t];
	}
	int dfs(int x,int a){
		if(x==t||a==0)return a;
		int FLOW=0,f;
/**/	for(int	&i=cur[x];i!=-1;i=next[i]){
			int v=to[i];
			if(d[x]+1==d[v]&&(f=dfs(v,min(a,cap[i]-flow[i])))>0){
				flow[i]+=f;
				flow[i^1]-=f;
				FLOW+=f;
				a-=f;
				if(a==0)break;
			}
		}
		return FLOW;
	}
	int Maxflow(){
		int FLOW=0;
		while(bfs()){
			for(int i=1;i<=n;++i)cur[i]=head[i];
			FLOW+=dfs(s,0x3f3f3f3f);
		}
		return FLOW;
	}
}T;
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&s,&t);
	e=-1;
/**/memset(T.next,-1,sizeof(T.next));
/**/memset(T.head,-1,sizeof(T.head));
	for(int i=1;i<=m;++i){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		T.add(x,y,z);
		T.add(y,x,0);
	}
	printf("%d\n",T.Maxflow());
	return 0;
}
/*
debug:
6.2
1.64,65,因为e从0开始，这两个东西要置成-1
2.20行写成0
3.33行忘记return
4.38行忘记&
*/
