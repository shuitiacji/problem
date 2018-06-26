#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL ans;
const int maxn=2e5+10;
int a[maxn],hs[maxn];
int st[maxn],l[maxn],r[maxn];
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]),hs[a[i]]=i;
	int top=0;
	for(int i=1;i<=n;++i){
		while(top&&st[top]>a[i])--top;
		st[++top]=a[i];
		if(top==1)l[i]=0;
		else l[i]=hs[st[top-1]];
	}
	top=0;
	for(int i=n;i>=1;--i){
		while(top&&st[top]>a[i])--top;
		st[++top]=a[i];
		if(top==1)r[i]=n+1;
		else r[i]=hs[st[top-1]];
	}
	for(int i=1;i<=n;++i){
		ans+=1LL*((LL)(i-l[i]))*((LL)(r[i]-i))*((LL)a[i]);
	}
	cout<<ans<<endl;
	return 0;
}
/*
题意：
a为1-n的排列
输出∑∑min(a[l],a[l+1],..,a[r]) (sigma分别枚举l,r)


思路：
排列意味着，值与位置有一一映射关系，通常暗示我们从值入手。
一个个n^2搞肯定不行，我们发现一个值在多个序列中存在贡献，且只求答案，想办法反着搞。
我们发现一个数只有在经过它，且序列中没有比它小时产生一次贡献。
根据这两个约束构造，
首先是经过它：
显然是在这个数的左边枚举一个左端点，右边枚举一个右端点。
接下来根据没有比它小的数，找出这两个端点的取值范围：
显然就是找到在其左边第一个比它小的，与右边第一个比它大的，这两段范围乘一下就是满足的序列个数。这个可以用单调栈预处理。
*/
