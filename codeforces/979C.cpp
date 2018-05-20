#include<bits/stdc++.h>
using namespace std;
const int maxn=300010;
#define next Next
typedef long long LL;
int next[maxn*2],to[maxn*2],head[maxn],sz[maxn];
int tot=0;
int n,s,t;
void add(int x,int y){
	to[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
}
int dfs(int x,int fa){
	sz[x]++;
	int fg=0;
	for(int i=head[x];i;i=next[i]){
		int v=to[i];
		if(v==fa)continue;
		int tmp=dfs(v,x);
		sz[x]+=sz[v];
		if(x==s&&tmp)sz[x]-=sz[v];
		if(tmp==1)fg=1;
	}
	if(x==t)fg=1;
	return fg;
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d%d",&n,&s,&t);
	for(int i=1;i<n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(s,s);
	printf("%lld\n",1LL*n*(n-1)-1LL*sz[s]*sz[t]);
	return 0;
}
/*
题意：
给出一棵树，其中有两个点，x和y，限制走了x之后的路径上不能有y，问可以走的路径(u,v)有多少条，(u,v)和(v,u)考虑为两条不同的路径。
debug:LL
*/
