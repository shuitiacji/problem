#include<bits/stdc++.h>
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
const int maxn=100005,Maxn=1800000;
int tot;
int f[maxn],sum[Maxn],ls[Maxn],rs[Maxn],rt[maxn],hs[maxn];
int find(int x){
	int r=x;
	while(r!=f[r])r=f[r];
	int i=x,j;
	while(i!=r){
		j=f[i];
		f[i]=r;
		i=j;
	}
	return r;
}
void insert(int &o,int l,int r,int k){
	if(!o)o=++tot;
	sum[o]++;
	if(l==r)return ;
	int mid=(l+r)>>1;
	if(k<=mid)insert(ls[o],l,mid,k);
	else insert(rs[o],mid+1,r,k);
}
int que(int o,int l,int r,int k){
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(sum[ls[o]]<k)que(rs[o],mid+1,r,k-sum[ls[o]]);
	else que(ls[o],l,mid,k);
}
int merge(int x,int y){
	if(!x)return y;
	if(!y)return x;
	ls[x]=merge(ls[x],ls[y]);
	rs[x]=merge(rs[x],rs[y]);
	sum[x]=sum[ls[x]]+sum[rs[x]];
	return x;
}
void uni(int x,int y){
	x=find(x);y=find(y);
	if(x==y)return ;
	f[x]=y;
/**/rt[y]=merge(rt[x],rt[y]);
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n=read(),m=read();
	for(int i=1;i<=n;++i){
		int x=read();
		insert(rt[i],1,n,x);
		hs[x]=i;
/**/	f[i]=i;
	}
	for(int i=1;i<=m;++i){
		int x=read(),y=read();
		uni(x,y);	
	}
	int q=read();
	for(int i=1;i<=q;++i){
		char s[10];
		scanf("%s",s);
		int x=read(),y=read();
		if(s[0]=='Q'){
			int X=find(x);
			if(sum[rt[X]]<y){
				puts("-1");
				continue;
			}	
			printf("%d\n",hs[que(rt[X],1,n,y)]);
		}
		else uni(x,y);
	}
	return 0;
}
/*
debug:
6.6
1.59行忘写
2.49行写成merge(x,y)
*/
