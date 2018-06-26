#include<bits/stdc++.h>
using namespace std;
#define pow POOOW
typedef long long LL;
const int maxn=2e5+5;
const LL seed=13,mod=1e9+7;
LL pow[maxn],Hash[maxn][30],t1[30],t2[30];
char s[maxn];
int n,m;
void sol(){
	int x,y,len;
	scanf("%d%d%d",&x,&y,&len);
	for(int i=0;i<26;++i){
		t1[i]=(Hash[x+len-1][i]-Hash[x-1][i]*pow[len]%mod+mod)%mod;
		t2[i]=(Hash[y+len-1][i]-Hash[y-1][i]*pow[len]%mod+mod)%mod;
	}
	sort(t1,t1+26);
	sort(t2,t2+26);
	for(int i=0;i<26;++i){
		if(t1[i]!=t2[i]){
			puts("NO");
			return ;
		}
	}
	puts("YES");
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	pow[0]=1;
	for(int i=1;i<=maxn;++i)pow[i]=(pow[i-1]*seed)%mod;
	for(int i=1;i<=n;++i){
		for(int j=0;j<26;++j){
			Hash[i][j]=(Hash[i-1][j]*seed+(s[i]==('a'+j)))%mod;
		}
	}
	for(int i=1;i<=m;++i){
		sol();
	}
	return 0;
}
/*
题意：给你一个长度为n的字符串， m次询问， 每次输入一个s, t, l,找到一种字母之间的映射 使的 [s,s+l-1] 与 [t,t+l-1] 里面的字符一一对应。并且只能一对一 不能一对多也不能多对一。
思路：既然是字符之间的一一映射，可以每次挑一个字母出来，hash一下它在这段中的排列，再找一下在另一段中有没有与它hash值相同的，这个判断可以把两段的hash值排个序比一下。但如果hash值暴力算没有任何意义，可以像前缀和一样存一下。
debug：数组下标为负,sort
1.s从0->n-1，导致Hash[x-1][...]下标爆负
2.写成sort(t1,t1+25)
*/
