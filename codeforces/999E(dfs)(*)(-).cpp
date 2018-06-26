#include<bits/stdc++.h>
using namespace std;
const int maxn=5010,maxm=maxn<<1;
int e;
int to[maxm],nxt[maxm],head[maxn],mak[maxn],vis[maxn];
void add(int x,int y){
	to[++e]=y;
	nxt[e]=head[x];
	head[x]=e;
}
int ans;
int n,m,s;
void dfs(int u,int cur){
	vis[u]=cur;
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(vis[v]!=cur)dfs(v,cur);
	}
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1;i<=m;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	int now=0;
	dfs(s,++now);
	for(int i=1;i<=n;++i){
		if(!vis[i])dfs(i,++now);
	}
	set<int> S;
	for(int i=1;i<=n;++i){
		if(vis[i]!=1)S.insert(vis[i]);
	}
	cout<<S.size()<<endl;
	return 0;
}
/*
题意：
有向图。
添加最小的边数，使得从s点能抵达其他任一点。

思路：
类似无向图求联通块，答案即为联通块个数-1。
这里换成了有向图，一样有向图dfs染色一下，只要注意17行，因为是有向图，需要重复染。
*/
