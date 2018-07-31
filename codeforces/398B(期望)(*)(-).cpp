#include<bits/stdc++.h>
using namespace std;
typedef double db;
const int maxn=2e3+10;
int r[maxn],c[maxn];
db d[maxn][maxn];
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	int t1=n,t2=n;
	for(int i=1;i<=m;++i){
		int a,b;
		scanf("%d%d",&a,&b);
		if(!r[a])r[a]=1,t1--;
		if(!c[b])c[b]=1,t2--;
	}
	for(int i=1;i<=n;++i){
		d[i][0]=d[i-1][0]+(db)n/i;
		d[0][i]=d[0][i-1]+(db)n/i;
	}
	for(int i=1;i<=t1;++i){
		for(int j=1;j<=t2;++j){
			d[i][j]=n*n;
			d[i][j]+=i*j*d[i-1][j-1];
			d[i][j]+=i*(n-j)*d[i-1][j];
			d[i][j]+=(n-i)*j*d[i][j-1];
			d[i][j]/=(n*n-(n-i)*(n-j));
		}
	}
	printf("%.10lf\n",d[t1][t2]);
	return 0;
}
/*
题意：
有一个n*n的方格，有m个方格有颜色，现在随机涂方格，可以重复涂，求使得每行每列至少都有一个方格有颜色的期望步数．

思路：
对于这种末状态确定，初状态步数未知（甚至无限），可以采取倒推．
设d[i][j]表示还有i行j列未有颜色方格时，到末状态的期望步数．
d[i][j]=(1+i*j*d[i-1][j-1]+i*(n-j)*d[i-1][j]+(n-i)*j*d[i-1][j]+(n-i)*(n-j)*dp[i][j])/n*n
但式子中有两个d[i][j]，这里有个技巧，可以通过移项减下系数解决．
最后特殊处理i,j==0的情况
*/
