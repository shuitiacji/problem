#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL ans,f[22],a[12],c[12];
LL C(int i,int j){
	return f[j]/f[i]/f[j-i];
}
void dfs(int u){
	if(u==11){
		LL s=0;
		for(int i=1;i<=10;++i)s+=a[i];
		LL k=f[s];
		for(int i=1;i<=10;++i)k/=f[a[i]];
		if(!c[0])ans+=k;
		else {
			for(int i=1;i<=c[0];++i)ans+=k*C(s-1,i+s-1);
		}
		return ;
	}
	for(int i=1;i<=c[u];++i){
		a[u]=i;
		dfs(u+1);
	}
	if(!c[u])dfs(u+1);
}
char A[20];
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	f[0]=f[1]=1;
	for(int i=2;i<=20;++i)f[i]=f[i-1]*i;
	scanf("%s",A);
	for(int i=0;i<strlen(A);++i)c[A[i]-'0']++;
	dfs(1);
	cout<<ans<<endl;
	return 0;
}
/*
题意：
给你一个数A，要求有多少个数满足每个数位上的数字要在A中出现，且出现的次数不能比A中的大（不含前导零）

思路：
先爆搜每种数字出现的个数，然后组合一下（有0就特殊搞一下）
*/
