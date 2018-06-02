#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
struct node{
	int sz,ch[2],tg,ff,v;
}t[maxn];
int tot,root;
void maintain(int o){
	t[o].sz=t[t[o].ch[0]].sz+t[t[o].ch[1]].sz+1;
}
void pushdown(int o){
	if(t[o].tg==0)return ;
	t[t[o].ch[0]].tg^=1;t[t[o].ch[1]].tg^=1;
	swap(t[o].ch[0],t[o].ch[1]);
	t[o].tg=0;
}
void rotate(int x){
	int y=t[x].ff;
	int z=t[y].ff;
	int d=t[y].ch[1]==x;
	if(z)t[z].ch[t[z].ch[1]==y]=x;t[x].ff=z;
	t[y].ch[d]=t[x].ch[d^1];t[t[x].ch[d^1]].ff=y;
	t[x].ch[d^1]=y;t[y].ff=x;
	maintain(y);maintain(x);
}
void splay(int x,int goal){
	while(t[x].ff!=goal){
		int y=t[x].ff;int z=t[y].ff;
		if(z!=goal)
			(t[y].ch[0]==x)^(t[z].ch[0]==y)?rotate(x):rotate(y);
		rotate(x);
	}
	if(goal==0)root=x;
}
void ins(int x){
	int u=root;
	while(t[u].ch[t[u].v<x])u=t[u].ch[t[u].v<x];
	int v=++tot;
	if(u)t[u].ch[t[u].v<x]=v;t[v].ff=u;
	t[v].sz=1;t[v].v=x;
	splay(v,0);
}
int k_q(int x){
	int u=root;
	while(1){
		pushdown(u);
		int tmp=t[t[u].ch[0]].sz;
		if(x>tmp+1){
			x-=tmp+1;
			u=t[u].ch[1];
		}
		else {
			if(x<=tmp)u=t[u].ch[0];
			else return u;
		}
	}
}
void flip(int x,int y){
	int X=k_q(x),Y=k_q(y+2);
	splay(X,0);splay(Y,X);
	t[t[Y].ch[0]].tg^=1;
}
void gao(int u){
	pushdown(u);
	if(t[u].ch[0])gao(t[u].ch[0]);
	if(abs(t[u].v)!=0x3f3f3f3f)printf("%d ",t[u].v);
	if(t[u].ch[1])gao(t[u].ch[1]);
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	ins(-0x3f3f3f3f);ins(0x3f3f3f3f);
	int n,m;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)ins(i);
	scanf("%d",&m);
	for(int i=1;i<=m;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		flip(x,y);
	}
	gao(root);
	return 0;
}
/*
debug:
5.16:
1.maintain忘记自身+1
2.gao忘记pushdown
5.21:
1.gao忘记pushdown
2.gao忘记把==0x3f3f3f3f去掉
3.39行写成t[t[u].v]而不是t[t[u].v<x]
*/
