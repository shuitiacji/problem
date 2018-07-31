#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=100010;
int n;
LL a[maxn],b[maxn];
map<LL,int> hs;
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		LL x;
		scanf("%lld",&x);
/**/	for(LL j=2;j*j*j<=x;++j){
			while(x%(j*j*j)==0)x/=j*j*j;
		}
		a[i]=x;
		hs[x]++;
		LL y=1;
/**/	for(LL j=2;j*j*j<=x;++j){
			if(x%j==0){
				y*=(x%(j*j))==0?j:j*j;
			}
			while(x%j==0)x/=j;
		}
		if((LL)sqrt(x)*(LL)sqrt(x)==x)y*=(LL)sqrt(x);
		else y*=x*x;
		b[i]=y;
	}
	int ans=0;
	if(hs[1]>0)ans++,hs[1]=0;
	for(int i=1;i<=n;++i)ans+=max(hs[a[i]],hs[b[i]]),hs[a[i]]=0,hs[b[i]]=0;
	cout<<ans<<endl;
	return 0;
}
/*
题意：
给你n个数，从中选出尽可能多的数，使得这些数之间两两相乘无法成为立方数。

思路：
因为在原数列中，一个数能与其组成立方数的数比较多，只能n^2查找。
考虑如果一个数只有一个数能与其组成立方数。（这个数我们称为补数）
做到这一步只需要将每个数质因数的指数模3，就可以做到。
现在的任务就是对10^10的数分解质因数。
可以pollard_rho，但也有更简单的办法。
因为指数在3及3以上的质因数的范围不会超过10^(10/3)，这一部分我们可以暴力枚举。
除去这部分后，可能还有1个或2个大于10^(10/3)的质因数，因为我们只关心补数，只要看它现在是否是平方数即可。

debug：
15,21行，虽然j<10^(10/3)，在int内，但还是要开LL，因为后面存在一些表达式如j*j*j，这些表达式的结果超过了int，要么LL j，要么在表达式前强转LL
*/
