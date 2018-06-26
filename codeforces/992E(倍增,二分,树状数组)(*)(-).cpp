#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=2e5+10;
int lowbit(int x){return x&(-x);}
LL c[maxn];
int a[maxn],n,q;
void add(int x,int v){
	while(x<=n){
		c[x]+=v;
		x+=lowbit(x);
	}
}
LL que(int x){
	LL ret=0;
	while(x>0){
		ret+=c[x];
		x-=lowbit(x);
	}
	return ret;
}
int gao(int l,int r,LL now){
	if(l==r){
		if((now=que(l-1))==a[l])return l;
		if(l==n)return -1;
		return gao(l+1,n,(now+a[l])<<1);
	}
	int mid=(l+r)>>1;
	LL tmp=que(mid);
	if(tmp<now)return gao(mid+1,r,tmp<<1);
	else return gao(l,mid,now);
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		add(i,a[i]);
	}
	for(int i=1;i<=q;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y-a[x]);
		a[x]=y;
		printf("%d\n",gao(1,n,0));
	}
	return 0;
}
/*
题意：
有一列数，要求查询这一列数中，存不存在一个数，它前面所有数之和等于它自身的值，输出这个数的编号(存在多个，只求任意一个)。
同时要求支持修改，q个修改操作，将第i个数修改为一个新值，将每次修改后数列进行查询操作。

思路：
先不管修改。
先考虑暴力，显然是暴力扫一遍，O(n)
优化：在暴力过程中，若第i个不满足，直接就去看第i+1个了，我们能不能充分利用第i个不行的信息进行优化，通过这个状态的不可能方便的直接看出一些其他状态的不可能。
因为题意满足的东西中，sum[i-1]=val[i]，sum[i]=2*sum[i-1]，能不能利用这个东西进行倍增。
因为sum序列是单调上升的，满足条件的val[i]，一定满足sum[i]>=2*sum[j](j<=i-1)，反之就不可能满足条件。
对当前处理到第i个，若i不行，我们不必跳到i+1，可以二分一下sum[i]*2在序列中的位置跳过去，因为这之间的数不能为答案，这样复杂度有两个log，仍不够优。
因为在i与跳过去的位置中这些数，它们也可以再倍增(它们肯定不是答案)，即我们能通过它们再获取一些不可能的状态，在这里我们再优化。
考虑二分与倍增一起执行，二分到一个mid，如果它处于像刚刚说的i与跳过去的位置中（即已能证实不可能为答案），不仅修改二分的区间，而且倍增（相当于再次通过这个状态的不可能，又扩张一些已证实不可能的状态），若不处于这段位置（即还无法证实是否不可能的），只修改二分区间，而不通过它倍增。
最后二分到一个数，即使用完了之前的信息，能知道的最左边的有可能为答案的数，进行一次暴力判断，若可以则找到答案，不行则通过它再来一次倍增。
实现上列操作，只需记一下倍增的值，若sum小于这个值，就是不能满足条件的，大于就是还无法确定的。
其中二分与倍增同时进行（不为嵌套），而非之前的每一次倍增搞一次二分（为嵌套），复杂度即为倍增复杂度，log(Maxsum)。
修改的话，一个BIT维护sum即可，复杂度再套上一个q*log(n)。
*/
