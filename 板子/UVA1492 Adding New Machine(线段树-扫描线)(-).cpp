#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;
const int maxn=50100;
struct Node{
	int l,r,h,v;
}seg[2*maxn],node[8*maxn];
int N,M;
vector<int> vec,bset;
int x[maxn][2],y[maxn][2];
void add(int i,int l,int r,int h,int v){
	seg[i]=(Node){l,r,h,v};
	vec.push_back(l);
	vec.push_back(r);
}
void hashinit(){
	sort(vec.begin(),vec.end());
	bset.push_back(vec[0]);
	for(int i=1;i<vec.size();++i){
		if(vec[i]!=vec[i-1])bset.push_back(vec[i]);
	}
}
void build(int o,int l,int r){
	node[o]=(Node){l,r,0,0};
	if(l==r)return ;
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
}
int find(int x){
	return lower_bound(bset.begin(),bset.end(),x)-bset.begin();
}
void pushup(int o){
	if(node[o].h)node[o].v=bset[node[o].r+1]-bset[node[o].l];
	else if(node[o].l==node[o].r)node[o].v=0;
	else node[o].v=node[o<<1].v+node[o<<1|1].v;
}
void ins(int o,int l,int r,int x){
	if(l<=node[o].l&&node[o].r<=r){
		node[o].h+=x;
		pushup(o);
		return ;
	}
	int mid=(node[o].l+node[o].r)>>1;
	if(l<=mid)ins(o<<1,l,r,x);
	if(r>mid)ins(o<<1|1,l,r,x);
	pushup(o);
}
int cmp(Node x,Node y){
	return x.h<y.h;
}
LL sol(int x[maxn][2],int y[maxn][2],int R,int C){
	if(N==0)return 1LL*(C-M+1)*R;
	vec.clear();
	bset.clear();
	int n=0;
	for(int i=1;i<=N;++i){
		add(++n,max((int)(x[i][0]-M),0),x[i][1],y[i][0]-1,1);
		add(++n,max((int)(x[i][0]-M),0),x[i][1],y[i][1],-1);
	}
	add(++n,max((int)(C-M+1),0),C,0,1);
	add(++n,max((int)(C-M+1),0),C,R,-1);
	hashinit();
	int sz=bset.size()-2;
	build(1,0,sz);
	LL ret=0;
	sort(seg+1,seg+n+1,cmp);
	for(int i=1;i<=n;++i){
		LL tmp=node[1].v;
		if(i>1)ret+=1LL*(seg[i].h-seg[i-1].h)*tmp;
		ins(1,find(seg[i].l),find(seg[i].r)-1,seg[i].v);
	}
	return 1LL*R*C-ret;
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int W,H;
	while(scanf("%d%d%d%d",&W,&H,&N,&M)==4){
		for(int i=1;i<=N;++i){
			scanf("%d%d%d%d",&x[i][0],&y[i][0],&x[i][1],&y[i][1]);
		}
		LL ans=sol(y,x,W,H)+sol(x,y,H,W);
		if(M==1)ans>>=1;
		printf("%lld\n",ans);
	}
	return 0;
}
/*
题意：在一个R∗C矩阵上有N台旧的机器，给定每个机器的占地，现在要添加一台1∗M的机器，问有多少种摆放方法。


debug：
x.x
57,74,77行忘开LL,87行x，y搞反。

*/
