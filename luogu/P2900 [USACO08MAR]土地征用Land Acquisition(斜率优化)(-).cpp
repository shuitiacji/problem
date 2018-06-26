#include<bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long LL;
const int maxn=1000000;
struct node{
	int l,w;
	bool operator < (const node &b) const{
/**/	if(l==b.l)return w>b.w;
		return l>b.l;
	}
}ld[maxn],b[maxn];
int q[maxn];
LL dp[maxn];
db slope(int k,int j){
	return (db)(dp[k]-dp[j])/(db)(b[k+1].l-b[j+1].l);
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d %d",&ld[i].l,&ld[i].w);
	}
	sort(ld+1,ld+n+1);
	int top=0;
	for(int i=1;i<=n;++i){
		if(!top||ld[i].w>b[top].w){
			b[++top]=ld[i];
		}
	}
	int l=1,r=1;
	for(int i=1;i<=top;++i){
/**/	while(l<r&&slope(q[l+1],q[l])>-b[i].w)++l;
		dp[i]=dp[q[l]]+(LL)b[q[l]+1].l*b[i].w;
		while(l<r&&slope(i,q[r])>slope(q[r],q[r-1]))--r;
		q[++r]=i;
	}
	cout<<dp[top]<<endl;
	return 0;
}
/*
题意：
约翰准备扩大他的农场，眼前他正在考虑购买N块长方形的土地。如果约翰单买一块土 地，价格就是土地的面积。但他可以选择并购一组土地，并购的价格为这些土地中最大的长 乘以最大的宽。比如约翰并购一块3 × 5和一块5 × 3的土地，他只需要支付5 × 5 = 25元， 比单买合算。 约翰希望买下所有的土地。他发现，将这些土地分成不同的小组来并购可以节省经费。 给定每份土地的尺寸，请你帮助他计算购买所有土地所需的最小费用。

思路：
先发现如果一块土地l，w均比另一块小，这块土地是没有价值的（完全可以把它并到那块大土地上）
根据这个，我们可以把土地变成单调的（l单调下降，w单调上升）
这样就可以斜率优化了

debug：
1.35行，一定要注意因为x单调下降，b[i].w前要加-
2.9行，不能写成小于，因为是严格单调，如果是小于：
1000 1
1000 2
上面两个不严格下降；
写成大于：
1000 2
1000 1
第二个会在处理w时被删掉
*/
