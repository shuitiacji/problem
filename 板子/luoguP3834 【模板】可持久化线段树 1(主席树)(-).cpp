#include<bits/stdc++.h>
using namespace std;
const int maxn=200010;
int ls[maxn*25],rs[maxn*25],rt[maxn],tot,sum[maxn*25],a[maxn],b[maxn];
int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
void upt(int o,int &o1,int l,int r,int p){
	o1=++tot;
	ls[o1]=ls[o];rs[o1]=rs[o];sum[o1]=sum[o]+1;
	if(l==r)return ;
	int mid=(l+r)>>1;
	if(p<=mid)upt(ls[o],ls[o1],l,mid,p);
	else upt(rs[o],rs[o1],mid+1,r,p);
}
int que(int o,int o1,int l,int r,int p){
	if(l==r)return l;
	int tmp=sum[ls[o1]]-sum[ls[o]];
	int mid=(l+r)>>1;
	if(p<=tmp)que(ls[o],ls[o1],l,mid,p);
	else que(rs[o],rs[o1],mid+1,r,p-tmp);
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n=read(),m=read();
	for(int i=1;i<=n;++i){
		a[i]=read();
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	int sz=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;++i){
		upt(rt[i-1],rt[i],1,sz,lower_bound(b+1,b+sz+1,a[i])-b);
	}
	for(int i=1;i<=m;++i){
		int l=read(),r=read(),k=read();
		printf("%d\n",b[que(rt[l-1],rt[r],1,sz,k)]);
	}
	return 0;
}
/*
debug:
5.20
1.24行p-tmp与23行p搞反
2.37行写成b+n+1
3.17行写成p-mid
*/
