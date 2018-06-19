#include<bits/stdc++.h>
using namespace std;
#define pb push_back
int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
const int maxn=100005;
struct edge{
	int x,y;
}e[maxn];
struct fou{
	int x,y,z,id;
};
struct node{
	int l,r;
	vector<fou> q;
};
queue<node> Q;
int ans[maxn],f[maxn],sz[maxn];
int find(int x){
	int r=x;
	while(r!=f[r])r=f[r];
	int i=x,j;
	while(i!=r){
		j=f[i];
		f[i]=r;
		i=j;
	}
	return r;
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n=read(),m=read();
	for(int i=1;i<=n;++i)f[i]=i,sz[i]=1;
	for(int i=1;i<=m;++i){
		e[i]={read(),read()};
	}
	int qs=read();
	node tmp;
	for(int i=1;i<=qs;++i){
		tmp.q.pb({read(),read(),read(),i});
	}
	tmp.l=0;tmp.r=m;
	Q.push(tmp);
	int tot=0;
	while(!Q.empty()){
		node u=Q.front();Q.pop();
		if(u.r-u.l==1){
			for(int i=0;i<u.q.size();++i){
				ans[u.q[i].id]=u.r;
			}
			continue;
		}
		int mid=(u.l+u.r)>>1;
		if(tot>mid){
			for(int i=1;i<=n;++i)f[i]=i,sz[i]=1;
			tot=0;
		}
		for(int i=tot+1;i<=mid;++i){
			int fx=find(e[i].x),fy=find(e[i].y);
			if(fx!=fy){
				f[fx]=fy;
				sz[fy]+=sz[fx];
				sz[fx]=0;
			}
		}
		tot=mid;
		vector<fou> tmp1,tmp2;
		for(int i=0;i<u.q.size();++i){
			int sum=sz[find(u.q[i].x)];
			if(find(u.q[i].x)!=find(u.q[i].y))sum+=sz[find(u.q[i].y)];
			if(u.q[i].z<=sum)tmp1.pb(u.q[i]);
			else tmp2.pb(u.q[i]);
		}
		Q.push({u.l,mid,tmp1});
		Q.push({mid,u.r,tmp2});
	}
	for(int i=1;i<=qs;++i)printf("%d\n",ans[i]);
	return 0;
}
/*
题意：
一个n点无向图，每条边从1编号到m，给出q组询问，包含3个值x，y，z，从x与y开始任意移动，总遍历的点数要>=z（包括x，y，若两点都走到这个点只算一次），使得经过的边中编号最大的尽可能小，输出这个值。

思路：
若正向思考，怎么都逃不出dfs的思路，考虑反向思考。
对于点对，考虑最大编号为i能否满足有z个点。
显然最大值最小，很容易想到二分答案。
将1->i的边，用并查集维护一下加边，看x，y分别在的联通块大小。
这样对每个询问二分，还要并查集加边，O(qmlogm)。

考虑重复运算主要在并查集重复加边加了很多次，考虑把所有询问离线一起二分处理。
用一个三元组{l,r,q{Q1,Q2,Q3,...,}}，分别表示在(l,r}的答案范围内，有Q1,Q2,...,这些个询问的点对满足遍历超过z个。
把这些三元组放进一个队列，每次取队首，进行二分答案：
1.r-l==1，二分到了，把q中每个的答案赋值一下。
2.mid=(l+r)>>1,
对于现在并查集若边数>mid,进行暴力重构。
边数小于mid，加边。
3.对当前q中的每个询问在答案mid下，看满不满足条件，并分成两类，定义新的两个三元组压进队中（这个过程也可以不用队列(BFS)，换成DFS）

分析一下复杂度
首先是logm个状态量，乘上重构并查集(m)，询问分类(q)，O((m+q)logm)
*/
