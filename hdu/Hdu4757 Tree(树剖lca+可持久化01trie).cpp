#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=2e5+10;
#define next Next
int V[maxn],rt[maxn],ch[maxn*17][2],val[maxn*17],head[maxn],to[maxn<<1],next[maxn<<1],f[maxn],top[maxn],dep[maxn],son[maxn],sz[maxn],tot,e;
void ins(int o,int &O1,int x){
	O1=++tot;
	int o1=O1;
	for(int i=17;i>=0;--i){
		int c=(x>>i)&1;
		ch[o1][c]=++tot;
		ch[o1][c^1]=ch[o][c^1];
		if(!ch[o][c])val[tot]=1;
		else val[ch[o1][c]]=val[ch[o][c]]+1;
		o1=ch[o1][c];o=ch[o][c];
	}
}
int que(int o,int o1,int x){
	int ans=0;
	for(int i=17;i>=0;--i){
		int c=(x>>i)&1;
		int tmp=val[ch[o1][c^1]]-val[ch[o][c^1]];
		if(tmp>0){
			ans+=(1<<i);
			o=ch[o][c^1];
			o1=ch[o1][c^1];
		}
		else {
			o=ch[o][c];
			o1=ch[o1][c];
		}
	}
	return ans;
}
void dfs1(int u,int fa){
	ins(rt[fa],rt[u],V[u]);
	sz[u]=1;dep[u]=dep[fa]+1;f[u]=fa;son[u]=0;
	for(int i=head[u];i;i=next[i]){
		int v=to[i];
		if(v==fa)continue;
		dfs1(v,u);
		sz[u]+=sz[v];
		if(!son[u]||sz[v]>sz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp){
	top[u]=tp;
	if(son[u])dfs2(son[u],tp);
	for(int i=head[u];i;i=next[i]){
		int v=to[i];
		if(v==son[u]||v==f[u])continue;
		dfs2(v,v);
	}
}
int lca(int u,int v){
	int f1=top[u],f2=top[v];
	while(f1!=f2){
		if(dep[f1]<=dep[f2])swap(f1,f2),swap(u,v);
		u=f[f1];f1=top[u];
	}
	return dep[u]<dep[v]?u:v;
}
void add(int x,int y){
	to[++e]=y;
	next[e]=head[x];
	head[x]=e;
}
void init(){
	tot=0;e=0;
	memset(val,0,sizeof(val));
	memset(ch,0,sizeof(ch));
	memset(rt,0,sizeof(rt));
	memset(head,0,sizeof(head));
	memset(dep,0,sizeof(dep));
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n,m;
	while(~scanf("%d%d",&n,&m)){
		init();
		for(int i=1;i<=n;++i)scanf("%d",&V[i]);
		for(int i=1;i<n;++i){
			int x,y;
			scanf("%d%d",&x,&y);
			add(x,y);add(y,x);
		}
		dfs1(1,0);dfs2(1,1);
		for(int i=1;i<=m;++i){
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			int tmp=lca(x,y);
			printf("%d\n",max(que(rt[f[tmp]],rt[x],z),que(rt[f[tmp]],rt[y],z)));
		}
	}
	return 0;
}
/*
题意：给定一棵树，每个节点有权值，每次查询节点 (u,v) 以及 x ，问 u 到 v 路径上的某个节点与 x 异或最大的值是多少。
思路：lca+可持久化01trie
debug：
1.8行，非递归程序使用了传值，没有将o1与O1分开，使rt计算错误。
2.54||写成&&
*/
