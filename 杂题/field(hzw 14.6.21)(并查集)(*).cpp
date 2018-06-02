#include<bits/stdc++.h>
using namespace std;
const int maxn=5010;
int f[maxn*2+11],d[maxn][maxn];
int find(int x){
	int r=x;
	while(f[r]!=r)r=f[r];
	int i=x,j;
	while(i!=r){
		j=f[i];
		f[i]=r;
		i=j;
	}
	return r;
}
void uni(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx==fy)return;
	f[fy]=fx;
}
inline int Max(int x,int y){
	return x>y?x:y;
}
int main(){
	freopen("field.in","r",stdin);
	freopen("field.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=1;i<=maxn*2+10;++i)f[i]=i;
	for(int i=1;i<=n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		uni(x,y+maxn);
	}
	int ans=0;
	for(int i=1;i<=5000;++i){
		for(int j=1;j<=5000;++j){
			if(find(i)==find(j+maxn))
				d[i][j]=d[i-1][j-1]+1;
			else d[i][j]=Max(d[i-1][j],d[i][j-1]);
			ans=max(d[i][j],ans);
		}
	}
	cout<<ans<<endl;
	return 0;
}
/*
题意：给你一些点，并且对于A(a1,a2),B(b1,b2),C(c1,c2),若存在a1==b1,b2==c2,则添加一点D(c1,a2)。求从原点开始的一条路径，使得经过的点所占的行数与列数的最小值尽可能大，输出这个最大值，且这个路径不能是u型的即每次y+1或x+1或x+1&&y+1。

思路：不考虑加点的话，求最大值直接按题意搞即可。
考虑如何快速加点
只考虑那个B点，它的y坐标上要有其他点，x坐标上也要有其他点，并且两两要配对去生成点，但这样很慢。
正解是把所有的列和行抽象成一个个数，用并查集维护行与列的连通性。对于点(a,b),把a列与b行在并查集中连一下，那么如果a1列b1行在并查集中联通，则(a1,b1)存在。不难发现这样搞，直接就自动把点加上去了。
*/
