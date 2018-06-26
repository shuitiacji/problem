#include<bits/stdc++.h>
using namespace std;
const int maxn=1001000;
int pos[maxn];
struct node{
	int l,r,id;
	bool operator < (const node &b) const {
		if(pos[l]==pos[b.l]){
			if(pos[l]&1)return r<b.r;
			return r>b.r;
		}
		return pos[l]<pos[b.l];
	}
}q[maxn];
int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int Ans;
int cnt[maxn],ans[maxn],a[maxn];
inline void add(int x){
	cnt[a[x]]++;
	if((cnt[a[x]]&1)&&cnt[a[x]]!=1)Ans--;
/**/if(!(cnt[a[x]]&1))Ans++;
}
inline void del(int x){
	cnt[a[x]]--;
	if((cnt[a[x]]&1))Ans--;
	if(!(cnt[a[x]]&1)&&cnt[a[x]]!=0)Ans++;
}
int main(){
	freopen("harem.in","r",stdin);
	freopen("harem.out","w",stdout);
	int n=read(),c=read(),m=read();
	int sz=sqrt(n);
/**/for(int i=1;i<=n;++i)a[i]=read(),pos[i]=i/sz;
	for(int i=1;i<=m;++i){
		q[i].l=read();q[i].r=read();
		q[i].id=i;
	}
	sort(q+1,q+m+1);
	int l=1,r=0;
	for(int i=1;i<=m;++i){
		while(r<q[i].r)add(++r);
		while(r>q[i].r)del(r--);
		while(l>q[i].l)add(--l);
		while(l<q[i].l)del(l++);
		ans[q[i].id]=Ans;
	}
	for(int i=1;i<=m;++i)printf("%d\n",ans[i]);
	return 0;
}
/*
问题简述:n 个数,m 次询问,每次问[l,r]区间有多少个数恰好出现正偶数次
思路：莫队
debug:
1.38行i/sz写成n/sz
2.26行，31行,!要写在括号外面
*/
