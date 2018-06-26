#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
typedef long long LL;
const int maxn=60100;
LL ans=0;int h,x1,x2;
vector<int> point[maxn];
int mina[maxn];
void init(){
	ans=0;
	memset(mina,0x3f,sizeof(mina));
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int t;
	scanf("%d",&t);
	while(t--){
		init();
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;++i){
			int x,y;
			scanf("%d%d",&x,&y);
			if(i==1)h=y;
			if(i==1)x1=x;
			if(i==2)x2=x;
			point[x].push_back(y);
		}
		if(x1>x2)swap(x1,x2);
		for(int i=x1;i<=x2;++i){
			for(int j=0;j<point[i].size();++j){
				int tmp=abs(point[i][j]-h);
				mina[i]=min(mina[i],tmp);
				if(tmp==0)mina[i]=0;
			}
			mina[i]=min(mina[i],mina[i-1]+1);
		}
		for(int i=x2;i>=x1;--i){
			for(int j=0;j<point[i].size();++j){
				int tmp=abs(point[i][j]-h);
				mina[i]=min(mina[i],tmp);
				if(tmp==0)mina[i]=0;
			}
			mina[i]=min(mina[i],mina[i+1]+1);
			if(mina[i]!=0)
				ans+=2LL*mina[i]-1;
		}
		for(int i=0;i<=m;++i)point[i].clear();
		printf("%lld\n",ans);
	}
	return 0;
}
/*
题意：题意：给定A，B公寓和一些餐馆坐标，要在要么比A或要么比B近的位置（曼哈顿距离）建新餐馆，问有几个位置。
思路：首先注意这不是欧几里得距离。根据题意，x坐标不在AB横坐标之间的点可以排除掉。其次，由于AB处于同意水平之上，可以分在上面与下面讨论。对于只在一边的餐馆，其本身坐标以及其左上或右上(左下或右下)的点均不会满足要求。从整体上看，两边的点数必须对称，（不对称多出来的点不会优）。维护一根扫描线，线上处理这一列的上下两边能取的最小值。可以先正序扫一遍，维护餐馆右上不优的情况，倒序扫一遍维护左上不优的情况。
debug：没考虑对称
*/
