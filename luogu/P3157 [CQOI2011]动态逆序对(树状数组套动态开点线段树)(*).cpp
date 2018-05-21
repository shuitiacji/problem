#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
typedef long long LL;
int lowbit(int x){
	return x&(-x);
}	
int tot=0,n,m;
int pos[maxn],fro[maxn],beh[maxn],a[maxn];
struct BIT_ZXS{
	int ls[maxn*60],rs[maxn*60],rt[maxn*21];
	LL sum[maxn*60];
	LL SUM(int o,int l,int r,int X,int Y){
		if(X<=l&&r<=Y)return sum[o];
		int mid=(l+r)>>1;LL ret=0;
		if(X<=mid&&ls[o])ret+=SUM(ls[o],l,mid,X,Y);
		if(Y>mid&&rs[o])ret+=SUM(rs[o],mid+1,r,X,Y);
		return ret;
	}
	LL que(int l,int r,int X,int Y){
		LL ret=0;
		for(int i=r;i;i-=lowbit(i)){
			ret+=SUM(rt[i],1,n,X,Y);
		}
		for(int i=l;i;i-=lowbit(i)){
			ret-=SUM(rt[i],1,n,X,Y);
		}
		return ret;
	}
	void add(int &o,int l,int r,int v){
		if(!o)o=++tot;
		sum[o]++;
		if(l==r)return ;
		int mid=(l+r)>>1;
		if(v<=mid)add(ls[o],l,mid,v);
		else add(rs[o],mid+1,r,v);
	}
}T;
struct BIT{
	int c[maxn];
	void add(int x){
		while(x<=n){
			c[x]++;x+=lowbit(x);
		}
	}
	int que(int x){
		int ret=0;
		while(x){
			ret+=c[x];x-=lowbit(x);
		}
		return ret;
	}
}few1,few2;
LL ans=0;
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		pos[a[i]]=i;
		fro[i]=i-1-few1.que(a[i]);
		few1.add(a[i]);
		ans+=1LL*fro[i];
	}
	for(int i=n;i>=1;--i){
		beh[i]=few2.que(a[i]);
		few2.add(a[i]);
	}
	for(int i=1;i<=m;++i){
		int x;
		scanf("%d",&x);
		printf("%lld\n",ans);
		int y=pos[x];
		ans-=(fro[y]+beh[y])-(T.que(0,y,x+1,n)+T.que(y,n,1,x-1));
		for(int j=y;j<=n;j+=lowbit(j)){
			T.add(T.rt[j],1,n,x);
		}
	}	
	return 0;
}
/*
题意：给1到n的一个排列，按照某种顺序依次删除m个元素，你的任务是在每次删除一个元素之前统计整个序列的逆序对数。
思路：先用BIT求一次逆序对，在考虑删除点对答案的影响。删除这个点时，答案要减去在这个点前面比它大的和后面比它小的，这两个可以两个数组fro与beh在一开始求逆序对的时候记一下。但问题是，fro与beh中有被删除的点，这样就减多了，于是我们要找到这点前/后的删除点，且权值要大于/小于这个点。可以建一颗权值线段树动态开点维护时间这一具有约束的维度。但题目要求的不只是时间，还有范围要求（前面有多少与后面有多少）。我们可能会想到建多颗线段树，每颗代表一段区间内的删除点，这样我们只要能选几颗在询问区间的线段树中权值满足询问条件的求个和几颗。为了实现管理并求和这么多线段树，我们可以再套一个BIT（或线段树）维护第二个维度区间，BIT的每个节点即为代表一段区间的一颗动态开点的线段树。
debug：
62行求逆序对公式写成:fro[i]=few1.que(a[i])
33行忘记写退出操作
*/
