#include<bits/stdc++.h>
using namespace std;
const int maxn=5000039;
int n,m;
int vis[maxn],mak[maxn],ans;
void dfs(int x){
	if(vis[x])return ;
	vis[x]=1;
	for(int i=0;i<n;++i){
		if(x&(1<<i))
			dfs(x^(1<<i));
	}
	if(mak[x])dfs((1<<n)-1-x);
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int x;
		scanf("%d",&x);
		mak[x]++;
	}
	for(int i=0;i<(1<<n);++i){
		if(mak[i]&&!vis[i]){
			ans++;
			dfs((1<<n)-1-i);
		}
	}
	cout<<ans<<endl;
	return 0;
}
/*
题意：给出一种新的建边方式，若两点的权值&为0，则建边。给出权值范围2^n，与m个点的权值，求图中联通块的个数。

思路：
算是一种套路题吧。
尽可能的少建边，来提高效率。
考虑暴力，n^2建边肯定效率低下，因为我们只要维护连通性，像是已有1010->1，1->100，就不必1010->100。
对于权值x，现将它1,0反一下（即2^n-1-x），不妨令它为1010。那么对于0000,1000,0010,1010都可以连边，即每一位的1可以选或不选，0必须为0。考虑上述重复的边是如何产生的，像1010->1000,1000->0000,1010->0000。可以类比一下，一些状压dp的转移方式，每次只消除一个1（因为顺序对答案不产生影响，只考虑连通性），这样像1010->0000这样的边就不会产生，边数少了很多（极限为2^n*n）
最后灌水dfs求联通块即可。
*/

