#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=400005;
int tot,sz,n;
LL cnt1,cnt2,ans;
int v[maxn],l[maxn],r[maxn],ls[maxn<<4],rs[maxn<<4],sum[maxn<<4],rt[maxn];
inline LL Min(LL x,LL y){return x<y?x:y;}
inline void treeread(int x){
	scanf("%d",&v[x]);
	if(!v[x]){
		l[x]=++tot;
		treeread(l[x]);
		r[x]=++tot;
		treeread(r[x]);
	}
}
inline void build(int &o,int l,int r,int v){
	if(!o)o=++sz;
	sum[o]++;
	if(l==r)return ;
	int mid=(l+r)>>1;
	if(v<=mid)build(ls[o],l,mid,v);
	else build(rs[o],mid+1,r,v);
}
inline void pushup(int x){sum[x]=sum[ls[x]]+sum[rs[x]];}
inline int merge(int x,int y){
	if(!x)return y;
	if(!y)return x;
	cnt1+=1LL*sum[rs[x]]*sum[ls[y]];
	cnt2+=1LL*sum[ls[x]]*sum[rs[y]];
	ls[x]=merge(ls[x],ls[y]);
	rs[x]=merge(rs[x],rs[y]);
	pushup(x);
	return x;
}	
inline void solve(int x){
	if(!x)return ;
	solve(l[x]);solve(r[x]);
	if(!v[x]){
		cnt1=0;cnt2=0;
		rt[x]=merge(rt[l[x]],rt[r[x]]);
		ans+=Min(cnt1,cnt2);
	}
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d",&n);
	++tot;
	treeread(1);
	for(int i=1;i<=tot;++i)
		if(v[i])build(rt[i],1,n,v[i]);
	solve(1);
	cout<<ans<<endl;
	return 0;
}
/*
题意：
现在有一棵二叉树，所有非叶子节点都有两个孩子。在每个叶子节点上有一个权值(有n个叶子节点，满足这些权值为1..n的一个排列)。可以任意交换每个非叶子节点的左右孩子。

要求进行一系列交换，使得最终所有叶子节点的权值按照中序遍历写出来，逆序对个数最少。

思路：
子树内的交换不会对子树外的造成影响。
先考虑暴力，递归下去，枚举此时左子树的点与右子树的点，每次比较暴力算一下。
考虑优化这个比较的过程，对左子树与右子树分别建一颗权值线段树，线段树递归下去算即可。
只需要合并线段树即可，可以在算答案的时候顺便合并一下。
*/
