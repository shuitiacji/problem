#include<bits/stdc++.h>
using namespace std;
int f[5010],c[100010],C[100010],h[12];
int dp(int x,int y){
	memset(f,-1,sizeof(f));
	f[0]=0;
	for(int i=1;i<=x;++i){
		for(int j=y;j>=0;--j){
			if(f[j]!=-1){
				for(int k=1;k<=10;++k)f[j+k]=max(f[j]+h[k],f[j+k]);
			}
		}
	}
	int ans=0;
	for(int i=0;i<=y;++i)ans=max(f[i],ans);
	return ans;
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n*k;++i){
		int x;
		scanf("%d",&x);
		c[x]++;
	}
	for(int i=1;i<=n;++i){
		int x;
		scanf("%d",&x);
		C[x]++;
	}
	for(int i=1;i<=k;++i){
		scanf("%d",&h[i]);
	}
	int ans=0;
	for(int i=1;i<=100000;++i){
		if(C[i]&&c[i])ans+=dp(C[i],c[i]);
	}
	cout<<ans<<endl;
	return 0;
}
/*
题意：
n个人，每个人有个幸运数字。
现有n*k个数字，每个人得到k个。
若k个中有i个此人的幸运数字，对答案产生h[i]的贡献（每个人的h[i]相同）
求可能的最大贡献。

思路：
对每种幸运数字泛化背包dp
*/
