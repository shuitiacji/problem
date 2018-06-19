#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<cstring>
#define top front
using namespace std;
const int maxn=1010;
int xx[4]={1,0,-1,0},yy[4]={0,1,0,-1};
struct node{
	int x,y,z;
	node (int a,int b,int c): x(a),y(b),z(c) {}
};
queue<node> Q;
int vis[maxn][maxn],mp[maxn][maxn];
int n,X,Y,x1,x2,y1,y2;
void pre(){
	while(!Q.empty()){
		int nx=Q.top().x,ny=Q.top().y,nz=Q.top().z;Q.pop();
		for(int i=0;i<=3;++i){
			int tx=nx+xx[i],ty=ny+yy[i],tz=nz+1;
			if(tx>=X||ty>=Y||tx<0||ty<0||mp[tx][ty]!=-1)continue;
			mp[tx][ty]=tz;
			Q.push(node(tx,ty,tz));
		}
	}
}
int ck(int v){
	memset(vis,0,sizeof(vis));
	queue<node> q;
	if(x1==x2&&y1==y2)return 0;
	q.push(node(x1,y1,0));
	vis[x1][y1]=1;
	while(!q.empty()){
		int nx=q.top().x,ny=q.top().y,nz=q.top().z;q.pop();
		for(int i=0;i<=3;++i){
			int tx=nx+xx[i],ty=ny+yy[i],tz=nz+1;
			if(tx>=X||ty>=Y||tx<0||ty<0||vis[tx][ty]||mp[tx][ty]<v)continue;
			vis[tx][ty]=1;
			if(tx==x2&&ty==y2)return tz;
			q.push(node(tx,ty,tz));
		}
	}
	return -1;
}
int main(){
	freopen("escape.in","r",stdin);
	freopen("escape.out","w",stdout);
	scanf("%d%d%d",&n,&X,&Y);
	scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
	memset(mp,-1,sizeof(mp));
	for(int i=1;i<=n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		Q.push(node(x,y,0));
		mp[x][y]=0;
	}
	pre();
	int l=0,r=mp[x1][y1];
	int ans1=0,ans2;
	while(l<=r){
		int mid=(l+r)>>1;
		int t=ck(mid);
		if(t==-1)r=mid-1;
		else {
			l=mid+1;ans1=mid;
			ans2=t;
		}
	}
	cout<<ans1<<' '<<ans2<<endl;
	return 0;
}
/*
题意：
N(1<=N<=10000),X(1<=x<=1000),Y(1<=Y<=1000),代
表有 N 个敌人分布一个 X 行 Y 列的矩阵上,矩形的行号从 0 到 X-1,列号从 0
到 Y-1 再给出四个数字 x1,y1,x2,y2,代表你要从点(x1,y1)移到(x2,y2)。在移
动的过程中你当然希望离敌人的距离的最小值最大化,现在请求出这个值最大
可以为多少,以及在这个前提下,你最少要走多少步才可以回到目标点。注意这
里距离的定义为两点的曼哈顿距离,即某两个点的坐标分为(a,b),(c,d),那么它
们的距离为|a-c|+|b-d|。

思路：
二分答案+bfs
其中一个点到敌人最小距离可以先以敌人为起点跑一次bfs

debug：
一些地方x1,x2,y1,y2分清那个是起点，不要x1,x2为起点
*/
