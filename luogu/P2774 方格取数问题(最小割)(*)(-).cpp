#include<bits/stdc++.h>
using namespace std;
#define next Next
#define map Map
const int maxn=9000,maxm=100000;
int s,t;
int map[maxn][maxn];
struct Max_flow{
	int e;
	int to[maxm],head[maxn],cap[maxm],next[maxm],d[maxn],vis[maxn],flow[maxm],cur[maxm];
	void add(int x,int y,int z){
		to[++e]=y;
		next[e]=head[x];
		head[x]=e;
		cap[e]=z;
		to[++e]=x;
		next[e]=head[y];
		head[y]=e;
		cap[e]=0;
	}
	int bfs(){
		memset(vis,0,sizeof(vis));
		queue<int> q;
		vis[s]=1;q.push(s);d[s]=0;
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=head[u];i!=-1;i=next[i]){
				int v=to[i];
				if(!vis[v]&&flow[i]<cap[i]){
/**/				d[v]=d[u]+1;
					vis[v]=1;
					q.push(v);
				}
			}
		}
		if(!vis[t])return 0;
		return 1;
	}
	int dfs(int x,int a){
		if(x==t||a==0){return a;}
		int f,FLOW=0;
/**/	for(int &i=cur[x];i!=-1;i=next[i]){
			int v=to[i];
			if(d[v]==d[x]+1&&(f=dfs(v,min(a,cap[i]-flow[i])))>0){
				FLOW+=f;
				flow[i]+=f;
				flow[i^1]-=f;
				a-=f;
				if(a==0)break;
			}
		}
		return FLOW;
	}
	int gao(){
		int ret=0;
		while(bfs()){
			for(int i=s;i<=t;++i)cur[i]=head[i];
			ret+=dfs(s,0x3f3f3f3f);
		}
		return ret;
	}
}T;
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF){
		T.e=-1;
		memset(T.head,-1,sizeof(T.head));
		memset(T.flow,0,sizeof(T.flow));
		s=0;t=n*m+1;
		int tot=0,sum=0;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				scanf("%d",&map[i][j]);
				sum+=map[i][j];
			}
		}
/*		for(int i=1;i<=k;++i){
			int x,y;
			scanf("%d%d",&x,&y);
//			map[x][y]=0x3f3f3f3f;
			if((x+y)&1)T.add(s,(x-1)*n+y,0x3f3f3f3f);
			else T.add((x-1)*n+y,t,0x3f3f3f3f);
		}*/
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				int x=map[i][j];
/**/			if((i+j)&1)T.add(s,(i-1)*m+j,x);
				else T.add((i-1)*m+j,t,x);
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				if(i+1<=n){
					if((i+j)&1)T.add((i-1)*m+j,i*m+j,0x3f3f3f3f);
					else T.add(i*m+j,(i-1)*m+j,0x3f3f3f3f);
				}
				if(j+1<=m){
					if((i+j)&1)T.add((i-1)*m+j,(i-1)*m+j+1,0x3f3f3f3f);
					else T.add((i-1)*m+j+1,(i-1)*m+j,0x3f3f3f3f);
				}
			}
		}
		printf("%d\n",sum-T.gao());
	}
	return 0;
}
/*
题意：
在一个有 m*n 个方格的棋盘中，每个方格中有一个正整数。现要从方格中取数，使任意 2 个数所在方格没有公共边，且取出的数的总和最大。试设计一个满足要求的取数算法。对于给定的方格棋盘，按照取数要求编程找出总和最大的数。
思路：
这种取数，且数与数之间有关系的题，可以构建二分图求最小割解决。
对于路径source -> x -> y -> sink，我们根据最小割的边来讨论所表示的意义。
一、若割去source -> x，说明不选x点选y点；
二、若割去y->sink，说明不选y点选x点；
三、若割去x->y，说明既选x点又选y点。
对于本题：
一、对y与sink连点，容量为y权值
二、对x与source连点，容量为x权值
三、对x与y连点，容量为0x3f3f3f3f，表示无法割去，即xy不能同选
对于二分图：
我们发现只有i+j为奇的点会与i+j为偶的有关系，根据这个建二分图即可
debug:
1.30行，写成d[v]=d[s]+1;
2.42行，忘记当前弧优化
3.后面所有建点的编号均写成了...*n，而不是...*m
*/
