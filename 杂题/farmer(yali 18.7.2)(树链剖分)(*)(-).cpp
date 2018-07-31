#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int son[maxn],sz[maxn],f[maxn],s[maxn][3],a[maxn],p[maxn],fp[maxn],totp,top[maxn],End[maxn];
int Maxl[maxn<<2],Maxr[maxn<<2],Minl[maxn<<2],Minr[maxn<<2],tag[maxn<<2],mak[maxn],b[maxn];
void dfs1(int u,int fa){
	sz[u]=1;son[u]=-1;f[u]=fa;
	for(int i=1;i<=2;++i){
		int v=s[u][i];
		if(v==0)continue;
		dfs1(v,u);
		if(son[u]==-1||sz[son[u]]<sz[v])son[u]=v;
		sz[u]+=sz[v];
		mak[v]=i-1;
		a[v]=b[u];
	}
}
void dfs2(int u,int tp){
	top[u]=tp;p[u]=++totp;fp[totp]=u;
	if(son[u]!=-1)dfs2(son[u],tp);
	for(int i=1;i<=2;++i){
		int v=s[u][i];
		if(v==0||v==son[u])continue;
		dfs2(v,v);
	}	
	End[u]=totp;
}
#define ls o<<1,l,mid
#define rs o<<1|1,mid+1,r
void maintain(int o){
	Minl[o]=min(Minl[o<<1],Minl[o<<1|1]);
	Minr[o]=min(Minr[o<<1],Minr[o<<1|1]);
	Maxl[o]=max(Maxl[o<<1],Maxl[o<<1|1]);
	Maxr[o]=max(Maxr[o<<1],Maxr[o<<1|1]);
}
void build(int o,int l,int r){
	if(l==r){
		Minl[o]=0x3f3f3f3f;Minr[o]=0x3f3f3f3f;
		Maxl[o]=0;Maxr[o]=0;
		if(fp[l]==1)return ;
		if(mak[l]==0){
			Minl[o]=a[fp[l]];Maxl[o]=a[fp[l]];
		}
		if(mak[r]==1){
			Minr[o]=a[fp[l]];Maxr[o]=a[fp[l]];
		}
		return ;
	}
	int mid=(l+r)>>1;
	build(ls);build(rs);
	maintain(o);
}
void pushdown(int o,int l,int r){
	if(!tag[o])return ;
	tag[o<<1]^=1;tag[o<<1|1]^=1;
	int mid=(l+r)>>1;
	if(tag[o<<1]){
		swap(Minl[o<<1],Minr[o<<1]);swap(Maxl[o<<1],Maxr[o<<1]);
		if(l==mid){
			mak[l]^=1;
		}
	}
	if(tag[o<<1|1]){
		swap(Minl[o<<1|1],Minr[o<<1|1]);swap(Maxl[o<<1|1],Maxr[o<<1|1]);
		if(mid+1==r){
			mak[r]^=1;
		}	
	}
	tag[o]=0;
}
void upt(int o,int l,int r,int x,int v){
	if(l==r){
		Minl[o]=0x3f3f3f3f;Minr[o]=0x3f3f3f3f;
		Maxl[o]=0;Maxr[o]=0;
		if(fp[l]==1)return ;
		if(mak[l]==0){
			Minl[o]=v;Maxl[o]=v;
		}
		if(mak[l]==1){
			Minr[o]=v;Maxr[o]=v;
		}
		return ;
	}
	pushdown(o,l,r);
	int mid=(l+r)>>1;
	if(x<=mid)upt(ls,x,v);
	else upt(rs,x,v);
	maintain(o);
}
void rev(int o,int l,int r,int x,int y){
	if(x<=l&&r<=y){
		tag[o]^=1;
		swap(Minl[o],Minr[o]);swap(Maxl[o],Maxr[o]);
		return ;
	}
	pushdown(o,l,r);
	int mid=(l+r)>>1;
	if(x<=mid)rev(ls,x,y);
	if(y>mid)rev(rs,x,y);
	maintain(o);
}
int que(int o,int l,int r,int x,int y,int fg){
	if(x<=l&&r<=y){
		if(fg==0)return Maxr[o];
		return Minl[o];
	}
	pushdown(o,l,r);
	int mid=(l+r)>>1,ret;
	if(!fg)ret=0;
	else ret=0x3f3f3f3f;
	if(x<=mid){if(!fg)ret=max(ret,que(ls,x,y,fg));else ret=min(ret,que(ls,x,y,fg));}
	if(y>mid){if(!fg)ret=max(ret,que(rs,x,y,fg));else ret=min(ret,que(rs,x,y,fg));}
	return ret;
}
int find(int X){
	int u=X;
	int tmpx=0,tmpn=0x3f3f3f3f;
	int f1=top[u];
	while(f1!=1){
		tmpx=max(tmpx,que(1,1,totp,p[f1],p[u],0));
		tmpn=min(tmpn,que(1,1,totp,p[f1],p[u],1));
		u=f[f1];f1=top[u];
	}
	tmpx=max(tmpx,que(1,1,totp,p[1],p[u],0));
	tmpn=min(tmpn,que(1,1,totp,p[1],p[u],1));
	if(b[X]>tmpx&&b[X]<tmpn)return 1;
	return 0;
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n=read(),m=read();
	for(int i=1;i<=n;++i){
		b[i]=read();s[i][1]=read();s[i][2]=read();
	}
	dfs1(1,0);dfs2(1,1);
	build(1,1,totp);
	for(int i=1;i<=m;++i){
		int opt,x;
		scanf("%d%d",&opt,&x);
		if(opt==1){
			int y;
			scanf("%d",&y);
			b[x]=y;
			if(s[x][1])upt(1,1,totp,p[s[x][1]],y);
			if(s[x][2])upt(1,1,totp,p[s[x][2]],y);
		}
		if(opt==2){
			rev(1,1,totp,p[x],End[x]);
		}
		if(opt==3){
			int ok=find(x);
			if(ok)puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
/*
题意：
小D有一棵二叉树，第i个节点权值为ai。
现在给这棵树施肥，肥料是这么工作的：
首先假设所有节点各不相同（小D这棵可能不满足），每种权值对应一种肥料，所有肥料会从根进入树中，如果一种肥料对应的权值等于当前节点的权值，这种肥料会被当前节点完全吸收，否则若肥料对应的权值小于当前节点权值，肥料会流向左子树，否则流向右子树。
查询一个点能否吸收到肥料，并且支持修改一个点的权值或者翻转一个子树（子树内所有节点左右儿子互换）
思路：
首先如果暴力，对每种肥料都要从根往下走，不同肥料走的都不一样，没有什么公共的信息可以维护，所以要换一种思路，考虑对每种肥料都普适的东西进行维护。
考虑一个节点，它对于所有肥料都有同样的限制，在它左子树中被吸收的肥料权值必须小于这个点的权值，右子树必须大于。
这样一来，询问一个点时，它到根的路径上，会有各种各样这种限制，而这些东西实际上就是个不等式，表示能流到这个节点的范围，只需要看看它的权值是否在其中即可。
维护这个东西的话，因为是不等式，只须要维护一个最大值（对于所有右子节点），最小值（左子节点）。树剖+线段树即可。
区分开左子节点与右子节点，在线段树叶子处增加一个属性值，只对属性为左的求最大，右的求最小。

考虑翻转，先在树剖中像dfs序一样来找到子树区间，并对区间内所有点的属性值取反。
这个可以打标记，同时也需要记一下对于右节点的最小值和左节点的最大值，方便swap左与右的最值信息。
*/
