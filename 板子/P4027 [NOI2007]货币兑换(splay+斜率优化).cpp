#include<bits/stdc++.h>
using namespace std;
#define db double
#define inf 1e9
#define eps 1e-9
const int maxn=100010;
struct node{
	int ff,ch[2];db v;
}t[maxn];
int n;
db dp[maxn],lk[maxn],rk[maxn],A[maxn],B[maxn],R[maxn],X[maxn],Y[maxn];
void rotate(int x){
	int y=t[x].ff;int z=t[y].ff;int d=t[y].ch[1]==x;
/**/if(z)t[z].ch[t[z].ch[1]==y]=x;t[x].ff=z;
	t[y].ch[d]=t[x].ch[d^1];t[t[x].ch[d^1]].ff=y;
	t[x].ch[d^1]=y;t[y].ff=x;
}
int rt,tot;
void splay(int x,int goal){
	while(t[x].ff!=goal){
		int y=t[x].ff,z=t[y].ff;
		if(z!=goal)
			(t[y].ch[1]==x)^(t[z].ch[1]==y)?rotate(x):rotate(y);
		rotate(x);
	}
	if(goal==0)rt=x;
}
void ins(db x){
	int u=rt;
/**/while(t[u].ch[t[u].v<x+eps])u=t[u].ch[t[u].v<x+eps];
	tot++;
	if(u!=0)t[u].ch[t[u].v<x+eps]=tot;t[tot].ff=u;
	t[tot].v=x;t[tot].ch[1]=t[tot].ch[0]=0;
	splay(tot,0);
}
int find(int x,db num){
	if(!x)return 0;
	if(lk[x]+eps>=num&&rk[x]<=num+eps)return x;
	if(lk[x]<num+eps)return find(t[x].ch[0],num);
	return find(t[x].ch[1],num);
}
db gk(int a,int b){
	return (Y[a]-Y[b])/(X[a]-X[b]);
}
int pre(int x){
	int u=t[x].ch[0],tmp=u;
	while(u){
		if(lk[u]+eps>=gk(x,u))tmp=u,u=t[u].ch[1];
		else u=t[u].ch[0];
	}
	return tmp;
}
int nxt(int x){
	int u=t[x].ch[1],tmp=u;
	while(u){
/**/	if(rk[u]<=gk(u,x)+eps)tmp=u,u=t[u].ch[0];
		else u=t[u].ch[1];
	}
	return tmp;
}
void gao(int x){
	if(t[x].ch[0]){
		int y=pre(x);
		splay(y,x);t[y].ch[1]=0;
/**/	lk[x]=rk[y]=gk(x,y);
	}
	else lk[x]=inf;
	if(t[x].ch[1]){
		int y=nxt(x);
		splay(y,x);t[y].ch[0]=0;
		rk[x]=lk[y]=gk(y,x);
	}
	else rk[x]=-inf;
	if(lk[x]<=rk[x]+eps){
		rt=t[x].ch[0];t[rt].ff=0;t[rt].ch[1]=t[x].ch[1];t[t[x].ch[1]].ff=rt;
		lk[t[x].ch[1]]=rk[rt]=gk(t[x].ch[1],rt);
	}
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%lf",&n,&dp[0]);
	for(int i=1;i<=n;++i){
		scanf("%lf%lf%lf",&A[i],&B[i],&R[i]);
		int j=find(rt,-A[i]/B[i]);
		dp[i]=max(dp[i-1],Y[j]*R[j]*A[i]+Y[j]*B[i]);
		Y[i]=dp[i]/(A[i]*R[i]+B[i]),X[i]=Y[i]*R[i];
		ins(X[i]);
		gao(rt);
	}
	printf("%.3lf\n",dp[n]);
	return 0;
}
/*
Debug:
5.29
1.14行写成if(!z);
2.ins函数中v与x全没有用db与eps
3.nxt,pre,gao中的gk的x,y搞反
*/
