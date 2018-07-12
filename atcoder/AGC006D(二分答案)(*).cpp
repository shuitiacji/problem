#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
/**/int a[maxn<<1],mid,n;
int up(int x,int y){
	return a[x]>mid&&a[y]>mid;
}
int down(int x,int y){
	return a[x]<=mid&&a[y]<=mid;
}
int ck(){
	for(int i=n-1;i>=1;--i){
		if(up(i,i+1)||up(2*n-1-i,2*n-i))return 1;
		if(down(i,i+1)||down(2*n-1-i,2*n-i))return 0;
	}
	return up(1,1);
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n*2-1;++i){
		scanf("%d",&a[i]);
	}
	int l=1,r=2*n-1,ans;
	while(l<=r){
		mid=(l+r)>>1;
		if(ck())l=mid+1;
		else r=mid-1,ans=mid;
	}
	cout<<ans<<endl;
	return 0;
}
/*
题意：
给一个n层的金字塔，给出底部的方块数字，其他未知，要求每一个方块都是其下方，下左方和下右方的中位数，输出顶层数字。

思路：
第二次看见这种套路了。
是求一个序列中满足条件的一个数，且如果只有两类数方便处理，想到二分答案转01串。
由上一题可知当两个相同的数挨在一起时，不仅可以一直上去，还能往左右扩展(因为只有01，手玩一下就能发现）。
所以选离中点最近的就行了。

debug:
数组要开maxn*2
*/
