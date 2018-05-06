#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=100010;
int lowbit(int x){return x&(-x);}
int n,m;
int pos[maxn];
struct Fenwick{
	int c[2*maxn];
	void insert(int x,int y){
		while(x<=2*n){
			c[x]+=y;x+=lowbit(x);
		}
	}
	int sum(int x){
		int r=0;
		while(x>0){
			r+=c[x];x-=lowbit(x);
		}
		return r;
	}
	void init(){
		memset(c,0,sizeof(c));
	}
}val;
int tot;
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--){
		val.init();//tot=n;
		scanf("%d%d",&n,&m);
		tot=n;
		for(int i=1;i<=n;++i){val.insert(n-i+1,1);pos[i]=n-i+1;}
		for(int i=1;i<=m;++i){
			int x;
			scanf("%d",&x);printf ("%d%c", n - val.sum(pos[x]), i == m ? '\n':' ');    
			val.insert(pos[x],-1);
			pos[x]=++tot;
			val.insert(pos[x],1);
		}
	}
	return 0;
}
/*
题意：有编号1~n的n个影碟从上到下排列， 每次取一个影碟并把其放在最上面， 求每次取之前该影碟前面有多少个影碟。







思路：不考虑放在上面的操作，用树状数组维护前缀和即可。
考虑这个操作的话，可以把树状数组开大一倍，把原先的暴力删掉，在后面再加就是。此时的答案即为后缀和，用n减一下前缀和。
debug:insert忘记是两倍n，tot忘修改,insert不是两倍n而是两倍maxn
*/
