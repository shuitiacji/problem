#include<bits/stdc++.h>
using namespace std;
#define delta 0.994
typedef double db;
const int maxn=10005;
db ans,ansx,ansy;
struct node{
	db x,y,w;
}a[maxn];
int n;
db energy(db x,db y){
	db sum=0;
	for(int i=1;i<=n;++i){
/**/	db tx=(x-a[i].x)*(x-a[i].x);
/**/	db ty=(y-a[i].y)*(y-a[i].y);
		sum+=sqrt(tx+ty)*a[i].w;
	}
	return sum;
}
db avx,avy;
void sa(){
	db xx=avx,yy=avy;db now=energy(xx,yy);
	db t=19260817;
	while(t>1e-18){
		db tmpx=xx+(rand()*2-RAND_MAX)*t;
		db tmpy=yy+(rand()*2-RAND_MAX)*t;
		db newans=energy(tmpx,tmpy);
		db de=newans-now;
		if(newans<ans){
			ans=newans;
			ansx=tmpx;
			ansy=tmpy;
		}
		if(de<0||exp(-de/t)*RAND_MAX>rand()){
			now=newans;
			xx=tmpx;
			yy=tmpy;
		}
		t*=delta;
	}
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%lf%lf%lf",&a[i].x,&a[i].y,&a[i].w);
		avx+=a[i].x;avy+=a[i].y;
	}
	avx/=1.0*n;avy/=1.0*n;
/**/ans=energy(avx,avy);ansx=avx;ansy=avy;
	srand(19260817);
	int T=5;
	while(T--){
		sa();
		for(int i=1;i<=5;++i)srand(rand());
	}
	printf("%.3lf %.3lf\n",ansx,ansy);
	return 0;
}
/*
debug:
6.9
1.ans不能定义成0x3f3f3f3f，因为有可能答案大于这个
2.14,15 db写成int
3.rand()是正数，要用rand()*2-RAND_MAX，这是-RAND_MAX->RAND_MAX
4.随机数种子最好不要time(NULL)
5.now与ans，xx、yy与ansx、ansy分清
*/
