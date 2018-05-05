#include<bits/stdc++.h>
using namespace std;
#define next Next
#define hash Has
const int maxn=16777220;
int a[maxn];
int n,tot;
struct node{
	int v,x,y;
}hs[maxn];
int next[maxn],head[maxn];
int hashval(int x){
	if(x<0)x=abs(x);
	return ((x<<1)+(x>>1))&16777215;
}
void hash(int v,int x,int y){
	int hv=hashval(v);
	++tot;
	hs[tot].x=x;hs[tot].y=y;hs[tot].v=v;
	next[tot]=head[hv];
	head[hv]=tot;
}
void init(){
	tot=0;
	memset(head,0,sizeof(head));
	memset(next,0,sizeof(next));
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	while(scanf("%d",&n)!=EOF&&n!=0){
		init();
		for(int i=1;i<=n;++i)scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		for(int i=1;i<n;++i){
			for(int j=i+1;j<=n;++j){
				hash(a[i]+a[j],i,j);
			}
		}
		for(int i=n;i>=1;--i){
			for(int j=1;j<=n;++j){
				if(i==j)continue;
				int val=a[i]-a[j];
				int V=hashval(val);
				for(int k=head[V];k;k=next[k]){
					if(hs[k].v==val){
						if(hs[k].x!=i&&hs[k].x!=j&&hs[k].y!=i&&hs[k].y!=j){
							printf("%d\n",a[i]);
							goto nxt;
						}
					}
				}
			}
		}
		printf("no solution\n");
		nxt:;
	}
	return 0;
}
/*
题意：给定一个集合(N)，求三个数和为另一个数
N=1000;









思路：中间相遇法
先处理a+b后处理d-c，中间在用hash维护
debug：排序记得顺序要检查。。。
*/
