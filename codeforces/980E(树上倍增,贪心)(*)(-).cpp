#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
#define next Next
int head[maxn],next[maxn*2],to[maxn*2],can[maxn],anc[maxn][21];
int e;
void add(int x,int y){
	to[++e]=y;
	next[e]=head[x];
	head[x]=e;
}
void dfs(int u,int fa){
	for(int i=head[u];i;i=next[i]){
		int v=to[i];
		if(v==fa)continue;
		anc[v][0]=u;
		for(int i=1;i<=20;++i)anc[v][i]=anc[anc[v][i-1]][i-1];
		dfs(v,u);
	}
}
int check(int x,int k){
	for(int i=20;i>=0;--i){
		if((k>>i)&1)x=anc[x][i];
	}
	return can[x];
}
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	for(int i=0;i<=20;++i)anc[n][i]=n;
	dfs(n,0);
	can[n]=1;
	k=n-k-1;
	for(int i=n-1;i>=1;--i){
		if(check(i,k)){
			int t=i;
			while(!can[t]){
				can[t]=1;
				t=anc[t][0];
				k--;
			}
		}
	}
	for(int i=1;i<=n;++i){
		if(!can[i])printf("%d ",i);
	}
	return 0;
}
/*
题意：给定一颗有 n个点的树，i号点的权值是2^i要求删去 k个点，使得剩下的点仍然连通，并且总权值和最大，问删去的所有点的编号。
思路：考虑一个特殊性质，只要选了n号点，1——(n-1)号点总和都不会超过n，于是可以不计后果的取当前最大点来贪心。可以将n号作为树的根，现只要判断一个点能不能在k且联通的限制内保留，明显只要看这个点向上走到根遍历的点数有没有超过k，于是可以倍增向上跳加速算法。
debug：错误定义anc[maxn][20],应该是21才对
*/
