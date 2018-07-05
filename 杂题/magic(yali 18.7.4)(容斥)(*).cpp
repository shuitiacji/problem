#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
typedef long long LL;
const int maxn=5050;
LL inv[maxn],a[maxn],ifac[maxn],fac[maxn],g[maxn],f[maxn][maxn],G[maxn];
LL C(int n,int m){
	if(m>n)return 0;
	return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
void mathint(){
	fac[0]=fac[1]=inv[0]=inv[1]=ifac[0]=ifac[1]=1;
	for(int i=2;i<=5010;++i){
		fac[i]=fac[i-1]*i%mod;
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
		ifac[i]=inv[i]*ifac[i-1]%mod;
	}
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n,m,k;
/**/scanf("%d%d%d",&m,&n,&k);
	mathint();
	for(int i=1;i<=m;++i)scanf("%lld",&a[i]);
	f[0][0]=1;
	for(int i=1;i<=m;++i){
		for(int j=0;j<=n;++j){
			for(int s=0;s<a[i];++s){
				if(s>j)break;
				if(f[i-1][j-s]>0){
/**/				f[i][j]+=f[i-1][j-s]*C(a[i],s)%mod*fac[a[i]-1]%mod*ifac[a[i]-s-1]%mod;
/**/				f[i][j]%=mod;
				}
			}
		}
	}
	for(int i=0;i<=n;++i){
		g[i]=fac[n-i]*f[m][i]%mod;
	}
	G[n]=g[n];
	for(int i=n-1;i>=k;--i){
		G[i]=g[i];
		for(int j=i+1;j<=n;++j){
			G[i]=((G[i]-C(j,i)*G[j]%mod)%mod+mod)%mod;
		}
	}
/**/for(int i=1;i<=m;++i)G[k]=G[k]*ifac[a[i]]%mod;
	cout<<G[k]<<endl;
	return 0;
}
/*
题意:
桌面上摆放着m种魔术卡，共n张，第i种魔术卡的数量为ai，魔术卡顺次摆放，形成一个长度为n的魔术序列，在序列中，若两张相邻的魔术卡种类相同，则它们被称为一个魔术对。
两个序列本质不同，当且仅当存在一个位置，使得两个魔术序列这个位置上的魔术卡种类不同，求本质不同的恰好包含k个魔术对的魔术序列的数量。

思路：
本质不同很棘手,不妨假设任意两个魔术卡均不同
设这样算出的方案数为 ans
则真正的方案数 =ans/a[1]!/a[2]!/.../a[m]!
考虑容斥
g[i]= 至少存在 i 个“魔术对”的方案数
首先考虑如何求出 g[0]~g[n]
既然要求至少存在 sum 个“魔术对”,不妨把这 sum 个“魔术对”分配
到 m 种魔术卡里面
设第 i 种魔术卡中至少存在 s[i] 个“魔术对”,则需要满足 s[1]+s[2]+...+s
[m]=sum
选出 s[i] 个魔术卡“浪费掉”:把那 s[i] 张魔术卡顺次插入到当前所有魔
术卡后面
这样保证不重不漏
方案数 =C[a[i]][s[i]]*(a[i]-s[i])*(a[i]-s[i]+1)*...*(a[i]-1)
=C[a[i]][s[i]]*(a[i]-1)!/(a[i]-s[i]-1)!

于是可以 DP 了
f[i][j]= 前 i 种魔术卡一共钦定了 j 个“魔术对”的方案数
转移时枚举 s[i] ,用 f[i-1][j-s[i]] 更新 f[i][j]
即: f[i][j]+=f[i-1][j-s[i]]*C[a[i]][s[i]]*(a[i]-1)!/(a[i]-s[i]-1)!
其中 0<=s[i]<=a[i]-1
状态数 O(mn) ,转移总复杂度 O(n^2)
O(n^2)
g[i] 的计算:先将没有浪费的魔术卡进行排列,表示它们的相对位置,再
插入所有浪费的魔术卡
g[i]=f[m][i]*(n-i)!

设 G[i]= 恰好存在 i 个“魔术对”的方案数
假设已经求出 g[k] , G[k+1]~G[n] ,考虑计算 G[k]
G[k]=g[k]-C[k+1][k]*G[k+1]-C[k+2][k]*G[k+2]-...-C[n][k]*G[n]
特殊地, G[n]=g[n]
O(n^2) 递推出 G[k] 即可
O(n^2)

debug:
1.23行，nm搞反
2.32,48,除法一定要用逆元
3.33忘写
*/
