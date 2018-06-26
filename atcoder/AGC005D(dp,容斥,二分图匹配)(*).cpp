#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=2010,maxm=maxn<<1;
#define mod 924844033
int vis[maxn][2],ed[maxm];
int tot;LL f[maxm][maxn][2],fac[maxn];
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i){
		for(int j=0;j<=1;++j){
			if(!vis[i][j]){
				int len=0;
				for(int x=i,y=j;x<=n;x+=k,y^=1){
					vis[x][y]=1;len++;
				}
				ed[tot+=len]=1;
			}
		}
	}
/**/f[1][0][0]=1;
	for(int i=1;i<tot;++i){
		for(int j=0;j<=n;++j){
			f[i+1][j][0]=(f[i][j][1]+f[i][j][0])%mod;
			if(!ed[i])f[i+1][j+1][1]=f[i][j][0];
		}	
	}
	fac[0]=1;
	for(LL i=1;i<=n;++i)fac[i]=fac[i-1]*i%mod;
	LL ans=fac[n];
	for(LL i=1,j=-1;i<=n;++i,j=-j){
/**/	ans=(ans+mod+j*fac[n-i]*((f[tot][i][0]+f[tot][i][1])%mod)%mod)%mod;
	}
	cout<<ans<<endl;
	return 0;
}
/*
题意：
给出n和k，问有多少个长度为n的排列p使得对于任意的i，有|pi−i|≠k。 

思路：
反着来容斥。
那么我们要求的就是至少选x个位置不满足条件的方案。 
利用上题目中的条件|pi−i|≠k。
为挖掘这个性质，用图的方式形象的表示
考虑把值和位置之间的关系建成一个二分图。
假定左半的N个点依次代表值1~N，右半的N个点依次代表位置1~N。
那么，一条边(i,j)存在的意义是，位置j处的值是i。
可以发现所有不合法的情况均包含形如(i,i−k)或(i,i+k)的一条边。
此时二分图匹配数就为排列中至少不满足条件的位置数
注意到每个数和他相减绝对值为k的数只有不超过两个，也就是说n个点会形成很多条链，每个点只能和与它有边相连的点配对。 
因为每条链都是平行的，我们可以在每条链上dp出方案来(满足二分图匹配的情况下)，最后背包一下。
其实也可以一起dp，即把链串起来，但在链与链的连接处，因为链与链并未实际相连特殊处理一下。

具体方法：

令f[i][j][0/1]，描述当前在i号边，已经选择了j条匹配边，上一条边(i-1)是选了(1)还是没选(0)(因为相当于二分图匹配，看是不是匹配边)的方案数。
那么可以得到转移方程:
f[i+1][j][0]=f[i][j][0]+f[i][j][1]
f[i+1][j+1][1]=f[i][j][0](这一步在链与链并未实际连接处要省掉)

发现由于是按边顺序dp，要保证一条链中编号是相邻的

debug：
1.33行，为防爆负，要加个mod
2.22行，因为15行中，是从i开始而非i+k，所以在一条链开始的边是一个自边（i到i），所以22行一开始的1号边是不存在的自边，不存在什么是匹配边的1情况

*/
