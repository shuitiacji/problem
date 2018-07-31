#include<bits/stdc++.h>
using namespace std;
const int maxn=20010,maxm=maxn<<1;
int e;
int sum[4],to[maxm],head[maxn],w[maxm],nxt[maxm],sz[maxn],vis[maxn];
int n;
void add(int x,int y,int z){ 
	to[++e]=y;nxt[e]=head[x];head[x]=e;w[e]=z;
	to[++e]=x;nxt[e]=head[y];head[y]=e;w[e]=z;
}
void getsz(int u,int fa){
	sz[u]=1;
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa||vis[v])continue;
		getsz(v,u);
		sz[u]+=sz[v];
	}
}
int tmpsz,minsz,id;
void getroot(int u,int fa){
	int maxsz=tmpsz-sz[u];
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa||vis[v])continue;
		getroot(v,u);
		maxsz=max(sz[v],maxsz);
	}
	if(maxsz<minsz){
		minsz=maxsz;id=u;
	}
}
int ans;
void cal_dfs(int u,int fa,int dis){
	ans+=sum[(3-dis%3)%3];
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(vis[v]==1||v==fa)continue;
		cal_dfs(v,u,dis+w[i]);
	}
}
void set_dfs(int u,int fa,int dis){
	sum[dis%3]++;
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(vis[v]==1||v==fa)continue;
		set_dfs(v,u,dis+w[i]);
	}
}
void div(int u){
	getsz(u,0);tmpsz=sz[u];
	minsz=0x3f3f3f3f;
	getroot(u,0);
	u=id;
	vis[u]=1;
	memset(sum,0,sizeof(sum));
	sum[0]++;
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(vis[v])continue;
		cal_dfs(v,u,w[i]);
		set_dfs(v,u,w[i]);
	}
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(vis[v])continue;
		div(v);
	}
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n-1;++i){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}
	div(1);
	ans*=2;ans+=n;
	int t=__gcd(ans,n*n);
	printf("%d/%d\n",ans/t,n*n/t);
	return 0;
}
/*
debug:
6.30
1.61,62行，因为路径必须经过当前的根，所以cal与set必须分开操作，不然会算到自己子树中的点
*/
