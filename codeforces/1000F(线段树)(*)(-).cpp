#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
int pre[maxn],las[maxn],a[maxn],ans[maxn];
#define inf 0x3f3f3f3f
struct node{
	int x,y;
	bool operator < (const node &b) const{
		return x<b.x;
	}
};
node t[maxn<<2];
vector<node> Q[maxn];
#define ls o<<1,l,mid
#define rs o<<1|1,mid+1,r
void upt(int o,int l,int r,int p,node v){
	if(l==r){
		t[o]=v;
		return ;
	}
	int mid=(l+r)>>1;
	if(p<=mid)upt(ls,p,v);
	else upt(rs,p,v);
	t[o]=min(t[o<<1],t[o<<1|1]);
}
node que(int o,int l,int r,int x,int y){
	if(x<=l&&r<=y){
		return t[o];
	}
	int mid=(l+r)>>1;
	node tmp=(node){inf,inf};
	if(x<=mid)tmp=min(tmp,que(ls,x,y));
	if(y>mid)tmp=min(tmp,que(rs,x,y));
	return tmp;
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		if(las[a[i]])pre[i]=las[a[i]];
		las[a[i]]=i;
	}
	int q;scanf("%d",&q);
	for(int i=1;i<=q;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		Q[y].push_back((node){x,i});
	}
	for(int i=1;i<=n;++i){
		if(pre[i]){
			upt(1,1,n,pre[i],(node){inf,inf});
		}
		upt(1,1,n,i,(node){pre[i],a[i]});
		for(int j=0;j<Q[i].size();++j){
			node tmp=que(1,1,n,Q[i][j].x,i);
			if(tmp.x<Q[i][j].x){
				ans[Q[i][j].y]=tmp.y;
			}
		}
	}
	for(int i=1;i<=q;++i)printf("%d\n",ans[i]);
	return 0;
}
/*
题意：
给你n个数（值有重复），q个查询，每次询问在区间l,r之间存不存在值只出现一次的数，有多个随便输出一个。

思路：
一个区间可能有很多存在一次的数，我们真的随便输出一个吗。
适当对题目加上一些约束方便我们处理。
比如说，我们对每个区间都取最优的那个数。
最优，当然是最不可能出现多次，即前面后面与它一样的离得越远越好，两个同时满足不太好，我们先最优一个，在本题中就是这段区间中pre值（就是与这个数相等的上一个数的位置）最小，因为这样更容易满足条件，因为上个数离这个数越远就越不可能与这个数在一个询问区间中。
同时我们发现，这个最小值如果都不满足的话，就没有其他数满足了。
但这个东西有个问题，我们只关心了pre，没有关心nxt，如果a[i]==a[j]，i<j，且都在这个区间的话，若最小值是i的话，也不满足题意。
用扫描线来离线询问来维护nxt，我们可以一个一个把数放到线段树中，值就为pre，维护区间最小值，同时把它的pre从线段树中去除，碰到一个询问的右端点，就在线段树中查一下该区间的最小值。

debug:
用(node){}替代node{}
*/
