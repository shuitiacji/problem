/*#include<bits/stdc++.h>
using namespace std;
const int maxn=200010;
struct node{
	int l,r,id,pos;
	bool operator < (const node &b) const{
		if(pos!=b.pos)return pos<b.pos;
		if(pos&1)return r>b.r;
		return r<b.r;
	}
}que[maxn];
int ans,a[maxn],c[maxn],Ans[maxn];
void add(int p){
	c[a[p]]++;
	if(ans==a[p])while(c[ans])ans++;
}
void remove(int p){
	c[a[p]]--;
	if(c[a[p]]==0&&ans>a[p])ans=a[p];
}
int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int main(){
	freopen("mex.in","r",stdin);
	freopen("mex.out","w",stdout);
	int n=read(),q=read();;
	int sz=sqrt(n);
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<=q;++i){
		que[i].l=read();que[i].r=read();
		que[i].id=i;que[i].pos=que[i].l/sz;
	}
	sort(que+1,que+q+1);
	int L=1,R=0;
	for(int i=1;i<=q;++i){
		while(R<que[i].r)add(++R);
		while(R>que[i].r)remove(R--);
		while(L<que[i].l)remove(L++);
		while(L>que[i].l)add(--L);
		Ans[que[i].id]=ans;
	}
	for(int i=1;i<=q;++i)printf("%d\n",Ans[i]);
	return 0;
}
//dubug:42,43,<与>打反
*/

#include<bits/stdc++.h>
using namespace std;
#define next Next
#define ls o<<1,l,mid
#define rs o<<1|1,mid+1,r
const int maxn=200010;
struct node{
	int l,r,id;
	bool operator < (const node &b) const{
		return l<b.l;
	}
}que[maxn];
int tag[maxn*4],a[maxn],last[maxn],next[maxn],ans[maxn],T[maxn],cnt[maxn];
void pushdown(int o){
	if(tag[o]==0x3f3f3f3f)return ;
	if(tag[o<<1]>tag[o]){
		tag[o<<1]=tag[o];
	}
	if(tag[o<<1|1]>tag[o]){
		tag[o<<1|1]=tag[o];
	}
	tag[o]=0x3f3f3f3f;
}
void upt(int o,int l,int r,int X,int Y,int v){
	if(X<=l&&r<=Y){
		tag[o]=min(tag[o],v);
		return ;
	}
	pushdown(o);
	int mid=(l+r)>>1;
	if(X<=mid)upt(ls,X,Y,v);
	if(Y>mid)upt(rs,X,Y,v);
}
int query(int o,int l,int r,int p){
	if(l==r)return tag[o];
	pushdown(o);
	int mid=(l+r)>>1;
	if(p<=mid)query(ls,p);
	else query(rs,p);
}
void build(int o,int l,int r){
	if(l==r){tag[o]=T[l];return ;}
	int mid=(l+r)>>1;
	build(ls);build(rs);
}
int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int main(){
	freopen("mex.in","r",stdin);
	freopen("mex.out","w",stdout);
	memset(tag,0x3f,sizeof(tag));
	memset(cnt,0,sizeof(cnt));
	int n=read(),q=read();
	int tmp=0;
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<=n;++i){
		next[last[a[i]]]=i;
		last[a[i]]=i;
	}
	for(int i=1;i<=n;++i){
		cnt[a[i]]++;
		while(cnt[tmp]!=0){tmp++;}
		T[i]=tmp;
	}
	build(1,1,n);
	for(int i=1;i<=q;++i){
		que[i].l=read();que[i].r=read();
		que[i].id=i;
	}
	sort(que+1,que+q+1);
	int now=1;
	for(int i=1;i<=q;++i){
		while(now<que[i].l){
			if(!next[now])next[now]=n+1;
			upt(1,1,n,now+1,next[now]-1,a[now]);
			now++;
		}
		ans[que[i].id]=query(1,1,n,que[i].r);
	}
	for(int i=1;i<=q;++i)printf("%d\n",ans[i]);
	return 0;
}
/*
题意：给你一列数，询问区间l，r，求非负整数中不在l，r数的集合中的最小值。
思路：
首先要想到离线询问
1.傻逼莫队，add与remove暴力操作（无法O（1）），玄学复杂度（取决于数据卡不卡）
2.正解
先考虑暴力，若1个端点不变，for一遍右端点可以O(n)出解，如可以预处理出所有(1,1),(1,2),...,(1,n)的答案，这样枚举两个端点可以n^2暴力
现在考虑左端点不暴力枚举(也可以说是算左端点左边的最小值)(先预处理出(1,1),(1,2),...,(1,n),相当于预处理右端点，因为(1,i)肯定包含了i右边的最小值，只差左边的了)
如何不暴力枚举左端点？若把询问区间按左端点排序，如果能快速从上个区间转移到这个区间,就能够做到。
考虑从(i,j)转移到(i+1,j)，因为a[i]空出来了，对于右端点在(i+1,next[i]-1)中的询问，它的答案可以取a[i]（只是可以，若有更小的就不取）(其中next[i]表示在点i之后第一个与a[i]相同的点的位置，这个也是可以预处理出的)
这个转移操作即相当区间取min，然后对于询问的r单点查询。
线段树即可，加上每次+1的转移左端点，nlogn
*/

