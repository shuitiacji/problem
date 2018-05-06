#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long LL;
LL a[100100];
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	LL n;
	while(scanf("%lld",&n)&&n){
		LL ans=0,sum=0;
		for(int i=1;i<=n;++i){
			scanf("%lld",&a[i]);
			if(sum!=0)ans+=abs(sum);
			sum+=a[i];
		}
		cout<<ans<<endl;
	}
	return 0;
}
/*
题意：一题街道上很多酒店，交易葡萄酒，正数为卖出葡萄酒，负数为需要葡萄酒，总需求量和总售出量是相等的，从一家店到另外一家店需要路费（路费=距离×运算量），假设每家店线性排列且相邻两店之间距离都是1,求最小路费。










思路：容易想到一个贪心，每次只与相邻两家交易
有一个直观的方法看到这个算法的正确性：i=1-n，从前往后推，假设i要向j，k送酒or要酒，（设都在左侧，右侧的往后推的下一个i会处理），分别送，需要i-j+i-k的路程，如果按只与左交易的原则，i与i-1交易，i-1与i-2交易，... ... ，j+1与j交易，... ...，k+1与k交易。相当于分两次走的路程一次性走完了，需要max(i-j,i-k)的路程。
考虑如何实现，可以维护一个前缀和sum，令前面i个的状态像这样：0,0,0,0,0,0，... ... ，sum。当加入第i+1个时，将第i个的sum交易给i+1（sum=0时就不用交易），变成这样：0,0,0,0,0,0，... ... ，0，sum+a[i+1]，于是可以sum=sum+a[i+1]（维护前缀和），又变成前面的问题。
debug:long long忘开。
*/
