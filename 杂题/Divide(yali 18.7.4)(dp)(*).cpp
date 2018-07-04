#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
const int maxn=2010;
int top=0;
int w[maxn],f[maxn][maxn],g[maxn][maxn],n,m,a[maxn],tmp[maxn];
void Div(int l,int r){
	//cout<<l<<' '<<r<<endl;
	if(l==r){tmp[++top]=0;return ;}
	if(w[l]+w[r]<m)tmp[++top]=0,Div(l+1,r);
	else tmp[++top]=1,Div(l,r-1);
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%d",&w[i]);
	sort(w+1,w+n+1);
	Div(1,n);
	for(int i=1;i<=n;++i){
		a[n-i+1]=tmp[i];
	}
/*	for(int i=1;i<=n;++i)cout<<a[i]<<' ';
	cout<<endl;*/
	memset(f,-0x3f,sizeof(f));
	f[0][0]=0;
	g[0][0]=1;
	for(int i=1;i<=n;++i){
		for(int j=0;j<=i;++j){
			f[i][j]=f[i-1][j]+a[i]*j;
			g[i][j]=g[i-1][j];
			if(j>0){
				if(f[i][j]==f[i-1][j-1]+a[i]*(i-j)){
					g[i][j]=(g[i-1][j-1]+g[i][j])%mod;
				}
//			else{
				if(f[i][j]<f[i-1][j-1]+a[i]*(i-j)){	
					f[i][j]=f[i-1][j-1]+a[i]*(i-j);
					g[i][j]=g[i-1][j-1];
				}
			}
		}
	}
	int ans1=-1,ans2;
	for(int i=0;i<=n;++i){
		if(ans1<f[n][i]){
			ans1=f[n][i];
			ans2=g[n][i];
			continue;
		}
		if(ans1==f[n][i]){
			ans2=(ans2+g[n][i])%mod;
		}
	}
	cout<<ans1<<' '<<ans2<<endl;
	return 0;
}
/*
题意：
共有n艘飞船参与演练，每艘飞船都有一个武力值wi
你需要把它们分成两队，每队飞船数目任意
我们发现，如果两艘飞船i与j的武力值相加不小于m且不在同一队，那么这两艘飞船就能配合默契
请问最多能有多少对飞船配合默契，同时还需要算出有多少种分队方案可以达到此效果

思路：
如果考虑dp，设f[i][j]表示前面已经搞过了i个，有j个在A队，发现这样dp有后效性。
解决后效性，考虑更改dp顺序
首先把w排序
考虑[1,n]这段区间
如果 w1+wn < m，那么w1与区间中所有飞船配合都不默契，递归处理[2,n]
如果 w1+wn >= m，那么wn与区间中所有飞船配合都默契，递归处理[1,n-1]
把每次处理的w依次取出，形成一个新数组，如：w1 w2 wn wn-1 wn-2 w3 w4 w5 w6 wn-3 ...
其实新数组中每个元素大小是多少不重要，重要的是它与后面的飞船是否配合默契（要么都配合默契，要么都不默契）
于是得到了新的布尔数组，再把数组反转一下（原先后的放前面，原先前的放后面），命名为op数组
设f[i][j]表示，考虑完了前i艘飞船，其中有j艘属于A队的最佳默契数
f[i][j]=max(f[i-1][j-1]+op[i]*(i-j), f[i-1][j]+op[i]*j)
方案数也是一样的
设g[i][j]表示默契数为f[i][j]的个数，dp时顺便搞一下即可。

debug:
36行不要见到if就是else
*/
