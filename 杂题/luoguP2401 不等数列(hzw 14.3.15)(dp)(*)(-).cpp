#include<bits/stdc++.h>
using namespace std;
int n,k,f[1010][1010];
const int mod=2012;
int main(){
	freopen("num.in","r",stdin);
	freopen("num.out","w",stdout);
	scanf("%d%d",&n,&k);
	f[1][0]=1;
	for(int i=2;i<=n;++i){
		f[i][0]=1;
		for(int j=1;j<=n;++j){
			f[i][j]=(f[i-1][j-1]*(i-j)+f[i-1][j]*(j+1))%mod;
		}
	}
	printf("%d\n",f[n][k]);
	return 0;
}
/*
题意：
将1到n任意排列，然后在排列的每两个数之间根据他们的大小关系插入“>”和“<”。问在所有排列中，有多少个排列恰好有k个“<”。答案对2015(luogu)(2012:hzwer)取模。
思路：这个题决策顺序的选择不应是按时间序，这样决策对算法优化没有任何帮助；这个时候我们应该在不影响求答案的情况下，改变决策顺序，可以按1-n依次插入的顺序dp。这样不影响结果，且把dp中不好存储的状态约束直接放在了外层循环上。
在可以设状态，把另一个约束条件<的数量放进状态。f[i][j]表示前i个j个<的方案数
容易发现当当前这个数插入之前的序列中，若是<关系的两数间，由于当前数最大，使<不变，>数目++
同上，若>关系，>不变，<++
f[i][j]=(f[i-1][j-1]*(i-j)+f[i-1][j]*(j+1))%mod

这题给了一个很好的思路，当递推顺序对dp没有什么约束时，我们可以换一种有约束的顺序方便处理出dp中状态不好存储与约束的。
*/
