#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1010,maxm=maxn<<3;
int a[maxn],f[maxn],s,t;
struct Dinic{
	int e;
	int to[maxm],head[maxn],cur[maxn],nxt[maxm],cap[maxm],vis[maxn],d[maxn],flow[maxm];
	void add(int x,int y,int z){
		to[++e]=y;
		nxt[e]=head[x];
		head[x]=e;
		cap[e]=z;
		to[++e]=x;
		nxt[e]=head[y];
		head[y]=e;
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
		if(a==0||x==t)return a;
		int f,FLOW=0;
		for(int &i=cur[x];~i;i=nxt[i]){
			int v=to[i];
			if(d[v]==d[x]+1&&(f=dfs(v,min(a,cap[i]-flow[i])))>0){
				FLOW+=f;
				a-=f;
				flow[i]+=f;
				flow[i^1]-=f;
			}
		}
		return FLOW;
	}
	int gao(){
		LL ret=0;
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
	memset(T.head,-1,sizeof(T.head));
	T.e=-1;
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	f[1]=1;
	int ans=0;
	for(int i=2;i<=n;++i){
/**/	f[i]=1;
		for(int j=1;j<i;++j){
			if(a[i]>=a[j])
				f[i]=max(f[j]+1,f[i]);
		}
		ans=max(f[i],ans);
	}
	printf("%d\n",ans);
	s=0;t=2*n+1;
	for(int i=1;i<=n;++i)if(f[i]==1)T.add(s,i,1);
	for(int i=1;i<=n;++i)if(f[i]==ans)T.add(i+n,t,1);
	for(int i=2;i<=n;++i){
		for(int j=1;j<i;++j){
			if(a[i]>=a[j]&&f[i]==f[j]+1)T.add(j+n,i,1);
		}
	}
	for(int i=1;i<=n;++i)T.add(i,i+n,1);
	int tmp=T.gao();
	cout<<tmp<<endl;
	T.add(s,1,0x3f3f3f3f);
	T.add(1,n+1,0x3f3f3f3f);
	if(f[n]==ans)T.add(n+n,t,0x3f3f3f3f),T.add(n,n+n,0x3f3f3f3f);
	cout<<tmp+T.gao()<<endl;
	return 0;
}
/*
题意：
1.求最长不下降子序列的长度s。
2.求这样的长度为s的序列有多少（两个序列不能共用一个元素）
3.若可以共用第一个，和第n个，又有多少

思路:
先dp求以i结尾最大长度f[i]
分层图思想，以f[i]分层。
不能共用就拆点连容量为1的边。

debug:
70行
*/
