#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int maxn=2e5+10,maxm=maxn<<1;
int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int to[maxm],nxt[maxm],head[maxn],p[maxn],End[maxn],totp,son[maxn],dep[maxn],f[maxn],sz[maxn],top[maxn],e;
int n,m,q;
struct Node{
	int x,y;
}mak[maxn],bus[maxn];
vector<int> poi[maxn];
int bit[25],anc[maxn][25],ans[maxn];
void add(int x,int y){
	to[++e]=y;nxt[e]=head[x];head[x]=e;
	to[++e]=x;nxt[e]=head[y];head[y]=e;
}
namespace HLD{
	void dfs1(int u,int fa){
		dep[u]=dep[fa]+1;f[u]=fa;sz[u]=1;son[u]=-1;p[u]=++totp;
		for(int i=head[u];i;i=nxt[i]){
			int v=to[i];
			if(v==fa)continue;
			dfs1(v,u);
			if(son[u]==-1||sz[son[u]]<sz[v])son[u]=v;
			sz[u]+=sz[v];
		}
		End[u]=totp;
	}
	void dfs2(int u,int tp){
		top[u]=tp;
		if(son[u]!=-1)dfs2(son[u],tp);
		for(int i=head[u];i;i=nxt[i]){
			int v=to[i];
			if(v==f[u]||v==son[u])continue;
			dfs2(v,v);
		}
	}
	int lca(int u,int v){
		int f1=top[u],f2=top[v];
		while(f1!=f2){
			if(dep[f1]<dep[f2])swap(f1,f2),swap(u,v);
			u=f[f1];f1=top[u];
		}
		if(dep[u]>dep[v])swap(u,v);
		return u;
	}
}
int TMP;
namespace Mulp{
	void gao(){
		n=read();
		for(int i=2;i<=n;++i){
			int x=read();
			add(i,x);
		}
		m=read();
		for(int i=1;i<=m;++i){
			bus[i].x=read();bus[i].y=read();
		}
		HLD::dfs1(1,0);HLD::dfs2(1,1);
		for(int i=1;i<=n;++i){
			mak[i].x=dep[i];mak[i].y=i;
		}
		for(int i=1;i<=m;++i){
			int tmp=HLD::lca(bus[i].x,bus[i].y);
			if(mak[bus[i].x].x>dep[tmp]){
				mak[bus[i].x].x=dep[tmp];mak[bus[i].x].y=tmp;
			}
			if(mak[bus[i].y].x>dep[tmp]){
				mak[bus[i].y].x=dep[tmp];mak[bus[i].y].y=tmp;
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=0;j<=20;++j){
				anc[i][j]=i;
			}
		}
	}
	void dfs1(int u,int fa){
		for(int i=head[u];i;i=nxt[i]){
			int v=to[i];
			if(v==fa)continue;
			dfs1(v,u);
			if(mak[u].x>mak[v].x){
				mak[u].x=mak[v].x;mak[u].y=mak[v].y;
			}
		}
	}
	void dfs2(int u,int fa){
		for(int i=head[u];i;i=nxt[i]){
			int v=to[i];
			if(v==fa)continue;
			anc[v][0]=mak[v].y;
			for(int j=1;j<=20;++j){
				anc[v][j]=anc[anc[v][j-1]][j-1];
			}	
			dfs2(v,u);
		}
	}
	int dfs3(int u,int id,int Lca){
		if(u==Lca){return 1;}
		int v=u;
		for(int i=20;i>=0;--i){
			if(dep[anc[v][i]]>dep[Lca])v=anc[v][i],ans[id]+=bit[i];
		}
		if(dep[anc[v][0]]>dep[Lca]){return 0;}
		TMP=v;
		return 1;
	}
}	
namespace BIT{
	int C[maxn];
	int lowbit(int x){ return x&(-x); }
	void upt(int x){ while(x<=totp){ C[x]++;x+=lowbit(x); } }
	int que(int x){ int ret=0; while(x){ ret+=C[x];x-=lowbit(x); } return ret; }
}
struct node{
	int x,y,z;
};
vector<node> Q[maxn];
int Sum[maxn];
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	bit[0]=1;
	for(int i=1;i<=23;++i)bit[i]=bit[i-1]*2;
	Mulp::gao();Mulp::dfs1(1,0);Mulp::dfs2(1,0);
	q=read();
	for(int i=1;i<=q;++i){
		int x=read(),y=read();
		TMP=0;
		int Lcaxy=HLD::lca(x,y);
		int tmp=Mulp::dfs3(x,i,Lcaxy);
		if(tmp==0){ans[i]=-1;continue;}
		int tmp1=TMP;
		TMP=0;
		tmp=Mulp::dfs3(y,i,Lcaxy);
		if(tmp==0){ans[i]=-1;continue;}
		int tmp2=TMP;
		if(tmp1==0&&tmp2==0)continue;
		if(tmp1==0||tmp2==0){ans[i]++;continue;}
		Q[p[tmp1]-1].pb((node){p[tmp2],End[tmp2],i});
		Q[End[tmp1]].pb((node){p[tmp2],End[tmp2],i});
		ans[i]+=2;
	}	
	for(int i=1;i<=m;++i){
/**/	poi[p[bus[i].x]].pb(p[bus[i].y]);
/**/	poi[p[bus[i].y]].pb(p[bus[i].x]);
	}
	for(int i=1;i<=q;++i)Sum[i]=-1;
	for(int i=0;i<=totp;++i){
		for(int j=0;j<poi[i].size();++j){
			BIT::upt(poi[i][j]);
		}
		for(int j=0;j<Q[i].size();++j){
			if(Sum[Q[i][j].z]==-1){Sum[Q[i][j].z]=BIT::que(Q[i][j].y)-BIT::que(Q[i][j].x-1);}
			else {
				if(BIT::que(Q[i][j].y)-BIT::que(Q[i][j].x-1)-Sum[Q[i][j].z]>0){
					ans[Q[i][j].z]--;
				}
			}	
		}
	}
	for(int i=1;i<=q;++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
/*
题意：
一棵n个节点的树，给你m个a链，询问你q个b链，回答对于每个b链，最少需要多少个a链才能覆盖它。

思路：
树上的链上问题，除了树链剖分，惯用的手段就是把一条链转化成半链，如b链(x,y)转成(x,lca),(y,lca)，这样就将一条链转成了两个序列。
考虑问题在序列上，有点像区间最小覆盖问题，我们自然想到原来解决区间最小覆盖问题思想——贪心，这里显然也可以贪心，每次走一条能走到dep最小点的a链，最后看能不能dep小于lca，并统计答案。
因为只往上走，一个一个跳有点慢，我们可以倍增，这里的一步可以变成走一条a链（当然也是满足贪心的最好的那条）。
实现的话，可以将每个a链也先变半链，对x，y在点上打上一个lca深度的标记，因为若在一个点的子树内存在一个点的标记的dep小于此点，那么此点也可以跳一次到那个点标记的位置，先dfs一遍，回溯的时候处理一下即可，这相当于处理出了每个点的anc[i][0]。再dfs一遍，处理各个anc[i][1~20]。

这个东西有没有问题？有的，因为有可能算重，最多可能有一条a链在b链的两个半链中都出现过被算过。如果存在这样的a链，必须要在答案中减一，因为可以用这条特别的链减小使用的a链数。
为判断这存不存在，我们在两条半链上不能直接跳到lca及以上，跳到只差一步就能到lca的那点A，如果在两个半链上的A的子树中分别存在一组a链的x与y，则绝对要减一。
子树问题可以用dfs序转在序列上，则问题转化成存不存在点对(x,y)使得l1<=x<=r1,l2<=y<=r2，把(x,y)想象成平面上的点，问题即求在一个二维矩形中（l1,l2,r1,r2）的特殊点数（坐标刚好是a链的xy）这就是二维数点的模型。
可以扫描线消去一维，用树状数组维护另一维，边扫边把特殊点加进BIT，询问就在x轴上两点l1-1,r1,存一个pair(l2,r2),在询问开始时记一下树状数组上(l2,r2)区间上的点数，结束时求一下树状数组(l2,r2)的值，再减去一开始的。

debug:
1.anc一开始全部设为它自己没有关系
2.152,153,p[x]与x不要弄混
*/
