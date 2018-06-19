#include<bits/stdc++.h>
using namespace std;
#define max Max
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
const int maxn=4005;
int D,S;
inline int Max(int x,int y){return x>y?x:y;}
struct IN{
	int val[maxn],tag[maxn];
	inline void upt(int o,int l,int r,int x,int y,int v){
		val[o]=max(val[o],v);
		if(x<=l&&r<=y){
			tag[o]=max(tag[o],v);
			return ;
		}
		int mid=(l+r)>>1;
		if(x<=mid)upt(o<<1,l,mid,x,y,v);
		if(y>mid)upt(o<<1|1,mid+1,r,x,y,v);
	}
	inline int que(int o,int l,int r,int x,int y){
		if(x<=l&&r<=y){
			return val[o];
		}
		int mid=(l+r)>>1,ret=tag[o];
		if(x<=mid)ret=max(ret,que(o<<1,l,mid,x,y));
		if(y>mid)ret=max(ret,que(o<<1|1,mid+1,r,x,y));
		return ret;
	}
};
struct OUT{
	IN val[maxn],tag[maxn];
	inline void upt(int o,int l,int r,int x,int y,int X,int Y,int V){
		val[o].upt(1,1,S,X,Y,V);
		if(x<=l&&r<=y){
			tag[o].upt(1,1,S,X,Y,V);
			return ;
		}
		int mid=(l+r)>>1;
		if(x<=mid)upt(o<<1,l,mid,x,y,X,Y,V);
		if(y>mid)upt(o<<1|1,mid+1,r,x,y,X,Y,V);
	}
	inline int que(int o,int l,int r,int x,int y,int X,int Y){
		if(x<=l&&r<=y){
			return val[o].que(1,1,S,X,Y);
		}
		int mid=(l+r)>>1,ret=tag[o].que(1,1,S,X,Y);
		if(x<=mid)ret=max(ret,que(o<<1,l,mid,x,y,X,Y));
		if(y>mid)ret=max(ret,que(o<<1|1,mid+1,r,x,y,X,Y));
		return ret;
	}
}t;
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	D=read();S=read();++D;++S;
	int n=read();
	for(int i=1;i<=n;++i){
		int d=read(),s=read(),w=read(),x=read(),y=read();++x;++y;
		int tmp=t.que(1,1,D,x,x+d-1,y,y+s-1);
		t.upt(1,1,D,x,x+d-1,y,y+s-1,tmp+w);
	}
	printf("%d\n",t.que(1,1,D,1,D,1,S));
	return 0;
}
/*
题意：
给定一个矩阵，初始每个位置上的元素都是0，每次选择一个子矩形，将这个子矩形内的值修改为这个子矩形内的最大值+h，求最终所有位置上的最大值

思路：
二维线段树，需要区间修改。
对于二维来说，pushdown标记变得麻烦。
不用pushdown，路过那个节点，把它的tag贡献算进去即可
*/
