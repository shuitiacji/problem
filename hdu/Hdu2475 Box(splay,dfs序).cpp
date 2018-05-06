#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=5e5+10;
#define next Next

struct node{
	int ch[2],ff;
}t[maxn];
int to[maxn],head[maxn],next[maxn],n,dfn[2*maxn],fg[maxn],cnt,e,root,m;
void rotate(int x){
	int y=t[x].ff;
	int z=t[y].ff;
	int d=(x==t[y].ch[1]);
	if(z)t[z].ch[t[z].ch[1]==y]=x;t[x].ff=z;
	t[y].ch[d]=t[x].ch[d^1];t[t[x].ch[d^1]].ff=y;
	t[x].ch[d^1]=y;t[y].ff=x;
}
void splay(int x,int goal){
	while(t[x].ff!=goal){
		int y=t[x].ff,z=t[y].ff;
		if(z!=goal){
			(t[y].ch[0]==x)^(t[z].ch[0]==y)?rotate(x):rotate(y);
		}
		rotate(x);
	}
}
void add(int x,int y){
	to[++e]=y;
	next[e]=head[x];
	head[x]=e;
}
void dfs(int x){
	dfn[++cnt]=x;
	for(int i=head[x];i;i=next[i]){
		dfs(to[i]);
	}
	dfn[++cnt]=x+n;
}
void build(int &u,int l,int r,int fa){
	if(l>r)return ;
	int mid=(l+r)>>1;
	u=dfn[mid];
	t[u].ch[0]=t[u].ch[1]=0;t[u].ff=fa;
	build(t[u].ch[0],l,mid-1,u);
	build(t[u].ch[1],mid+1,r,u);
}
void move(int x,int y){
	if(x==y)return ;
	splay(x,0);splay(x+n,x);
	int tmp=y;
	while(tmp){
		if(t[x+n].ch[0]==tmp)return ;
		tmp=t[tmp].ff;
	}
	int a=t[x].ch[0],b=t[x+n].ch[1];
	t[a].ff=t[b].ff=t[x].ch[0]=t[x+n].ch[1]=0;
	if(a&&b){
		while(t[b].ch[0])b=t[b].ch[0];
		t[b].ch[0]=a;
		t[a].ff=b;
	}
	if(!y)return ;
	splay(y,0);
	tmp=t[y].ch[1];
	while(t[tmp].ch[0])tmp=t[tmp].ch[0];
	t[tmp].ch[0]=x;
	t[x].ff=tmp;
}
int query(int x){
	splay(x,0);
	while(t[x].ch[0]){x=t[x].ch[0];}
	return x;
}
void init(){
	e=0;
	memset(head,0,sizeof(head));
	memset(fg,0,sizeof(fg));
	memset(t,0,sizeof(t));
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int fff=0;
	while(scanf("%d",&n)!=EOF){
		if(fff){cout<<endl;}
		else fff=1;
		init();
		for(int i=1;i<=n;++i){
			int x;
			scanf("%d",&x);
			if(!x)fg[i]=1;
			else add(x,i);
		}
		for(int i=1;i<=n;++i){
			if(fg[i]){
				cnt=0;
				dfs(i);
				build(root,1,cnt,0);
			}
		}
		scanf("%d",&m);
		while(m--){
			int x,y;
			char s[10];
			scanf("%s",s);
			if(s[0]=='M'){
				scanf("%d%d",&x,&y);
				move(x,y);
			}
			else {
				scanf("%d",&x);
				printf("%d\n",query(x));
			}
		}
	}
	return 0;
}
/*
题意：有一些盒子，盒子里可以放盒子，给出最初的盒子的状态，有两种操作，第一种是将某一个盒子移动到另一个盒子（如果操作不合法就直接忽略），第二种是查询某个盒子最外边的盒子的编号。








思路：盒子的包含关系就像一颗树，几个最外层的盒子都代表一个树的根，整个序列就是一个森林。可以将一颗树用dfs序的方式转化成线形，用splay维护序列。具体方法：考虑先dfs一遍,第一次访问时在dfs序中新加一个x，子树访问完后再加一个x + N。那么[x,x+N]即为盒内的状况。





Dubug:对每个splay预处理build的时候不是像建线段树一样(非[l,mid],[mid+1,r]),而是[l,mid-1],[mid+1,r]。*/
