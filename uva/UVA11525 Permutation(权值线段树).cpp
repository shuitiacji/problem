#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=100010;
int sz[4*maxn];
void maintain(int o){
	sz[o]=sz[o<<1]+sz[o<<1|1];
}	
void build(int o,int l,int r){
	if(l==r){sz[o]=1;return ;}
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
	maintain(o);
}
int ans;
void query(int o,int l,int r,int x){
	if(l==r){ans=l;sz[o]=0;return ;}
	int mid=(l+r)>>1;
	int tmp=sz[o<<1];
	if(x>tmp)query(o<<1|1,mid+1,r,x-tmp);
	else query(o<<1,l,mid,x);
	maintain(o);
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--){
		int k;
		scanf("%d",&k);
		build(1,1,k);
		for(int i=1;i<=k;++i){
			int x;
			scanf("%d",&x);
			query(1,1,k,x+1);
			printf("%d%c",ans,i<k?' ':'\n');
		}
	}
	return 0;
}
/*
题意：求1-k的排列中第n大的序列，题目给出n的计算方法：

n = si*(k-1)+s2*(k-2)...+sk*0!; 并给你s1-sk

思路：权值线段树加速康托展开
Debug：sz[o]写成sz[l](20行)
*/
