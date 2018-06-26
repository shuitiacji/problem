#include<bits/stdc++.h>
using namespace std;
const int maxn=5000010;
int n,k,d;
int c[maxn],a[maxn],dp[maxn];
int lowbit(int x){return x&(-x);}
void upt(int x){
	while(x<=n){
		c[x]++;x+=lowbit(x);
	}
}
int que(int x){
	if(x<0)return 0;
	int ret=0;
	while(x){
		ret+=c[x];x-=lowbit(x);
	}
	return ret;
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d%d",&n,&k,&d);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	int l=1;
	upt(1);
	for(int i=1;i<=n;++i){
		int R=i-k+1;
		while(l<i&&a[i]-a[l]>d)++l;
		dp[i]=que(R)-que(l-1);
		if(dp[i]>0){
			upt(i+1);
		}
	}
	if(dp[n]>0)
		puts("YES");
	else 
		puts("NO");
	return 0;
}
/*
题意：给n个数，可以放到若干个盒子里，要求每个盒子至少有k个数，并且每个盒子中最大和最小的数差值不超过d。问是否有合理的方案来分配。
思路：先将所有数排序，显然数只能一段一段地放在盒子里，考虑dp。
设dp[i]，若存在方案使得1-i能放在几个盒子中，且i作为它那个盒子中最大的数，则dp[i]=1。
可以很容易想到一个朴素的dp，每次从前面的状态选一个dp[j]==1的，把j+1-i的放一个盒子中且保证这个盒子满足约束条件，即if(dp[j]==1&&i-(j+1)+1>=l&&a[i]-a[j+1]<=d)dp[i]=1  (1<=j<i) 这样的算法是n^2的
考虑根据它的三个约束条件一个个优化
1.i-(j+1)+1:这个很容易，处理出R=i-k+1,则1<=j<=R
2.a[i]-a[j+1]<=d:考虑到a是单调的，能选的j的范围随着dp过程，会越来越大，定义一个指针l，每次要更新一个新的i时，把l右移至满足条件即可，此时l<=j<=R
3.dp[j]==1:现在已处理出j能所在的区间，只要查看这范围中sigma(dp[j])若和>0，则dp[i]=1，可以用BIT维护dp[]的和。debug:36,32行,忘写>0
*/
