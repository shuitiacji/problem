#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL d[2010][2010];
LL a[2010];
LL Min(LL A,LL B){return A<B?A:B;}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	LL n,x;
	scanf("%lld%lld",&n,&x);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
	}
	LL Ans=0;
	for(int i=1;i<=n;++i)d[i][0]=a[i],Ans+=a[i];
	for(int K=1;K<=n-1;++K){
		LL ans=0;
		for(int i=1;i<=n;++i){
			int pos=(i-K)<=0?n-abs(i-K):i-K;
			d[i][K]=Min(a[pos],d[i][K-1]);
			ans+=d[i][K];
		}
		ans+=K*x;
		Ans=min(ans,Ans);
	}
	cout<<Ans<<endl;
	return 0;
}

/*
题意：通过以下两种操作恰好获得 n 种颜色，最少要花费多少秒？
操作1：花费 a[i] 秒，直接获得 颜色 i 。
操作2：使用魔法，花费 x 秒，使得之前获得的 颜色 i 全部变为 颜色 i + 1。（n + 1 = 1）

思路：
对于每一个颜色，它只能从i-k到i之间的颜色转移而来，枚举k贪心即可。

*/
