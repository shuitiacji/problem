#include<bits/stdc++.h>
using namespace std;
const int maxn=100100;
typedef long long LL;
LL a[maxn],sum[maxn<<2],squ[maxn<<2],tag[maxn<<2];
#define ls o<<1,l,mid
#define rs o<<1|1,mid+1,r
struct pa{
	LL x,y;
};
void maintain(int o){
	sum[o]=sum[o<<1]+sum[o<<1|1];
	squ[o]=squ[o<<1]+squ[o<<1|1];
}
void pushdown(int o,int l,int r,int mid){
/**/if(l==r||!tag[o])return ;
/**/squ[o<<1]+=2LL*tag[o]*sum[o<<1]+tag[o]*tag[o]*(mid-l+1);
/**/sum[o<<1]+=tag[o]*(mid-l+1);
	tag[o<<1]+=tag[o];
/**/squ[o<<1|1]+=2LL*tag[o]*sum[o<<1|1]+tag[o]*tag[o]*(r-mid);
/**/sum[o<<1|1]+=tag[o]*(r-mid);
	tag[o<<1|1]+=tag[o];
	tag[o]=0;
}
void build(int o,int l,int r){
	if(l==r){
		sum[o]=a[l];
		squ[o]=a[l]*a[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(ls);build(rs);
	maintain(o);
}
void upt(int o,int l,int r,int X,int Y,LL v){
	int mid=(l+r)>>1;
	pushdown(o,l,r,mid);
	if(X<=l&&r<=Y){
		int sz=r-l+1;
/**/	squ[o]+=2LL*v*sum[o]+v*v*sz;
/**/	sum[o]+=v*sz;
		tag[o]+=v;
		return ;
	}
	if(X<=mid)upt(ls,X,Y,v);
	if(Y>mid)upt(rs,X,Y,v);
	maintain(o);
}
pa que(int o,int l,int r,int X,int Y){
	int mid=(l+r)>>1;
	pushdown(o,l,r,mid);
	if(X<=l&&r<=Y){
		pa tmp={sum[o],squ[o]};
		return tmp;
	}
	pa tmp1,tmp2;
	LL ret1=0,ret2=0;
	if(X<=mid){
		tmp1=que(ls,X,Y);
		ret1+=tmp1.x;
		ret2+=tmp1.y;
	}
	if(Y>mid){
		tmp2=que(rs,X,Y);
		ret1+=tmp2.x;
		ret2+=tmp2.y;
	}
	pa TMP={ret1,ret2};
	return TMP;
}
LL gcd(LL x,LL y){
	if(x==0)return y;
	return gcd(y%x,x);
}
void pri(LL x,LL y){
	LL tmp=gcd(x,y);
	printf("%lld/%lld\n",x/tmp,y/tmp);
}
LL read(){
	LL x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int main(){
	freopen("classroom.in","r",stdin);
	freopen("classroom.out","w",stdout);
	int n=read(),m=read();
	for(int i=1;i<=n;++i)a[i]=read();
	build(1,1,n);
	for(int i=1;i<=m;++i){
		int z=read(),x=read(),y=read();
		if(z==1){
			int d=read();
			upt(1,1,n,x,y,d);
		}
		if(z==2){
			pri(que(1,1,n,x,y).x,y-x+1);
		}
		if(z==3){
			pa tmp=que(1,1,n,x,y);
			LL sz=y-x+1;
			pri(tmp.y*sz-tmp.x*tmp.x,sz*sz);
		}
	}
	return 0;
}
/*
题意：
在接受借教室请求的 n 天中，第 i 天剩余的教室为 ai个。作为大学借教室服
务的负责人，你需要完成如下三种操作共 m 次：
① 第 l 天到第 r 天，每天被归还 d 个教室。
② 询问第 l 天到第 r 天教室个数的平均数。
③ 询问第 l 天到第 r 天教室个数的方差。

思路：
线段树维护区间和与区间平方和，推一下公式即可

debug:
公式一定要推对
16行注意一下l==r
*/
