#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1000;
LL a[maxn],n,k,d[maxn][maxn];
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
	}
	LL s=0;
	LL p=((1LL)<<(55LL));
	while(p>0){
		memset(d,0,sizeof(d));
		d[0][0]=1;
		s+=p;
		for(int i=0;i<n;++i){
			for(int j=0;j<k;++j){
				if(!d[i][j])continue;
				LL t=0;
				for(int w=i+1;w<=n;++w){
					t+=a[w];
					if((t&s)==s){
						d[w][j+1]=1;
					}
				}
			}
		}
		if(d[n][k]==0)s-=p;
		p>>=1;
	}
	cout<<s<<endl;
	return 0;
}
/*
题意：
给你一列n个数，要求划分成k段，求出每段和，使得段与段之间和的&最大


思路：
这题按套路顺序dp显然有后效性，我们发现这个后效性难以消除。
我们尝试增加维度与改变dp顺序发现也解决不了。
想想后效性产生的原因，是因为当前最大不一定是答案的组成（如对于答案11010,1100也许不如1010优），而要判断这个，比须知道答案。
所以消除后效性不止要考虑维度与dp顺序，从枚举答案入手也可。（也许这种算法不能只叫做dp了，只是后面按位枚举二分答案的check部分）
因为是二进制运算，按位枚举是个不错的主意，从高位开始判断当前位是否可以为1，不难发现因为是从高位开始，若当前位为1，不存在当前为0更优的情况。这样没有枚举所有可能的答案，而且正确性显然。这样的算法就像贪心一样希望尽可能大的答案，并同时用dp判断这个答案是否可行。（有点像一种在按位枚举上特殊的”二分“答案（这样按位搞也相当于log的））


debug:
1.14行注意1与55也要LL
2.22行注意LL
*/
