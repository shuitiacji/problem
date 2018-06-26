#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=100005;
int tag[maxn*4],val[maxn*4],ans;
int Min,Max;
struct node{
	int x,y,z;
}a[maxn];
void build(int o,int l,int r){
	tag[o]=0;val[o]=0;
	if(l==r)return ;
	int mid=l+((r-l)>>1);
	build(o<<1,l,mid);
	build((o<<1)|1,mid+1,r);
}
void pushdown(int o){
	if(tag[o]){
		tag[o<<1]=tag[o];val[o<<1]=tag[o];
		tag[(o<<1)|1]=tag[o];val[(o<<1)|1]=tag[o];
		tag[o]=0;
	}
}
void pushup(int o){
	val[o]=max(val[(o<<1)|1],val[o<<1]);
}
void update(int o,int l,int r,int x,int y,int z){
	if(tag[o]&&val[o]>z)return ;
	if(x<=l&&r<=y){
		if(val[o]<=z){
			ans+=r-l+1;
			tag[o]=z;
			val[o]=z;
			return ;
		}
	}
	if(l==r)return ;
	pushdown(o);
	int mid=l+((r-l)>>1);
	if(x<=mid)update(o<<1,l,mid,x,y,z);
	if(mid<y)update((o<<1)|1,mid+1,r,x,y,z);
	pushup(o);
}
void init(){
	ans=0;
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int t,n;
	scanf("%d",&t);
	while(t--){
		init();
		scanf("%d",&n);
		Max=0;Min=0x3f3f3f3f;
		for(int i=1;i<=n;++i){
			scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
			Max=max(a[i].y,Max);
			Min=min(a[i].x,Min);
		}
		build(1,Min,Max);
		for(int i=1;i<=n;++i)update(1,Min,Max,a[i].x,a[i].y-1,a[i].z);
		printf("%d\n",ans);
	}
	scanf("%d",&n);
	return 0;
}
/*
题意：依次建n个建筑， 每个建筑有3个信息，宽度：[l, r]， 和高度h， 要求求出每个建筑刚建完时最高的部分的区间长度之和。











debug：这里是区间问题，用树中每一个点当作一个长度为1的区间，如i这个点，当成i，i+1
*/
