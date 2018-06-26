#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
int m[maxn],a[maxn];
int main(){
	int n;
	long long  ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		m[i]=a[i];
	}
	for(int i=1;i<n;++i){
		if(m[i+1]<m[i])m[i+1]=m[i];
	}
	for(int i=n;i>1;--i){
		if(m[i]-m[i-1]>1)m[i-1]=m[i]-1;
	}
	for(int i=1;i<=n;++i)ans+=m[i]-a[i];
	cout<<ans<<endl;
	return 0;
}
/*
题意：你用n天时间去观察一条河，这条河的水位每天都有可能改变，所有你每天都会在当前水位上画一条线来标注（这个线永远都不会消失），当然啦，如果这个水位刚好和之前某天水位一致，也就是已经有线和水面平齐，那么当然就不需要再标记了。现在告诉你每天可以看到的水位线数量a[i]，求出∑d[i]的最小值，其中d[i]表示第i天水底下的标记线的个数
思路：设第i天总水位线的数目为m[i],m[i]=d[i]+a[i]+1;
则m[i]单调不减，且m[i+1]-m[i]最大为1
可以把问题转化成给你一堆数a[i]，可以将其任意一个+1，使得最后单调不减，且相差不超过1，求最少加几次可以
实现很简单，同时满足两个条件很困难，可以先正序一遍贪心将其变为单调不减，在倒序一遍将其变为相差只1
debug：longlong
*/
