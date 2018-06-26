#include<bits/stdc++.h>
using namespace std;
const int maxn=10100;
#define ls o<<1,l,mid
#define rs o<<1|1,mid+1,r
#define pb push_back
bitset<maxn> b[maxn<<2];
vector<int> a[maxn<<2];
void upt(int o,int l,int r,int X,int Y,int v){
	if(X<=l&&r<=Y){
		a[o].pb(v);
		return ;
	}
	int mid=(l+r)>>1;
	if(X<=mid)upt(ls,X,Y,v);
	if(Y>mid)upt(rs,X,Y,v);
}
void query(int o,int l,int r){
	if(l==r){
		b[o][0]=1;
		for(int i=0;i<a[o].size();++i){
			b[o]=(b[o]<<a[o][i])|b[o];
		}
		return ;
	}
	int mid=(l+r)>>1;
	query(ls);query(rs);
	b[o]=b[o<<1]|b[o<<1|1];
	for(int i=0;i<a[o].size();++i){
		b[o]=(b[o]<<a[o][i])|b[o];
	}
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=q;++i){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		upt(1,1,n,x,y,z);
	}
	query(1,1,n);
	int ans=0;
	for(int i=1;i<=n;++i)if(b[1][i])++ans;
	printf("%d\n",ans);
	for(int i=1;i<=n;++i)if(b[1][i])printf("%d ",i);
	return 0;
}
/*
题意：给你n个0，给你一些区间加法操作，你可以从中任选一些操作，得到一个区间最大值，现求这样能得到哪些在1-n范围内的可能的最大值。

思路：
首先发现对于一个1-n内的值，只要存在一些操作能凑出它，它就可以为答案的一个，不需要考虑什么最大值，因为操作任选，完全可以只选凑出它的操作。
再发现这个只求1-n范围内，明显的引导我们去用bitset。
可以打个线段树维护一下区间加法，用一个bitset:b[o][i]==1表示在o号线段树节点i值能否凑出。
*/
