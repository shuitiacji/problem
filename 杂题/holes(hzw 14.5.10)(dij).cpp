#include<bits/stdc++.h>
using namespace std;
#define next Next
const int maxn=100010,maxm=200000;
struct node{
	int x,y;
	node (int a,int b):x(a),y(b) {}
	bool operator > (const node &b) const {
		return y>b.y;
	}
};
int to[maxm],next[maxm],v[maxm],head[maxn],n,m,col[maxn],w[maxn],s[maxn],dis[maxn];
int tot=0;
void add(int x,int y,int z){
	to[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
	v[tot]=z;
}
priority_queue<node,vector<node>,greater<node> > q;
int main(){
	freopen("holes.in","r",stdin);
	freopen("holes.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%d",&col[i]);
	for(int i=1;i<=n;++i)scanf("%d",&w[i]);
	for(int i=1;i<=n;++i)scanf("%d",&s[i]);
	for(int i=1;i<=m;++i){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		int c1,c2,difw=abs(w[a]-w[b]);
		if(col[a]==col[b])c1=c2=c;
		else {
			if(col[a]==1)
				c1=c+difw,c2=max(c-difw,0);
			else 
				c2=c+difw,c1=max(c-difw,0);
		}
		add(a,b+n,c1);add(a+n,b,c2);
	}
	for(int i=1;i<=n;++i){
		int c1,c2;
		if(col[i]==0)c1=0,c2=s[i];
		else c1=s[i],c2=0;
		add(i,i+n,c1);add(i+n,i,c2);
	}
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;q.push(node(1,0));
	while(!q.empty()){
		int x=(q.top()).x;q.pop();
		for(int i=head[x];i;i=next[i]){
			int y=to[i];
			if(dis[y]>dis[x]+v[i]){
				dis[y]=dis[x]+v[i];
				q.push(node(y,dis[y]));
			}
		}
	}
	printf("%d\n",min(dis[n],dis[2*n]));
	return 0;
}
/*
题意：
N 个虫洞,M 条单向跃迁路径。从一个虫洞沿跃迁路径到另一个虫洞需要
消耗一定量的燃料和 1 单位时间。虫洞有白洞和黑洞之分。设一条跃迁路径两端
的虫洞质量差为 delta。
1.从白洞跃迁到黑洞,消耗的燃料值减少 delta,若该条路径消耗的燃料值
变为负数的话,取为 0。
2.从黑洞跃迁到白洞,消耗的燃料值增加 delta。
3.路径两端均为黑洞或白洞,消耗的燃料值不变化。
作为压轴题,自然不会是如此简单的最短路问题,所以每过 1 单位时间黑
洞变为白洞,白洞变为黑洞。在飞行过程中,可以选择在一个虫洞停留 1 个单
位时间,如果当前为白洞,则不消耗燃料,否则消耗 s[i]的燃料。现在请你求出
从虫洞 1 到 N 最少的燃料消耗,保证一定存在 1 到 N 的路线。




思路：
考虑把一个点看成一黑一白两个点，跑一遍dij即可
*/
