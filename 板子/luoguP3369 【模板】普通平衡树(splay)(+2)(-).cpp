#include<bits/stdc++.h>
using namespace std;
const int maxn=500010;
struct node{
	int sz,num,ch[2],ff,v;
}t[maxn];
int tot,root;
void maintain(int x){
	t[x].sz=t[x].num+t[t[x].ch[0]].sz+t[t[x].ch[1]].sz;
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
	int u=root,ff=0;
	while(u&&t[u].v!=x){
		ff=u;
		u=t[u].ch[t[u].v<x];
	}
	if(u)t[u].num++;
	else {
		u=++tot;
		if(ff)t[ff].ch[t[ff].v<x]=u;t[u].ff=ff;
		t[u].v=x;t[u].sz=t[u].num=1;t[u].ch[0]=t[u].ch[1]=0;
	}
	splay(u,0);
}
int k_q(int x){
	int u=root;
	while(1){
		int tmp=t[t[u].ch[0]].sz;
		if(x>tmp+t[u].num){
			x-=tmp+t[u].num;
			u=t[u].ch[1];
		}
		else {
			if(x<=tmp)u=t[u].ch[0];
			else return u;
		}
	}
}
void find(int x){
	int u=root;
	while(t[u].v!=x&&t[u].ch[t[u].v<x])u=t[u].ch[t[u].v<x];
	splay(u,0);
}
int Last_Next(int x,int fg){//fg 0 last fg 1 next
	find(x);
	int u=root;
	if((fg==0&&t[u].v<x)||(fg==1&&t[u].v>x))return u;
	u=t[u].ch[fg];
	while(t[u].ch[fg^1])u=t[u].ch[fg^1];
	return u;
}
void del(int x){
	int last=Last_Next(x,0);
	int next=Last_Next(x,1);
	splay(last,0);splay(next,last);
	int u=t[next].ch[0];
	if(t[u].num>1)t[u].num--,splay(u,0);
	else t[next].ch[0]=0;
	splay(next,0);
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
	ins(-0x3f3f3f3f);ins(0x3f3f3f3f);
	int n=read();
	for(int i=1;i<=n;++i){
		int opt=read();
		int x=read();
		if(opt==1)ins(x);
		if(opt==2)del(x);
		if(opt==3){find(x);printf("%d\n",t[t[root].ch[0]].sz);}
		if(opt==4)printf("%d\n",t[k_q(x+1)].v);
		if(opt==5)printf("%d\n",t[Last_Next(x,0)].v);
		if(opt==6)printf("%d\n",t[Last_Next(x,1)].v);
	}
	return 0;
}
/*
debug:
5.18
1.27行写成if(goal==root)
2.74行忘记splay(u,0)
3.73行写成.ch[1]
ps:洛谷55分一般是del写错
4.91写成t[find(x)].sz
6.3
1.47行符号写反
*/
