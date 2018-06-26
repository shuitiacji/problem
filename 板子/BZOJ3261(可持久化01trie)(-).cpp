
#include<bits/stdc++.h>
using namespace std;
const int maxn=600010;
int a[maxn],b[maxn],ch[maxn*30][2],sum[maxn*30],rt[maxn];
int tot;
void upt(int o,int &y,int v){
	y=++tot;int o1=y;
	for(int i=23;i>=0;--i){
		ch[o1][0]=ch[o][0];ch[o1][1]=ch[o][1];
		sum[o1]=sum[o]+1;
		int d=0;
		if((1<<i)&v)d=1;
		ch[o1][d]=++tot;
		o1=tot;
		o=ch[o][d];
	}
/**/sum[o1]=sum[o]+1;
}
void que(int o,int o1,int v){
	int tmp=0;
	for(int i=23;i>=0;--i){
		int d=0;
		if((1<<i)&v)d=1;
		if(sum[ch[o1][d^1]]-sum[ch[o][d^1]]){
			tmp+=1<<i;o=ch[o][d^1];o1=ch[o1][d^1];
		}
/**/	else o=ch[o][d],o1=ch[o1][d];
	}
	printf("%d\n",tmp);
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	n++;
	for(int i=2;i<=n;++i)scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)b[i]=b[i-1]^a[i];
	for(int i=1;i<=n;++i){
		upt(rt[i-1],rt[i],b[i]);
	}
	for(int i=1;i<=m;++i){
		char s[5];
		scanf("%s",s);
		int x,y,z;
		if(s[0]=='A'){
			scanf("%d",&x);
			n++;
			b[n]=b[n-1]^x;
			upt(rt[n-1],rt[n],b[n]);
		}
		else {
			scanf("%d%d%d",&x,&y,&z);
			que(rt[x-1],rt[y],b[n]^z);
		}
	}
	return 0;
}
/*
debug:
5.29
1.17行忘写
2.27行写成o1=ch[o1][d^1]
3.36与37没有像现在这样处理去加个0入trie
*/
