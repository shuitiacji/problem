#include<bits/stdc++.h>
using namespace std;
const int maxn=40100,maxm=maxn<<1;
int to[maxm],nxt[maxm],head[maxn],son[maxn],sz[maxn],dep[maxn],f[maxn],top[maxn];
int e;
void add(int x,int y){
	to[++e]=y;
	nxt[e]=head[x];
	head[x]=e;
}
void dfs1(int u,int fa){
	dep[u]=dep[fa]+1;f[u]=fa;sz[u]=1;son[u]=-1;
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa)continue;
//		if(v!=fa)dfs1(v,u);
		dfs1(v,u);
		if(son[u]==-1||sz[v]>sz[son[u]])son[u]=v;
		sz[u]+=sz[v];
	}
}
void dfs2(int u,int tp){
	top[u]=tp;
	if(son[u]!=-1)dfs2(son[u],tp);
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v!=f[u]&&v!=son[u])dfs2(v,v);
	}
}
int find(int u,int v){
	int f1=top[u],f2=top[v];
	while(f1!=f2){
		if(dep[u]<dep[v])swap(u,v),swap(f1,f2);
		u=f[f1];f1=top[u];
	}
	if(dep[u]>dep[v])swap(u,v);
	return u;
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	int n,m;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		if(x==-1)x=maxn-10;
		if(y==-1)y=maxn-10;
		add(x,y);
		add(y,x);
	}
	dfs1(maxn-10,maxn-10);
	dfs2(maxn-10,maxn-10);
	scanf("%d",&m);
	for(int i=1;i<=m;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		int tmp=find(x,y);
		if(tmp==x)puts("1");
		if(tmp==y)puts("2");
		if(tmp!=x&&tmp!=y)puts("0");
	}
	return 0;
}
/*
题意：
已知一棵 n 个节点的有根树。有 m 个询问。每个询问给出了一对节点的编号 x 和 y ,询问 x
与 y 的祖孙关系。

思路：
lca
or dfs序
debug：
16行的写法是错误的，应写成15行
*/
