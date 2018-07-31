#include<bits/stdc++.h>
using namespace std;
void godie(){
	puts("Impossible");
	exit(0);
}
const int maxn=110;
int n,a[maxn],s[maxn];
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d",&n);
	int d=0;
	for(int i=1;i<=n;++i)scanf("%d",&a[i]),d=max(a[i],d),s[a[i]]++;
	if(d&1){
		for(int i=d-d/2;i<=d;++i){
			s[i]-=2;if(s[i]<0)godie();
		}
		for(int i=d-d/2;i;--i)if(s[i])godie();
	}
	else {
		if(!s[d/2])godie();
		--s[d/2];
		for(int i=d/2+1;i<=d;++i){
			s[i]-=2;if(s[i]<0)godie();
		}
		for(int i=d/2;i;--i)if(s[i])godie();
	}
	puts("Possible");
	return 0;
}
/*
题意：
给你一列数a，求构造出一棵树使每个点i与其最远点的距离等于a[i]，所有边的长度为1，问有没有可能构造出来

思路：
一个性质是每个点的最远点一定是直径的端点。
然后我们找出直径长度，要求能构造出这条直径（每种距离都有2个点，当然直径中心只需要1个(也有可能有两个(奇偶))）。
然后其余点都可以直接接在直径上，因此到最远点的距离不能少于直径长度的一半(分直径长度的奇偶讨论）。
满足就能构造。
*/
