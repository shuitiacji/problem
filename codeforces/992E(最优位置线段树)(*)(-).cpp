#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define ls o<<1,l,mid
#define rs o<<1|1,mid+1,r
int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
const int maxn=2e5+10;
int Sum[maxn<<2],Max[maxn<<2],a[maxn];
void maintain(int o){
	Sum[o]=Sum[o<<1]+Sum[o<<1|1];
	Max[o]=max(Max[o<<1],Max[o<<1|1]);
}
void upt(int o,int l,int r,int p,int v){
	if(l==r){
		Sum[o]=Max[o]=v;
		return ;
	}
	int mid=(l+r)>>1;
	if(p<=mid)upt(ls,p,v);
	else upt(rs,p,v);
	maintain(o);
}
int que(int o,int l,int r,int x,int y) {
	if(x<=l&&r<=y){
		return Sum[o];
	}
	int mid=(l+r)>>1,ret=0;
	if(x<=mid)ret+=que(ls,x,y);
	if(y>mid)ret+=que(rs,x,y);
	return ret;
}
int tmp;
void find(int o,int l,int r,int x,int y,int v){
	if(tmp!=-1)return ;
	if(l==r){tmp=l;return ;}
	int mid=(l+r)>>1;
	if(x<=mid&&Max[o<<1]>=v)find(ls,x,y,v);
	if(y>mid&&Max[o<<1|1]>=v)find(rs,x,y,v);
}
main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n,q;
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;++i){
		a[i]=read();
		upt(1,1,n,i,a[i]);
	}
	for(int i=1;i<=q;++i){
		int x=read(),y=read();
		upt(1,1,n,x,y);
		a[x]=y;
		if(a[1]==0){puts("1");continue;}
		int j=1,fg=-1;
		while(j<n){
			tmp=-1;
			int TMP=que(1,1,n,1,j);
			find(1,1,n,j+1,n,TMP);	
			if(tmp==-1)break;
			if(a[tmp]==que(1,1,n,1,tmp-1)){fg=tmp;break;}
			j=tmp;
		}
		printf("%lld\n",fg);
	}
	return 0;
}
/*
思路：
同之前的做法，因为a[i]=sum[i-1],又sum单调，所以如果i满足条件则a[i]>sum[j](j<i)
不同的是，我们不利用sum单调性来倍增从而在sum序列上二分，我们可以直接在a序列上查找。
但a不是单调的，无法直接二分，我们怎么做呢。
考虑建一个max线段树，每次当儿子的max>=当前询问的值且询问的区间在其中就递归下去继续做，否则不递归，查找到第一个叶子就结束。为保证找到最左的，我们要优先递归左儿子。
这个操作的复杂度是log的，因为走一次到叶子节点是log的，一个区间最多划分成log个且区间走的复杂是log同区间加法的证明，O(logn+logn)
同时这个做法还有个好处，就是因为a是动态的，直接在线段树上查找刚好可以省去先前方法中每次都去查一下sum的log，虽然失去了一边倍增一边二分的好处，但省去了动态查询的时间。
这种非单调动态序列，要求支持快速查找大于or小于一个数的位置，可以考虑这种方法。

debug:
long long 忘开
*/
