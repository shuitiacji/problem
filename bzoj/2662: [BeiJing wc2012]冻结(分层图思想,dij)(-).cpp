#include<bits/stdc++.h>
using namespace std;
const int maxn=100,maxm=2010;
int to[maxm],nxt[maxm],tim[maxm],head[maxn],n,m,k,dis[maxn][maxn];
int e;
void add(int x,int y,int z){
	to[++e]=y;
	nxt[e]=head[x];
	head[x]=e;
	tim[e]=z;
}
struct node{
	int x,y,z;
	bool operator > (const node &b) const{
		return y>b.y;
	}
};
priority_queue<node,vector<node>,greater<node> > q;
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;++i){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);add(y,x,z);
	}
	memset(dis,0x3f,sizeof(dis));
	q.push(node{1,0,0});	
	dis[1][0]=0;
	while(!q.empty()){
		int a=q.top().x,b=q.top().y,c=q.top().z;q.pop();
		for(int i=head[a];i;i=nxt[i]){
			int v=to[i];
			if(dis[v][c]>b+tim[i]){
				dis[v][c]=b+tim[i];
				q.push(node{v,dis[v][c],c});
			}
			if(c+1<=k&&dis[v][c+1]>b+tim[i]/2){
				dis[v][c+1]=b+tim[i]/2;
				q.push(node{v,dis[v][c+1],c+1});
			}
		}
	}
	int ans=0x3f3f3f3f;
	for(int i=0;i<=k;++i){
		ans=min(dis[n][i],ans);
	}
	cout<<ans<<endl;
	return 0;
}
/*
题意：
我们考虑最简单的旅行问题吧：  现在这个大陆上有 N 个城市，M 条双向的
道路。城市编号为 1~N，我们在 1 号城市，需要到 N 号城市，怎样才能最快地
到达呢？
  这不就是最短路问题吗？我们都知道可以用 Dijkstra、Bellman-Ford、
Floyd-Warshall等算法来解决。
  现在，我们一共有 K 张可以使时间变慢 50%的 SpellCard，也就是说，在通
过某条路径时，我们可以选择使用一张卡片，这样，我们通过这一条道路的时间
就可以减少到原先的一半。需要注意的是：
  1. 在一条道路上最多只能使用一张 SpellCard。
  2. 使用一张SpellCard 只在一条道路上起作用。
  3. 你不必使用完所有的 SpellCard。 

思路：
分层图，多一维记card数

*/
