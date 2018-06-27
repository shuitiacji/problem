#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=100010;
int a[maxn],c[maxn],b[maxn],A[maxn],ans[maxn];
int AA[maxn];
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&AA[i]);
/**/	if(i!=1)a[i]=AA[i]-AA[i-1];
		else a[i]=AA[i];
		c[i]=i;
	}
	int m;LL k;
	scanf("%d%lld",&m,&k);
	for(int i=1;i<=m;++i){
		int x;
		scanf("%d",&x);
		swap(c[x],c[x+1]);
	}
	for(int i=1;i<=n;++i){
		if(!b[i]){
			int cnt=0;
			for(int j=i;!b[j];j=c[j]){
				b[j]=1;
				A[++cnt]=j;
			}
			for(int j=1;j<=cnt;++j){
				ans[A[j]]=a[A[((LL)(j+k-1))%cnt+1]];
			}
		}
	}
	LL sum=0;
	for(int i=1;i<=n;++i){
		sum+=ans[i];
		printf("%lld.0\n",sum);
	}
	return 0;
}
/*
题意：
数轴上有n只兔子，第i只兔子的坐标为xi。
有一种操作，这操作有很多子操作,第i个子操作是要让第ai只兔子等概率的跳到自己关于第ai+1或第ai-1只兔子的对称点。
进行K次这种操作，求每只兔子最后坐标的期望值。

思路：
每次操作Ax=1/2(2A(x−1)−ax)+1/2(2A(x+1)−ax)=A(x−1)+A(x+1)−Ax
发现这个操作是线性的，可以直接用期望值替换
如果是对这个东西维护差分序列：
原：a[x] a[x+1] a[x+2] 
    a[x] a[x+1]-a[x] a[x+2]-a[x+1]
变后：
	a[x] a[x-1]+a[x+1] a[x+2]
	a[x] a[x+2]-a[x+1] a[x+1]-a[x]
发现就是交换了一下位置
又是对一个操作重复执行多次，还是交换操作，必然状态出现循环
找到所有循环后，在每个循环上走k步，当然要%一下循环长度

debug：
14行，差分数组要和原数组分清
*/
