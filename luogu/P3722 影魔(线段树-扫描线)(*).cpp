#include<bits/stdc++.h>
using namespace std;
const int maxn=200100;
typedef long long LL;
struct node{
	int l,r,v,tmp;
};
struct Q{
	int x,id;
};
struct tree{
	LL v,tag;
}t[maxn*4];
vector<node> vec[maxn];
vector<Q> que1[maxn],que2[maxn];
LL Ans[maxn];
int sta[maxn],L[maxn],R[maxn];
int k[maxn];
void pushdown(int o,int l,int mid,int r){
	t[o<<1].v+=1LL*(mid-l+1)*t[o].tag;t[o<<1].tag+=t[o].tag;
	t[o<<1|1].v+=1LL*(r-mid)*t[o].tag;t[o<<1|1].tag+=t[o].tag;
	t[o].tag=0;
}
void maintain(int o){
	t[o].v=t[o<<1].v+t[o<<1|1].v;
}
void update(int o,int l,int r,int x,int y,int v){
	if(y<l||x>r)return ;
	if(x<=l&&r<=y){
		t[o].v+=1LL*(r-l+1)*v;
		t[o].tag+=1LL*v;
		return ;
	}
	int mid=(l+r)>>1;
	if(t[o].tag)pushdown(o,l,mid,r);
	if(x<=mid)update(o<<1,l,mid,x,y,v);
	if(y>mid)update(o<<1|1,mid+1,r,x,y,v);
	maintain(o);
}
LL query(int o,int l,int r,int x,int y){
	if(y<l||x>r)return 1LL*0;
	if(x<=l&&r<=y){
		return t[o].v;
	}
	int mid=(l+r)>>1;
	LL ret=0;
	if(t[o].tag)pushdown(o,l,mid,r);
	if(x<=mid)ret+=query(o<<1,l,mid,x,y);
	if(y>mid)ret+=query(o<<1|1,mid+1,r,x,y);
	return ret;
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n,m,p1,p2;
	scanf("%d%d%d%d",&n,&m,&p1,&p2);
	int top=0;
	k[0]=k[n+1]=0x3f3f3f3f;
	sta[top]=0;
	for(int i=1;i<=n;++i)
		scanf("%d",&k[i]);
	for(int i=1;i<=n;++i){
		while(k[sta[top]]<k[i])
			--top;
		L[i]=sta[top];
		sta[++top]=i;
	}
	top=0;
	sta[top]=n+1;
	for(int i=n;i>=1;--i){
		while(k[sta[top]]<k[i])
			--top;
		R[i]=sta[top];
		sta[++top]=i;
	}
	for(int i=1;i<=n;++i){
		vec[L[i]].push_back((node){i+1,R[i]-1,p2,i});
		vec[R[i]].push_back((node){L[i]+1,i-1,p2,i});
		vec[R[i]].push_back((node){L[i],L[i],p1,i});
		if(i>1)vec[i].push_back((node){i-1,i-1,p1,i});
	}
	for(int i=1;i<=m;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		que1[x].push_back((Q){y,i});
		que2[y].push_back((Q){x,i});
	}
	for(int i=0;i<=n;++i){
		for(int j=0;j<vec[i].size();++j){
			update(1,1,n,vec[i][j].l,vec[i][j].r,vec[i][j].v);
		}
		for(int j=0;j<que1[i+1].size();++j){
			Ans[que1[i+1][j].id]=query(1,1,n,i+1,que1[i+1][j].x);
		}
		for(int j=0;j<que2[i].size();++j){
			Ans[que2[i][j].id]=query(1,1,n,que2[i][j].x,i)-Ans[que2[i][j].id];
		}
	}
	for(int i=1;i<=m;++i)printf("%lld\n",Ans[i]);
	return 0;
}
/*
题意：给你一个N的排列，对于区间[l,r]，若l和r为区间最大值与次大值，则对区间有p1的贡献；若l和r中一个位最大值，一个不为次大值，则有p2的贡献。有m个查询[l,r]，查询区间[l,r]内的贡献



思路：可将每个点左边比它大的第一个和右边比它大的第一个预处理出来记为L[i]与R[i]，这样：1.L[i]与R[i]构成点对，中间的数都比他们小，产生p1贡献(给R[i]打上标记)。
2.L[i]+1——i-1中的每个点与R[i]构成点对，在加上中间的i就可以满足题意，产生p2贡献(给R[i]打上标记)
3.同理i+1——R[i]-1与L[i]构成点对产生p2贡献(给L[i]打上标记)
再将询问离线处理，扫描线一遍扫过去，碰到标记点，给相关的点用线段树区间加一下，碰到询问分两次，一次是询问刚开始，先线段树查一下区间，因为这时这个区间的标记点没有处理，所以此时的结果是不在此区间的标记点产生的，要存下来减掉，第二次，再query一下，并减掉第一次的多余的，得到答案。


debug：因为存在有数字所处位置与值特殊没有L[i]或R[i]，所以在0与n+1位置虚拟定义两个点，但在线段树时注意将这种情况造成的影响去掉（28行与41行）
*/
