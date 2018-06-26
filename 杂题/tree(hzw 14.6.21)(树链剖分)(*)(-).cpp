#include<bits/stdc++.h>
using namespace std;
const int maxn=100010,maxm=maxn<<1;
#define next Next
#define ls lc[o],l,mid
#define rs rc[o],mid+1,r
map<int,int> kind;
int e,tot,totp,totrt,n;
int rt[maxn*5],lc[maxn*100],rc[maxn*100],to[maxm],next[maxm],head[maxn];
int p[maxn],dep[maxn],f[maxn],top[maxn],son[maxn],sz[maxn];
int t[maxn*100];
int A[maxn];
void upt(int &o,int l,int r,int pos,int val){
	if(!o)o=++tot;
	t[o]+=val;
	if(l==r)return ;
	int mid=(l+r)>>1;
	if(pos<=mid)upt(ls,pos,val);
	else upt(rs,pos,val);
}
int query(int o,int l,int r,int X,int Y){
	if(!o){return 0;}
	if(X<=l&&r<=Y)return t[o];
	int mid=(l+r)>>1,ret=0;
	if(X<=mid&&lc[o])ret+=query(ls,X,Y);
	if(Y>mid&&rc[o])ret+=query(rs,X,Y);
	return ret;
}
void add(int x,int y){
	to[++e]=y;
	next[e]=head[x];
	head[x]=e;
}
void dfs1(int u,int fa){
	f[u]=fa;sz[u]=1;son[u]=0;dep[u]=dep[fa]+1;
	for(int i=head[u];i;i=next[i]){
		int v=to[i];
		if(v==fa)continue;
		if(sz[v])continue;
		dfs1(v,u);
		if(son[u]==0||sz[son[u]]<sz[v])son[u]=v;
		sz[u]+=sz[v];
	}
}
void dfs2(int u,int tp){
	top[u]=tp;p[u]=++totp;
	if(son[u]!=0)dfs2(son[u],tp);
	for(int i=head[u];i;i=next[i]){
		int v=to[i];if(p[v])continue;
		if(v!=f[u]&&v!=son[u])dfs2(v,v);
	}
}
int que(int u,int v,int val){
	int f1=top[u],f2=top[v];
	int tmp=0;
/**/while(f1!=f2){
		if(dep[f1]<dep[f2])swap(f1,f2),swap(u,v);
		tmp+=query(rt[val],1,n,p[f1],p[u]);
		u=f[f1];f1=top[u];
	}
	if(dep[u]<dep[v])swap(u,v);
	tmp+=query(rt[val],1,n,p[v],p[u]);
	return tmp;
}
int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n=read();int Q=read();
	for(int i=1;i<=n;++i){
		A[i]=read();
		if(kind[A[i]]==0)kind[A[i]]=++totrt;
		A[i]=kind[A[i]];
	}
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		add(x,y);add(y,x);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(int i=1;i<=n;++i)upt(rt[A[i]],1,n,p[i],1);
	int lastans=0;
	for(int i=1;i<=Q;++i){
		char a[4];
		scanf("%s",a);
		int x=read()^lastans,y=read()^lastans,z;
		if(a[0]=='Q'){
			z=read()^lastans;
			if(kind[z]==0)kind[z]=++totrt;
			lastans=que(x,y,kind[z]);
			printf("%d\n",lastans);
		}
		else {
			if(kind[y]==0)kind[y]=++totrt;
			upt(rt[kind[y]],1,n,p[x],1);
			upt(rt[A[x]],1,n,p[x],-1);
			A[x]=kind[y];
		}
	}
	return 0;
}

题意：
小奇的花园有n个温室，标号为1到n，温室以及以及温室间的双向道路形成一棵树。

每个温室都种植着一种花，随着季节的变换，温室里的花的种类也在不断发生着变化。

小奇想知道从温室x走到温室y的路径中(包括两个端点),第t种花出现的次数。

• C x t 表示在温室x中的花的种类变为t。

• Q x y t 表示询问温室x走到温室y的路径中(包括两个端点),第t种花出现

的次数。

思路：
给每种花开一个线段树，考虑到种类范围有2^31，但由于n与m没这么大，可以用map映射一下。
接下来两种思路。
1.然后暴力树剖。nlognlogn
2.不用树剖也可以，运用部分和思想把单点修改，路径查询转化成子树修改，单点询问。
具体地说我们用Vi 表示点i 的权值，Si 表示点i 到根节点上的权值和，那么询问x 到y 路径的权值和时，我们找到x 和y 的lca 那么答案就是Sx + Sy – 2Slca + Vlca. 而如果修改点x 的权值，就相当于x 子树上所有点的Si 都加上了一个数，我们只要先处理DFS序列之后就转化成区间加，这样可用线段树或者树状数组实现。(nlogn,然而并没有写).

debug：
56行while写成if
