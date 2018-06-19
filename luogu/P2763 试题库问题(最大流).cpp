#include<bits/stdc++.h>
using namespace std;
#define next Next
const int maxn=10000,maxm=maxn<<2;
int s,t;
struct Dinic{
	int e;
	int head[maxn],to[maxm],cur[maxn],cap[maxm],next[maxm],flow[maxm],vis[maxn],d[maxn];
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
		vis[s]=1;d[s]=0;queue<int> q;q.push(s);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=head[u];~i;i=next[i]){
				int v=to[i];
				if(!vis[v]&&cap[i]>flow[i]){
					vis[v]=1;d[v]=d[u]+1;q.push(v);
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
/**/		if(d[v]==d[x]+1&&(f=dfs(v,min(a,cap[i]-flow[i])))>0){
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
	T.e=-1;
	memset(T.head,-1,sizeof(T.head));
	int k,n;
	scanf("%d%d",&k,&n);
	s=0;t=k+n+1;int sum=0;
	for(int i=1;i<=k;++i){
		int x;
		scanf("%d",&x);
		sum+=x;
		T.add(i,t,x);
	}
	for(int i=1;i<=n;++i){
		T.add(s,i+k,1);
		int x;
		scanf("%d",&x);
		for(int j=1;j<=x;++j){
			int y;;
			scanf("%d",&y);
			T.add(i+k,y,1);
		}
	}
	if(T.gao()==sum){
		for(int i=1;i<=k;++i){
			printf("%d:",i);
			for(int j=T.head[i];~j;j=T.next[j]){
				int v=T.to[j];
				if(v!=t&&T.cap[j^1]==T.flow[j^1]){
					printf(" %d",v-k);
				}
			}
			printf("\n");
		}
	}
	else puts("No Solution!");
	return 0;
}
/*
题意：假设一个试题库中有n道试题。每道试题都标明了所属类别。同一道题可能有多个类别属性。现要从题库中抽取m 道题组成试卷。并要求试卷包含指定类型的试题。一个试题虽然有多种类别但只算一个。试设计一个满足要求的组卷算法。

思路：
二分图匹配，跑一下最大流即可。

debug：
38行==写成=
*/
