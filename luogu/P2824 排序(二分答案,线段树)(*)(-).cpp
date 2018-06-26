#include<bits/stdc++.h>
using namespace std;
const int maxn=30010,maxm=30010;
#define ls o<<1,l,mid
#define rs o<<1|1,mid+1,r
int ans;
int t[maxn<<2],tag[maxn<<2],a[maxn];
int n,m;
void maintain(int o){
	t[o]=t[o<<1]+t[o<<1|1];
}
void build(int o,int l,int r){
	tag[o]=-1;
	if(l==r){
		t[o]=a[l]>=ans?1:0;
		return ;
	}
	int mid=(l+r)>>1;
	build(ls);build(rs);
	maintain(o);
}
void pushdown(int o,int l,int r){
	if(tag[o]==-1)return ;
	int mid=(l+r)>>1;
	tag[o<<1]=tag[o];t[o<<1]=(mid-l+1)*tag[o];
	tag[o<<1|1]=tag[o];t[o<<1|1]=(r-mid)*tag[o];
	tag[o]=-1;
}	
void upt(int o,int l,int r,int X,int Y,int v){
	if(X<=l&&r<=Y){
		tag[o]=v;
		t[o]=(r-l+1)*v;
		return ;
	}
/**/pushdown(o,l,r);
	int mid=(l+r)>>1;
	if(X<=mid)upt(ls,X,Y,v);
	if(Y>mid)upt(rs,X,Y,v);
	maintain(o);
}
int que(int o,int l,int r,int X,int Y){
	if(X<=l&&r<=Y){
		return t[o];
	}
/**/pushdown(o,l,r);
	int mid=(l+r)>>1,ret=0;
	if(X<=mid)ret+=que(ls,X,Y);
	if(Y>mid)ret+=que(rs,X,Y);
	return ret;
}
struct node{
	int x,y,z;
}q[maxm];
int QUE;
int ck(){
	build(1,1,n);
	for(int i=1;i<=m;++i){
		int tmp=que(1,1,n,q[i].y,q[i].z);
		upt(1,1,n,q[i].y,q[i].z,0);
		if(q[i].x==0){
			upt(1,1,n,q[i].z-tmp+1,q[i].z,1);
		}
		else {
			upt(1,1,n,q[i].y,q[i].y+tmp-1,1);
		}
	}
	return que(1,1,n,QUE,QUE);
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	int l=1,r=n;
	int ANS;
	for(int i=1;i<=m;++i){
		scanf("%d%d%d",&q[i].x,&q[i].y,&q[i].z);
	}
	scanf("%d",&QUE);
	while(l<=r){
		ans=(l+r)>>1;
		if(ck()){
			ANS=ans;l=ans+1;
		}
		else r=ans-1;
	}
	cout<<ANS<<endl;
	return 0;
}
/*
题意：
在2016年，佳媛姐姐喜欢上了数字序列。因而他经常研究关于序列的一些奇奇怪怪的问题，现在他在研究一个难题，需要你来帮助他。这个难题是这样子的：给出一个1到n的全排列，现在对这个全排列序列进行m次局部排序，排序分为两种：1:(0,l,r)表示将区间[l,r]的数字升序排序2:(1,l,r)表示将区间[l,r]的数字降序排序最后询问第q位置上的数字。

思路：
只有一次查询，考虑离线。
适当将信息模糊化，使得题目更容易处理。
二分一个答案，将原序列中大于等于这个答案的置为1，小于置成0。
这样使得排序操作更好处理，先query一下区间1的个数，根据升序降序，把1放在区间的一端。
最后看q位置是否为1，为1则表示该位置原数应大于等于答案，根据这个check即可。

debug：
两处pushdown的位置应在下面，因为有可能到了线段树最底层，pushdown中再找儿子就会RE，要先return掉。
*/
