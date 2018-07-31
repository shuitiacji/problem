#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
typedef long long LL;
struct node{
	int x,y,z,sz,id;
	bool operator < (const node &B) const{
		if(x==B.x&&y==B.y)return z<B.z;
		if(x==B.x)return y<B.y;
		return x<B.x;
	}
	bool operator == (const node &B) const{
		return (x==B.x)&&(y==B.y)&&(z==B.z);
	}
}ts;
int c[maxn];LL f[maxn];node a[maxn],b[maxn],C[maxn];
int n,k;
int lowbit(int x){
	return x&(-x);
}
void upt(int x,int v){
/**/while(x<=k){
		c[x]+=v;x+=lowbit(x);
	}
}
int que(int x){
	int ret=0;
	while(x){
		ret+=c[x];x-=lowbit(x);
	}
	return ret;
}
void cdq(int l,int r){
	if(l==r)return ;
	int mid=(l+r)>>1;
	cdq(l,mid);cdq(mid+1,r);
	int tmpl=l,tmpr=mid+1,tmp=l;
	while(tmpl<=mid&&tmpr<=r){
		if(a[tmpl].y>a[tmpr].y){
			b[tmp]=a[tmpr];
/**/		f[a[tmpr].id]+=que(a[tmpr].z);
			++tmpr;
		}
		else b[tmp]=a[tmpl],upt(a[tmpl].z,a[tmpl].sz+1),tmpl++;
		++tmp;
	}
	int TMP=tmpl;
	for(int i=tmp;i<=r;++i){
		if(tmpl<=mid){
			b[i]=a[tmpl];
			tmpl++;
		}
		else {
			b[i]=a[tmpr];
/**/		f[a[tmpr].id]+=que(a[tmpr].z);
			tmpr++;
		}
	}
/**/for(int i=l;i<=TMP-1;++i)upt(a[i].z,-a[i].sz-1);
	for(int i=l;i<=r;++i)a[i]=b[i];
}
map<int,LL> d;
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i){
		scanf("%d%d%d",&C[i].x,&C[i].y,&C[i].z);
	}
	sort(C+1,C+n+1);
	int top=1;a[1]=C[1];a[1].id=1;
	for(int i=2;i<=n;++i){
		if(a[top]==C[i])a[top].sz++;
		else a[++top]=C[i],a[top].id=top;
	}
	ts.x=1;ts.y=2;ts.z=1;
	cdq(1,top);	
	for(int i=1;i<=top;++i){
		d[f[a[i].id]+a[i].sz]+=a[i].sz+1;
	}
	for(int i=0;i<n;++i){
		printf("%lld\n",d[i]);
	}
	return 0;
}
/*
debug:
6.29
1.要去重
2.归并排序中的位置不代表最后的位置，一定要记id
3.59行不是tmpl
*/
