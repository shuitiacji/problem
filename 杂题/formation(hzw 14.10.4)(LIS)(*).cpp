#include<bits/stdc++.h>
using namespace std;
const int maxn=50010;
int d;
int p[maxn],c[maxn],a[maxn];
int find(int x){
	int l=1,r=d;int ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(a[mid]<x)ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans+1;
}
int main(){
	freopen("formation.in","r",stdin);
	freopen("formation.out","w",stdout);
	int n,x;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&x);
		p[x]=i;
	}
	for(int i=1;i<=n;++i){
		scanf("%d",&x);
		c[i]=p[x];
	}
	d=1;a[1]=c[1];
	for(int i=2;i<=n;++i){
		int j=find(c[i]);
		a[j]=c[i];
		if(j>d)d++;
	}
	cout<<d<<endl;
	return 0;
}
/*
题意：
N 个编号为 1-n 的球,每个球都有唯一的编号。这些球被排成两种序列,分别为 A 、 B
序列,现在需要重新寻找一个球的序列 l ,对于这个子序列 l 中任意的两个球,要求
j,k(j<k) ,都要求满足 lj 在 A 中位置比 lk 在 A 中位置靠前,却 lj 在 B 中位置比 lk 在
B 中位置靠前,请你计算这个子序列 l 的最大长度。

思路：
将a[i]在b数组中的位置记为c[i]
求c的最长上升子序列

*/
