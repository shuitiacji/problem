#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
typedef long long LL;
LL sta[maxn],a[maxn],t[maxn],s[maxn];
int find(LL k,int r){
	int l=1,ANS=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(a[mid]<=k)ANS=mid,l=mid+1;
		else r=mid-1;
	}
	return ANS;
}
int n,m;
int top;
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d",&n,&m);
	sta[top=1]=n;
	for(int i=1;i<=m;++i){
		LL x;
		scanf("%lld",&x);
		while(sta[top]>=x)--top;
		sta[++top]=x;
	}
	m=top;
	for(int i=1;i<=m;++i)a[i]=sta[i];
	t[m]=1;
	for(int i=m;i>=1;--i){
		LL k=a[i];int p=find(k,i-1);
		while(p){
			t[p]+=t[i]*(k/a[p]);
			k%=a[p];
			p=find(k,p-1);
		}
		s[1]+=t[i];s[k+1]-=t[i];
	}
	LL ans=0;
	for(int i=1;i<=n;++i){ans+=s[i];printf("%lld\n",ans);}
	return 0;
}
/*
题意：
有一个长度为n的序列，初始为1~n。m个操作，每个操作ai表示把当前序列复制无限次，然后取前ai个数作为新序列。问最终序列里1~n各出现多少次。 

思路：
若a[i]>=a[i+1]，显然a[i]是没有用的。
我们可以预处理一下，用个单调栈使得a单调(需要包括一开始的n)。
假设每一步后的状态是这样子：
0： 1 2 3 4 5
1： 1 2 3 4 5|1
2： 1 2 3 4 5 1|1 2 3
3： 1 2 3 4 5 1 1 2 3|1 2 3 4
4： 1 2 3 4 5 1 1 2 3 1 2 3 4|1 2 3 4 5 1|1
可以看出，每一步的序列，都是上一步的几个序列加上一个后缀，而这个后缀也是在上面某一步的几个序列加上一个后缀（如第4步中，后缀1 2 3 4 5 1 1可以变为第1步加上后缀1）
这种神奇的性质很容易证明，因为序列是一步步推出来的，i步中包含了i-1步，i-1步又包含了i-2，……，因为后缀也算是上一步序列的一小部分，它也就包含了组成上一步的，也就是上面所有步的一部分，我们就可以将它一步步脱离出来，使它变小，这样的变小充分利用了之前的信息，肯定比暴力优。
对每个后缀，二分找一下比它小的最大的序列，模一下它的长度。
我们不断对这个后缀进行这种操作，直到它变小到小于n了停止（这时它就是原序列中的一段）
设t数组表示第i步的序列在最后的答案中出现了几次，s[i]表示第i个数被mark了几次(这个可以差分)。
倒推一下即可。
因为一个数模一个比它小的数最多只有log次(类比一下倍增?)，加上二分的log，O(nlognlogn)
*/

