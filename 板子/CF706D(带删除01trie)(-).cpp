#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=222222;
int tot=0,ch[maxn*32][2];
LL val[maxn*32];
void ins(LL x){
	int u=0;
	for(int i=32;i>=0;--i){
		int c=(x>>i)&1;
		if(!ch[u][c]){
			ch[u][c]=++tot;
		}
		u=ch[u][c];
		val[u]++;
	}
}
void del(LL x){
	int u=0;
	for(int i=32;i>=0;--i){
		int c=(x>>i)&1;
		u=ch[u][c];
		val[u]--;
	}
}
void que(LL x){
	int u=0;LL ans=0;
	for(int i=32;i>=0;--i){
		int c=(x>>i)&1;
		if(ch[u][c^1]&&val[ch[u][c^1]]){
			u=ch[u][c^1];
			ans+=((1)<<i);
		}
		else u=ch[u][c];
	}
	printf("%lld\n",ans);
}
char a[10];
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n;
	scanf("%d",&n);
	ins(0);
	for(int i=1;i<=n;++i){
		scanf("%s",a);
		LL x;
		scanf("%lld",&x);
		if(a[0]=='+')ins(x);
		if(a[0]=='-')del(x);
		if(a[0]=='?')que(x);
	}
	return 0;
}
题意：输出已有集合内与x的最大异或和
