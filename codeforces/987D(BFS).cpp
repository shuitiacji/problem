#include<bits/stdc++.h>
using namespace std;
#define next Next
const int maxn=200010,maxm=maxn<<1;
int to[maxm],head[maxn],next[maxm],w[maxm],dis[maxn][110];
int tot;
int n,m,k,S;
void add(int x,int y,int v){
	to[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
	w[tot]=v;
}
void dij(int s){
	queue<int> q;
	dis[s][s-n]=0;
	q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=next[i]){
			int v=to[i];
			if(dis[v][s-n]==0x3f3f3f3f){
				dis[v][s-n]=dis[u][s-n]+1;
				q.push(v);
			}
		}
	}
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
	n=read();m=read();k=read();S=read();
	for(int i=1;i<=n;++i){
		int x=read();
		add(x+n,i,0);
	}
	for(int i=1;i<=m;++i){
		int x=read(),y=read();
		add(x,y,1);add(y,x,1);
	}
	memset(dis,0x3f,sizeof(dis));
	for(int i=n+1;i<=n+k;++i){
		dij(i);
	}
	for(int i=1;i<=n;++i){
		sort(&dis[i][1],&dis[i][k]+1);
		int ret=0;
		for(int j=1;j<=S;++j){ret+=dis[i][j];}
		printf("%d ",ret-S);
	}
	return 0;
}
/*
n个点，m条边，有k种商品，每个点给定生产一种商品，对于每个点，要求从k种商品中选S种，然后从附近的点搬来这S种商品，使得这样费用（每经过一条边，费用+1）最小。对于每个点输出这个最小费用。
思路：因为k<=100，多建k个点代表k种商品，对于这些点，连向那些生产这种商品的点，对每一种商品跑一次BFS即可。
*/
