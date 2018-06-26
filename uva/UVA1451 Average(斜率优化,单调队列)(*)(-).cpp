#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cctype>
using namespace std;
const int maxn=100000+5;
int sum[maxn],p[maxn];
int comp(int x,int y,int x1,int y2){
	return (sum[y]-sum[x-1])*(y2-x1+1)-(sum[y2]-sum[x1-1])*(y-x+1);
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int t;
	scanf("%d",&t);
	while(t--){
		int n,L;
		scanf("%d%d",&n,&L);
		string s;
		cin>>s;
		sum[0]=0;
		for(int i=0;i<n;++i){
			sum[i+1]=sum[i]+s[i]-'0';
		}
		int i=0,j=0;
		int ansl=1,ansr=n;
		for(int t=L;t<=n;++t){
			while(j-i>1&&comp(p[j-2],t-L,p[j-1],t-L)>=0)--j;
			p[j++]=t-L+1;
			while(j-i>1&&comp(p[i],t,p[i+1],t)<=0)++i;
			int c=comp(p[i],t,ansl,ansr);
			if(c>0||(c==0&&t-p[i]<ansr-ansl)){
				ansl=p[i];ansr=t;
			}
		}
		printf("%d %d\n",ansl,ansr);
	}
	return 0;
}
/*
题意：给定一个长度为n 的01串, 找一个长度不小于L的子串让里面1的比例最大，如果有多个，找长度最短的，如果还有多个，找最靠前的。
思路：紫书243
debug:30行j++写成++j
*/
