#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=50010;
int n,m,R;
int f[maxn];
struct node{
	int u,v,w;
	bool operator < (const node &b) const{
		return w>b.w;
	}
}e[maxn];
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
void init(){
	for(int i=0;i<n+m;++i){
		f[i]=i;
	}
}
int main(){
	freopen("conscription.in","r",stdin);
	freopen("conscription.out","w",stdout);
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&m,&R);
		init();
		for(int i=1;i<=R;++i){
			scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
		}
		LL ans=1LL*(m+n)*10000;
		sort(e+1,e+R+1);
		for(int i=1;i<=R;++i){
			int fx,fy;
			if((fx=find(e[i].u))!=(fy=find(e[i].v+n))){
				f[fx]=fy;
				ans-=e[i].w;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
/*
题意：征召N名女兵，M名男兵，每征召一个人花费10000美金，其中一些男兵女兵关系密切，则征召每个人的费用为10000-（已经征召的人中和自己亲密度的最大值），要求通过适当的征召顺序使得征召所有人的总费用最少，输出总费用
思路：
由于一个人只能找之前另一个人，容易想到树，最大生成树即可。
*/
