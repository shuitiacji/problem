#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
const int maxn=5000010;
long long fac[maxn],ifac[maxn],inv[maxn],d[2010][2010];
int n,k;
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	cin>>n>>k;
	if(k==1){
		cout<<1<<endl;
		return 0;
	}
	fac[0]=inv[0]=ifac[0]=fac[1]=inv[1]=ifac[1]=1;
	for(int i=2;i<=n*k+10;++i){
		fac[i]=(fac[i-1]*i)%mod;
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
		ifac[i]=(ifac[i-1]*inv[i])%mod;
	}
	d[0][1]=1;
	for(int i=2;i<=n;++i)
		d[0][i]=d[0][i-1]*(fac[i*(k-1)-1]*ifac[k-2]%mod*ifac[(i-1)*(k-1)]%mod)%mod;
	for(int i=1;i<=n;++i){
		for(int j=i;j<=n;++j){
			d[i][j]=(d[i-1][j]+d[i][j-1]*(fac[i+j*(k-1)-1]*ifac[k-2]%mod*ifac[i+(j-1)*(k-1)]%mod)%mod)%mod;
		}
	}
	cout<<d[n][n]*fac[n]%mod<<endl;
	return 0;
}

/*
题意：
给定n种颜色的球每种k个，任意排序一下，将每种颜色的最左一个染白，求这样能得到的不同序列总有多少个。

思路：
先给加上一些无伤大雅的约束，比如说假定被染白的（也就是每种颜色最左的）原色按1->n排列，这样只需往答案上乘个n！即为原问题答案。
考虑满足题意的序列（被染过后的），对于每个1<=i<=n-1，你可以放i+1颜色在你至少在之前放了一个i颜色的时候；
同样，对于1<=i<=n，你可以放i颜色，在你放了至少i个白球之后。
计数问题，考虑dp
从后开始放球，转移显然有两种，放白or放第一个某种颜色的。
设状态dp[i][j]为后面已有i个白球，j种非白颜色。同时j>=i(你可以放i+1颜色在你至少在之前放了一个i颜色的时候，但因为从后开始，条件反了一下)，这个条件通过递推顺序解决。
选白直接加，选有色的，要把所有这种颜色的都考虑上（因为这时就可以乱选这种颜色的了，可以把它任意穿插在之后所有点中，这也是为什么从后放的原因，方便处理这个东西），可以排列组合解决。
*/
