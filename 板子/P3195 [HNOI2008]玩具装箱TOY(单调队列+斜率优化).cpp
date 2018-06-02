#include<bits/stdc++.h>
using namespace std;
const int maxn=50010;
typedef long long LL;
int n,l;
int c[maxn],q[maxn];
LL s[maxn],dp[maxn];
LL Y(int i){
	return dp[i]+1LL*(1LL*i+s[i])*(1LL*i+s[i])+1LL*2*(1+l)*(1LL*i+s[i]);
}
LL X(int i){
	return 1LL*2*(i+s[i]);
}
LL comp(LL x1,LL y1,LL x2,LL y2,LL x3,LL y3){
	return (y2-y3)*(x1-x2)-(y1-y2)*(x2-x3);
}
LL slope(int i,int j,int k){
	return (Y(i)-Y(j))>1LL*(1LL*k+s[k])*(X(i)-X(j));
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d",&n,&l);
	for(int i=1;i<=n;++i){
		scanf("%d",&c[i]);
		s[i]=s[i-1]+1LL*c[i];
	}
	int i=0,j=0;
	for(int t=1;t<=n;++t){
		while(i<j&&slope(q[i],q[i+1],t))++i;
		dp[t]=dp[q[i]]+1LL*(t-q[i]+s[t]-s[q[i]]-1-l)*(t-q[i]+s[t]-s[q[i]]-1-l);
		while(i<j&&comp(X(t),Y(t),X(q[j]),Y(q[j]),X(q[j-1]),Y(q[j-1]))>=0)--j;
		q[++j]=t;
	}
	printf("%lld\n",dp[n]);
	return 0;
}
/*
题意：dp[i]=min{dp[j]+(i−(j+1)+sumi−sumj−L)^2}求解这个式子
思路：设f(i)=i+s[i](s为前缀和)
	dp[i]=min(dp[j]+(f(i)-f(j)-1-L)^2)
	设j>k，且从j转移到i比k更优
	即：(dp[j]+f(j)^2+2(1+L)f(j)-dp[k]-f(k)^2-2(1+L)f(k))/(2*f(j)-2*f(k))<=f(i)
	把X，Y设一下，斜率优化即可
	因为f(i)递增，可以单调队列O(n)
debug:应先弹队头再加队尾，公式推错
*/
