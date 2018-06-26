#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define eps 2e18
const int maxn=2e5+10;
LL a[maxn],jp[maxn],n,k;
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;++i)scanf("%lld",&a[i]);
	jp[n]=n;jp[n+1]=n+1;
	for(int i=n-1;i>=1;--i){
		if(a[i]==1)jp[i]=jp[i+1];
		else jp[i]=i;
	}
	LL ans=0;
	for(int i=1;i<=n;++i){
		LL mul=1;
		LL sum=0;
		int j=i;
		int las=i;
		while(j<=n){
			sum+=a[j];
			if(eps/a[j]<mul)break;
			mul*=a[j];
			las=j;
			j=jp[j+1];
			if(mul%k==0&&mul/k>=sum&&mul/k<=sum+j-las-1)ans++;
			sum+=j-las-1;
		}
	}
	cout<<ans<<endl;
	return 0;
}
/*
题意：
Nastya 在生日那天收到了一个大小为 n 的数组，她想知道数组存放的序列中，有多少的连续子序列满足其中所有的数的乘积是数的总和的 k 倍。请帮她得到答案。

思路：对于a[i]==1的情况，因为对multipul是没有影响的，只影响L,R。那么对于连续的区间1我们就可以跳。根据数据有multipul不会超过2e18。那么根据以上的做法，因为每次乘的数都是≥2的，第二层while循环的次数不会超过61次。复杂度为O(60*n);
*/
