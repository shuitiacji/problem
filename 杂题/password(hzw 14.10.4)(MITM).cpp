#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
map<LL,int> hs;
LL ans;
int fg;
LL a[1000];
int n;
LL k;
void dfs(int p,LL sum){
	if(!fg&&p>n/2){
		hs[sum]++;
		return ;
	}
	if(p>n){
		ans+=hs[k-sum];
		return ;
	}
	dfs(p+1,a[p]+sum);
	dfs(p+1,sum);
}
int main(){
	freopen("password.in","r",stdin);
	freopen("password.out","w",stdout);
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;++i)scanf("%lld",&a[i]);
	dfs(1,0);	
	fg=1;
	dfs(n/2+1,0);
	cout<<ans<<endl;
	return 0;
}
/*
关于某种密码有如下描述:某种密码的原文 A 是由 N 个数字组成,而密文 B 是一个长度
为 N 的 01 数串,原文和密文的关联在于一个钥匙码 KEY 。若 KEY=∑  Ai*Bi ,则密文就是原文的一组合法密码。
现在有原文和钥匙码,请编一个程序来帮助他统计到底有多少个符合条件的密文。


思路：
meet in the middle
*/
