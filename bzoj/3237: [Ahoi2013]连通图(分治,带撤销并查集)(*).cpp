#include<bits/stdc++.h>
using namespace std;
/**/ 
#define div DDDIV
const int maxn=200010,maxm=200010,maxk=400010;
int f[maxn],sz[maxn],ans[maxk],vis[maxm],VIS[maxm];
struct node{
	int x,y;
}e[maxm];
vector<int> q[maxk];
int n,m;
int find(int x){
	int r=x;
	while(f[r]!=r)r=f[r];
	return r;
}
int top;
pair<int,int> sta[maxm];
void rec(int x){
	while(top>x){
		sz[sta[top].first]-=sz[sta[top].second];
		f[sta[top].second]=sta[top].second;
		--top;
	}
}
void uni(int x,int y){
	x=find(x);y=find(y);
/**/if(x==y)return ;
	if(sz[y]>sz[x])swap(x,y);
	sta[++top]=make_pair(x,y);
	sz[x]+=sz[y];
	f[y]=x;
}
void div(int l,int r){
	if(l==r){
		if(sz[find(1)]==n){
			ans[l]=1;
		}
		else ans[l]=0;
		return ;
	}
	int mid=(l+r)>>1,tmp=top;
	for(int i=l;i<=mid;++i){
		for(int j=0;j<q[i].size();++j){
			VIS[q[i][j]]=1;
		}
	}
	for(int i=mid+1;i<=r;++i){
		for(int j=0;j<q[i].size();++j){
			if(VIS[q[i][j]])continue;
			uni(e[q[i][j]].x,e[q[i][j]].y);
		}
	}
	for(int i=l;i<=mid;++i){
		for(int j=0;j<q[i].size();++j){
			VIS[q[i][j]]=0;
		}
	}
	div(l,mid);
	rec(tmp);
	for(int i=mid+1;i<=r;++i){
		for(int j=0;j<q[i].size();++j){
			VIS[q[i][j]]=1;
		}
	}
	for(int i=l;i<=mid;++i){
		for(int j=0;j<q[i].size();++j){
			if(VIS[q[i][j]])continue;
			uni(e[q[i][j]].x,e[q[i][j]].y);
		}
	}
	for(int i=mid+1;i<=r;++i){
		for(int j=0;j<q[i].size();++j){
			VIS[q[i][j]]=0;
		}
	}
	div(mid+1,r);
	rec(tmp);
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)f[i]=i,sz[i]=1;
	for(int i=1;i<=m;++i){
		scanf("%d%d",&e[i].x,&e[i].y);
	}
	int k;
	scanf("%d",&k);
	for(int i=1;i<=k;++i){
		int x;
		scanf("%d",&x);
		for(int j=1;j<=x;++j){
			int y;scanf("%d",&y);
			q[i].push_back(y);
			vis[y]=1;
		}
	}
	for(int i=1;i<=m;++i){
		if(!vis[i]){
			uni(e[i].x,e[i].y);
		}
	}
	div(1,k);
	for(int i=1;i<=k;++i){
		if(ans[i])puts("Connected");
		else puts("Disconnected");
	}
	return 0;
}
/*
题意：
给你一个n点m边的无向图，给你k个边的集合（集合元素不超过c），求每个集合中的边在原图中去掉后，原图是否连通。

思路：
这种删边加边多组询问图连通性的题，可以套路分治+可撤销并查集做.
首先可以把删边变加边操作，同时发现如果对每次操作单独处理，非常吃亏，因为重复建边会浪费很多效率。
借鉴整体二分的思想，把所有操作一起分治做，来减少重复并查集加边操作。
因为处理左半边时，要加上右半边的值，处理右半边又要减去右，加上左。
这里涉及到并查集的撤销操作，可以用栈把每次的边存进取，撤销就不断pop且在并查集中修改。
为维护形态，无法路径压缩，只能按秩合并保持log的复杂度。
O(kc*log(m)*log(k))

debug:
1.div是关键字，以后少用。
2.28行忘写。
*/
