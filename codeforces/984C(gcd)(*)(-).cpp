#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define gcd __gcd
/*inline LL gcd(LL a,LL b){
	if(b==0)return a;
	return gcd(b,a%b);
}*/
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		LL p,q,b;
		scanf("%lld%lld%lld",&p,&q,&b);
		LL tmp=gcd(p,q);
		q/=tmp;
		tmp=b;
		while(q!=1){
			tmp=gcd(q,tmp);
			q/=tmp;
			if(tmp==1)break;
		}
		if(q==1)printf("Finite\n");
		else printf("Infinite\n");
	}
	return 0;
}
/*
题意：p/q   在b进制是否是一个  有限小数。
分析：只有当分母的质因数全是进制的约数时不无限。
暴力处理每次除一个gcd(p,b)有可能超时，可以将b置成每次的gcd，因为如果gcd已经在变小，即有些b中的约数在p中已经不存在，在b中留这些约数也就没有用
*/
