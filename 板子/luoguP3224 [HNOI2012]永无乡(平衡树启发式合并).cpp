#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
int tot;
int f[maxn];
int find(int x){
	int r=x;
	while(f[r]!=r)r=f[r];
	int i=x,j;
	while(i!=r){
		j=f[i];
		f[i]=r;
		i=j;
	}
	return r;
}
struct node{
	int id,v,ff,ch[2],sz;
}t[500000];
struct SBT{
	int rt;
	void maintain(int x){
		t[x].sz=t[t[x].ch[1]].sz+t[t[x].ch[0]].sz+1;
	}
	void rotate(int x){
		int y=t[x].ff,z=t[y].ff;
		int d=t[y].ch[1]==x;
		if(z)t[z].ch[t[z].ch[1]==y]=x;t[x].ff=z;
		t[y].ch[d]=t[x].ch[d^1];t[t[x].ch[d^1]].ff=y;
		t[y].ff=x;t[x].ch[d^1]=y;
		maintain(y);maintain(x);
	}
	void splay(int x,int goal){
		while(t[x].ff!=goal){
			int y=t[x].ff,z=t[y].ff;
			if(z!=goal)
				(t[y].ch[1]==x)^(t[z].ch[1]==y)?rotate(x):rotate(y);
			rotate(x);
		}
		if(goal==0)rt=x;
	}
	int k_q(int x){
		int u=rt;
		if(t[u].sz<x)return -1;
		while(1){
			int tmp=t[t[u].ch[0]].sz;
			if(x>tmp+1){
				x-=tmp+1;
				u=t[u].ch[1];
			}
			else {
				if(x<=tmp)u=t[u].ch[0];
				else {
					return t[u].id;
				}
			}
		}
	}
	void ins(int x,int v){
		int u=rt;
		while(t[u].ch[t[u].v<v])u=t[u].ch[t[u].v<v];
		tot++;
		if(u)t[u].ch[t[u].v<v]=tot;t[tot].ff=u;
		t[tot].id=x;t[tot].v=v;t[tot].sz=1;
		splay(tot,0);
	}
}T[maxn];
void dfs(int u,int kk){
	if(t[u].ch[0])dfs(t[u].ch[0],kk);
	if(t[u].ch[1])dfs(t[u].ch[1],kk);
	T[kk].ins(t[u].id,t[u].v);
}
void merge(int x,int y){
	x=find(x);y=find(y);
	if(x==y)return ;
	if(t[T[x].rt].sz<t[T[y].rt].sz)swap(x,y);
	f[y]=x;
	dfs(T[y].rt,x);
}
int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n=read(),m=read();
	for(int i=1;i<=n;++i){
		int x=read();
/**/	f[x]=x;
		T[i].ins(i,x);
	}
	for(int i=1;i<=m;++i){
		int x=read(),y=read();
		merge(x,y);
	}
	int q=read();
	for(int i=1;i<=q;++i){
		char a[10];;
		scanf("%s",a);
		int x=read(),y=read();
		if(a[0]=='Q')printf("%d\n",T[find(x)].k_q(y));
		else merge(x,y);
	}
	return 0;
}
/*
debug:
6.6
1.92行忘记写
*/
