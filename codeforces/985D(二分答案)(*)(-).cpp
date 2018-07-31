#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL H,n;
LL Sum(LL x,LL y){
	return (y)*((x+x+y-1))/(2*1LL);
}
LL ck(LL len){
	if(len<=H){
		return (Sum(1,len));
	}
	else {
		LL tmp=Sum(1,H-1);
		len-=(H-1);
		if(len&1)
			return tmp+Sum(H,len/2+1)+Sum(H,len/2);
		else 
			return tmp+Sum(H,len/2)+Sum(H,len/2);
	}
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%lld%lld",&n,&H);;
	LL r=2*sqrt(n)+2;
	LL l=0;
	LL ans=0;
	while(l<=r){
		LL mid=(l+r)>>1;
		if(n<=ck(mid)){r=mid-1;ans=mid;}
		else l=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}
/*
题意：给定n，H，要求使a数列满足a[1]+a[2]+...+a[x]=n,且a[1]<=H,a[x]=1，|a[i]-a[i+1]|<=1(1<=i<x),求a的项数最小是几。
思路：正向思考得逐步分解n，有点困难，考虑反向思考，先构造出一个长度为x的序列再去判断它的长度是否为n。
但这样也很难，可以先考虑这x长度能达到的最大和，显然H做为a[1]和更大
根据H与x奇偶性有如下两种和最大构造方式：
1.H<H+1<H+2<...<k-1<k>k-1>...>1
2.H<H+1<H+2<...<k-1<k=k>k-1>...>1
我们发现只要n<=最大和，我们都能在这个x长度中构造出（通过调a[1]，与每一项是+1，+0，-1）
如n=最大和-1
可以（假设是第一种构造）：
H<H+1<H+2<...<k-1=k-1=k-1>...>1
n=最大和-2：
H<H+1<H+2<...<k-1>k-2<k-1>...>1
n=最大和-3：
H<H+1<H+2<...<k-2<k-2<k-1=k-1>...>1
n=最大和-M(M>H):
可以调a[1]<H
于是演算过程与答案奇偶性有关，且x越大条件越容易满足，容易想到二分答案。
debug：这个问题中存在着longlong相乘溢出的情况，可以按a[1]=1,a[x]=1,在前一半a每次加1后一半每次减1，这样的和为(x/2)^2=n,可以预处理出二分的一个上界x=2*sqrt(n)。注意29,5,变量定义也要LL
*/
