#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
typedef long long LL;
LL dp[maxn],Smoney[maxn],x[maxn],sum[maxn],p[maxn],c[maxn],q[maxn];
LL ck(int a,int b,int c){
	if(dp[a]-Smoney[a]-dp[b]+Smoney[b]>=x[c]*(sum[b]-sum[a]))return 1;
	return 0;
}
LL cmp(int a,int b,int c){
	return (dp[a]-Smoney[a]-dp[b]+Smoney[b])*(sum[c]-sum[b])-(dp[b]-Smoney[b]-dp[c]+Smoney[c])*(sum[b]-sum[a]);
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%lld%lld%lld",&x[i],&p[i],&c[i]);
	for(int i=1;i<=n;++i){
		sum[i]=sum[i-1]+p[i];
		x[i]=x[n]-x[i];
		Smoney[i]=Smoney[i-1]+p[i]*x[i];
	}
	int l=0,r=0;
	for(int i=1;i<=n;++i){
		while(l<r&&ck(q[l],q[l+1],i))++l;
		dp[i]=dp[q[l]]+Smoney[i-1]-Smoney[q[l]]-(sum[i-1]-sum[q[l]])*x[i]+c[i];
		while(l<r&&cmp(q[r-1],q[r],i)<=0)--r;
		q[++r]=i;
	}
	cout<<dp[n]<<endl;
	return 0;
}	
/*
debug：我在处理的时候为了好算把第七行的y部分写成sum[b]-sum[a],然而x部分是dp[a]-Smoney[a]-dp[b]+Smoney[b],也就是把y反了一下，然而我在画斜率推的时候没有反过来，导致上下凸壳的方向推错了。
以后应该y，x对应，写成sum[a]-sum[b],把不等式方向反一下即可
*/
