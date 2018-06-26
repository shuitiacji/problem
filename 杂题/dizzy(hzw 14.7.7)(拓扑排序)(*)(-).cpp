#include<bits/stdc++.h>
using namespace std;
const int maxn=100010,maxm=maxn;
#define next Next
int to[maxm],next[maxm],head[maxn],vis[maxn],in[maxn];
int e,tot;
void add(int a,int b){
	to[++e]=b;
	next[e]=head[a];
	head[a]=e;
}
int main(){
	freopen("dizzy.in","r",stdin);
	freopen("dizzy.out","w",stdout);
	memset(vis,0x3f,sizeof(vis));
	int n,p1,p2;
	scanf("%d%d%d",&n,&p1,&p2);
	for(int i=1;i<=p1;++i){
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);in[b]++;
	}
	queue<int> q;
	for(int i=1;i<=n;++i){
		if(!in[i])vis[i]=++tot,q.push(i);
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=next[i]){
			int v=to[i];
			in[v]--;
			if(!in[v])vis[v]=++tot,q.push(v);
		}
	}
	for(int i=1;i<=p2;++i){
		int a,b;
		scanf("%d%d",&a,&b);
		if(vis[a]<vis[b])printf("%d %d\n",a,b);
		else printf("%d %d\n",b,a);
	}
	return 0;
}
/*
题意：给你一张混合图,p1条有向边,p2条无向边,要求你为无向边定向,使得图上没有环。

思路：
判环的东西，我们能想到拓扑排序,我们发现一张图可以完全的拓扑排序是在该图为有向无环图的时候，那么如果有环呢？环里面的点是不会被加入排序队列里面的，也就是排出来的点数小于n
只看有向边的话,原图是个有向无环图,也就是说是个拓扑图,如果加完边后依然是拓扑图,也就是依然无环。
对原图做拓扑排序,得到每个点的入队时间,加边的时候把边定向为从入队时间早的点到晚的点,原来的入队顺序就依然成立,就无环了。

*/
