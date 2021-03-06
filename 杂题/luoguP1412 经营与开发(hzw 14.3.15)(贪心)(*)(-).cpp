#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
double ans,k,c;
int n,w,t[maxn],a[maxn];
int main(){
	freopen("exploit.in","r",stdin);
	freopen("exploit.out","w",stdout);
	scanf("%d%lf%lf%d",&n,&k,&c,&w);
	k=1-0.01*k;c=1+0.01*c;
	for(int i=1;i<=n;++i)scanf("%d%d",&t[i],&a[i]);
	for(int i=n;i>=1;--i){
		if(t[i]==1)
			ans=max(ans,ans*k+a[i]);
		else ans=max(ans,ans*c-a[i]);
	}
	printf("%.2lf\n",ans*w);
	return 0;
}
/*
题意：你驾驶着一台带有钻头（初始能力值w）的飞船，按既定路线依次飞过n个星球。
星球笼统的分为2类：资源型和维修型。（p为钻头当前能力值）
1.资源型：含矿物质量a[i]，若选择开采，则得到a[i]*p的金钱，之后钻头损耗k%，即p=p*(1-0.01k)
2.维修型：维护费用b[i]，若选择维修，则支付b[i]*p的金钱，之后钻头修复c%，即p=p*(1+0.01c)
注：维修后钻头的能力值可以超过初始值（你可以认为是翻修+升级）
金钱可以透支。
请作为舰长的你仔细抉择以最大化收入。



思路：
1.容易想到dp,F[i][x][y]表示到达第 i 个星球,且之前开采过 x 次,维修过 y 次。
因为本题开 采 和 维 修对 钻头 的 影响 都是定 值 。所以 钻头 能 力 就是
w*k^x*c^y
时空复杂度:O(n^3)
2.现在分析一下这题的特殊性，dp算法的瓶颈即为存储x，y来算出钻头能力，这是理所应当的，因为能力具有后效性，在dp中必须存储。考虑研究一下这个后效性的机制，想办法把这个状态舍去。发现这个能力的影响对后面状态的影响并不复杂，是一次（没有复杂的多次操作）的，只乘上了一个数值而(就好像初始钻头能力为 w,实际上你可以按 1 来做,最后再把 ans 乘上 w)。而已。
正难则反,F[i]表示第 i--n 个星球的最优收入,且假设从第 i 个星球开始时
钻头能力为 1。换句话说,这样的状态设计,规定了一个参考系。
转移过程就变得简单:如果在第 i 个星球开采,那么第 i+1--n 个星球的初
始钻头能力就是 1*(1-0.01k)。换句话说,就是 F[i+1]*(1-0.01k)。
所以 F[i]=max{F[i+1],F[i+1]*(1-0.01k)+a[i]}
对于维护型星球,大同小异。就系数和代价的正负而已。
观察方程,F[i]=max{F[i+1],F[i+1]*(1-0.01k)+a[i]}
实际上就是取下 i+1--n 的最值而已,所以这题实际上就成了贪心。
dp时可以多分析一下某些条件的后效性，想到省掉维度的办法。
*/
