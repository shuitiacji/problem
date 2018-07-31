#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
typedef long long LL;
const int maxn=200010,maxm=4040;
LL fac[maxn],ifac[maxn],inv[maxn];
LL dp[maxm+10][maxm+10];
LL c(int n,int m){
	if(n>m)return 0;
	return fac[m]*ifac[n]%mod*ifac[m-n]%mod;
}
int n,a[maxn],b[maxn];
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d%d",&a[i],&b[i]);
	fac[0]=1;fac[1]=1;inv[0]=1;inv[1]=1;ifac[0]=1;ifac[1]=1;
	for(LL i=2;i<=maxn-2;++i){
		fac[i]=fac[i-1]*i%mod;
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
		ifac[i]=inv[i]*ifac[i-1]%mod;
	}
	for(int i=1;i<=n;++i){
		dp[2020-a[i]][2020-b[i]]++;
	}
	for(int i=1;i<=maxm;++i){
		for(int j=1;j<=maxm;++j){
			dp[i][j]=((dp[i][j]+dp[i-1][j])%mod+dp[i][j-1])%mod;
		}
	}
	LL ans=0;
	for(int i=1;i<=n;++i){
		ans=(ans+dp[2020+a[i]][2020+b[i]])%mod;
		ans=((ans-c(a[i]+a[i],a[i]+a[i]+b[i]+b[i]))%mod+mod)%mod;
	}
	ans=(ans*inv[2])%mod;
	cout<<ans<<endl;
	return 0;
}
/*
题意：
有N个叉子，对应的叉子附带有两种各Ai个和Bi个的食材，每次选出两个叉子和对应的食材，将这两种食材按照某种顺序插到叉子上。其中，叉子之间都是不同的（不过叉子使用的顺序没有区别），而每种食材都是没有区别的（也就是说，所有是同一种类的食材都是一样的）。求能够有多少种不同的选取方案。

思路：
ans=∑∑((ai+aj+bi+bj)!/(ai+aj)!/(bi+bj)!);
->ans=∑∑C(ai+aj,ai+aj+bi+bj);
对于C(i,j)，它的几何意义是从原点到(i,j)的方案数(x坐标+1,与y坐标+1)
对于C(ai+aj,ai+aj+bi+bj)=(-ai,-bi)到(aj,bj)的方案数。
如果暴力n^2算效率很低，不如把这些抽象到点，一起跑一次dp
对于dp[-ai][-bi],置成1，然后一起dp，dp[i][j]=dp[i-1][j]+dp[i][j-1]，然后在dp[ai][bi]算一下贡献，减去(-ai,-bi)到它自己的。
因为有两次重复算，(-ai,-bi)到(aj,bj)与(-aj,-bj)到(ai,bi)，ans除以2

debug:
因为一个点可能有多个叉子，不能直接每次dp[i][j]-组合数，先加到ans，再减组合数。
*/
