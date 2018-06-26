#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
set<LL> s;
LL a[200010];
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		LL x;
		scanf("%lld",&x);
		s.insert(x);
		a[i]=x;
	}
	for(int i=1;i<=n;++i){
		for(LL j=1;j<2e9;j*=2){
			if(s.count(a[i]+j)&&s.count(a[i]+j*2)){
				puts("3");
				printf("%lld %lld %lld\n",a[i],a[i]+j,a[i]+j*2);
				return 0;
			}
		}
	}
	for(int i=1;i<=n;++i){
		for(LL j=1;j<2e9;j*=2){
			if(s.count(a[i]+j)){
				puts("2");
				printf("%lld %lld\n",a[i],a[i]+j);
				return 0;
			}
		}
	}
	puts("1");
	printf("%lld\n",a[1]);
	return 0;
}
/*
题意：
一列数，找出其中尽可能多的数，使得其中任意两个数之差为2的幂

思路：
当有4个数符合条件时。
b-a=2^x
c-b=2^y
d-c=2^z
d-a=2^m
有2^m=2^x+2^y+2^z(x<y<z)=2^x(1+2^(y-2)+2^(z-x))不存在

3个数：
2^x+2^y=2^z
x=y=z-1

暴力看一下答案是3 or 2 or 1
*/
