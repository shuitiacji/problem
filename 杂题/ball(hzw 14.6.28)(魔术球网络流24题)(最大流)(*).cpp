#include<bits/stdc++.h>
using namespace std;
#define eps 1e-9
#define maxn 50000
#define Maxn 2000
int s,t;
int N;
struct dinic{
	int e;
	int to[maxn],head[maxn],cap[maxn],next[maxn],flow[maxn],vis[maxn],d[maxn],cur[maxn],mak[maxn];
	void add(int x,int y,int z){
		to[++e]=y;
		next[e]=head[x];
		head[x]=e;
		cap[e]=z;
	}
	int bfs(){
		memset(vis,0,sizeof(vis));
		vis[s]=1;d[s]=0;
		queue<int> q;
		q.push(s);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=head[u];i!=-1;i=next[i]){
				int v=to[i];
				if(!vis[v]&&flow[i]<cap[i]){
					vis[v]=1;
					q.push(v);
					d[v]=d[u]+1;
				}
			}
		}
		if(!vis[t])return 0;
		return 1;
	}
	int dfs(int u,int a){
		if(u==t||a==0)return a;
		int FLOW=0,f;
		if(mak[u]==0)cur[u]=head[u],mak[u]=1;
		for(int &i=cur[u];i!=-1;i=next[i]){
			int v=to[i];
			if(d[v]==d[u]+1&&(f=dfs(v,min(a,cap[i]-flow[i])))>0){
				FLOW+=f;
/**/			flow[i]+=f;
				flow[i^1]-=f;
				a-=f;
				if(a==0)break;
			}
		}
/**/	return FLOW;
	}
	int Dinic(){
		int ret=0;
		while(bfs()){
			memset(mak,0,sizeof(mak));
			ret+=dfs(s,0x3f3f3f3f);
		}
		return ret;
	}
}T;
int TMP;
int main(){
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
	memset(T.head,-1,sizeof(T.head));
	s=Maxn-10;t=Maxn-5;T.e=-1;
	int n;
	scanf("%d",&n);
	while(1){
		N++;
		for(int i=1;i<N;++i){
			double tmp=(double)(sqrt(i+N));
/**/		if(ceil(tmp)*ceil(tmp)==i+N){
			T.add(N,i+Maxn,1);
			T.add(i+Maxn,N,0);
			}
		}
		T.add(s,N,1);T.add(N,s,0);
		T.add(N+Maxn,t,1);T.add(t,N+Maxn,0);
/**/	TMP++;TMP-=T.Dinic();
		if(TMP>n){
			printf("%d\n",N-1);
			break;
		}
	}
	return 0;
}

/*

«问题描述：
假设有n根柱子，现要按下述规则在这n根柱子中依次放入编号为1，2，3，...的球。
（1）每次只能在某根柱子的最上面放球。
（2）在同一根柱子中，任何2个相邻球的编号之和为完全平方数。
试设计一个算法，计算出在n根柱子上最多能放多少个球。例如，在4 根柱子上最多可放11 个球。
«编程任务：
对于给定的n，计算在n根柱子上最多能放多少个球。


思路：
直接求解较为困难，考虑转化为判定性问题，即在n根柱子上能不能放a个球。 
我们把球一个一个放进来
观察本题，对于一个进来的编号的球，他有两种情况，
1.放在某个和他组成平方数的球的后面
2.独立门户
考虑贪心，发现不行，因为即使现在这个点可以套在其他点上，它独立门户可能价值更大(其实贪心
是可以的，但这样就练不了网络流了呀)
所以发现加进来一个点，并不能通过之前的最优状态直接转移，它需要调整。我们可以联想到网络流求最大流过程，每个流也要动态调整，于是去往网络流上想。
对于图论建模，有很常用的办法，那就是针对不同状态拆成不同的点。
根据上述两种状态，把一个点拆成两点，一个点表示1状态，把它与其他构成平方数的点(这个点是原点的第二拆点)连一条容量为1的边，一个表示2，把它与t连一条容量为1的边。
这样求出的最大流，表示了没有自立门户的点的数量，用总量减一下，即得到自立门户的，也就是柱的数量。


debug:
1.50行写成f
2.44,45,+=,-=写反
*/

