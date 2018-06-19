#include<bits/stdc++.h>
using namespace std;
int x[105],y[105],ans[105];
int d[32][20][20][12][105];
void add(int *a,int *b){
	for(int i=1;i<=100;++i)a[i]+=b[i];
	for(int i=1;i<=100;++i){
		a[i+1]+=a[i]/10;a[i]%=10;
	}
}
void mul(int *a,int v){
	for(int i=1;i<=100;++i)a[i]*=v;
	for(int i=1;i<=100;++i){
		a[i+1]+=a[i]/10;a[i]%=10;
	}
}
void sub(int *a,int *b,int *c){
	for(int i=100;i>=1;--i)c[i]=a[i]-b[i];
	for(int i=1;i<=100;++i){
		if(c[i]<0){
			c[i]+=10;
			c[i+1]-=1;
		}
	}
}
int n,k;
void solve(){
	x[1]=1;y[1]=1;
	for(int i=1;i<=n;++i){
		mul(x,9);
		mul(y,10);
	}
	sub(y,x,ans);
	int t=100;
	while(!ans[t])--t;
	for(int i=t;i>=1;--i)printf("%d",ans[i]);
}
int main(){
	freopen("digit.in","r",stdin);
	freopen("digit.out","w",stdout);
	scanf("%d%d",&n,&k);
	if(k==0){solve();return 0;}
	int a2=0,a3=0,a5=0,a7=0;
	while(k%2==0)k/=2,a2++;
	while(k%3==0)k/=3,a3++;
	while(k%5==0)k/=5,a5++;
	while(k%7==0)k/=7,a7++;
	if(k!=1){puts("0");return 0;}
	d[0][0][0][0][1]=1;
	for(int i=1;i<=n;++i){
		for(int j=a2;j>=0;--j){
			for(int q=a3;q>=0;--q){
				for(int K=a5;K>=0;--K){
					for(int A=a7;A>=0;--A){
						if(j>=1)add(d[j][q][K][A],d[j-1][q][K][A]);
						if(j>=2)add(d[j][q][K][A],d[j-2][q][K][A]);
						if(j>=3)add(d[j][q][K][A],d[j-3][q][K][A]);
						if(q>=1)add(d[j][q][K][A],d[j][q-1][K][A]);
						if(q>=2)add(d[j][q][K][A],d[j][q-2][K][A]);
						if(K>=1)add(d[j][q][K][A],d[j][q][K-1][A]);
						if(A>=1)add(d[j][q][K][A],d[j][q][K][A-1]);
/**/					if(j>=1&&q>=1)add(d[j][q][K][A],d[j-1][q-1][K][A]);
					}
				}
			}
		}
	}
	int t=100;
	while(!d[a2][a3][a5][a7][t])t--;
	for(int i=t;i>=1;--i)printf("%d",d[a2][a3][a5][a7][i]);
	return 0;
}
/*
一个数字的数位和乘积为其各位数字的乘积。求所有的 N
位数中有多少个数的数位和乘积恰好为 K。请注意,这里的
N 位数是可以有前导零的。比如 01,02 视为二位数,但是
他们的数位和乘积都是 0。

思路：
k=0
10^n-9^n;

因为位数字只有1-10，k只能由2,3,5,7组成，dp一下即可，状态为2,3,5,7的个数。
高精

debug:
忘记6的情况,62行
*/
