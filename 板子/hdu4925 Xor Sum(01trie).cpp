#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=100005;
typedef long long LL;
int ch[maxn*32][2],tot;LL val[maxn*32];
void ins(LL x){
	int u=0;
	for(int i=32;i>=0;--i){
		int c=(x>>i)&1;
		if(!ch[u][c]){
			memset(ch[++tot],0,sizeof(ch[tot]));
			ch[u][c]=tot;
			val[tot]=0;
		}
		u=ch[u][c];
	}
	val[u]=x;
}
LL query(LL x){
	int u=0;
	for(int i=32;i>=0;--i){
		int c=(x>>i)&1;
		if(ch[u][c^1])u=ch[u][c^1];
		else u=ch[u][c];
	}
	return val[u];
}
void init(){
	tot=0;
	memset(ch[0],0,sizeof(ch[0]));
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int t;
	scanf("%d",&t);
	int id;
	while(++id<=t){
		init();
		printf("Case #%d:\n",id);
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i){
			LL x;
			scanf("%lld",&x);
			ins(x);
		}
		for(int i=1;i<=m;++i){
			LL x;
			scanf("%lld",&x);
			printf("%lld\n",query(x));
		}
	}
	return 0;
}
