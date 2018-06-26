#include<bits/stdc++.h>
using namespace std;
typedef double db;
#define eps 1e-5
struct node1{
	db x,r;
}s[10];
struct node2{
	db x,R,l,r;
	bool operator < (const node2 &b) const{
		return r<b.r;
	}
}y[10];
db x0,h;
int vis[10];
int ck(db x){
	for(int i=1;i<=7;++i){
		y[i].x=s[i].x;y[i].R=s[i].r+x;
		db tmp=sqrt(y[i].R*y[i].R-h*h);
		y[i].l=y[i].x-tmp;y[i].r=y[i].x+tmp;
	}
	sort(y+1,y+8);
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=7;++i)if(y[i].l<0)vis[i]=1;
	for(int i=2;i<=7;++i){
		for(int j=1;j<i;++j){
			if(y[j].r>=y[i].l)vis[i]=max(vis[i],vis[j]);
		}
	}
	for(int i=1;i<=7;++i)if(vis[i]&&y[i].r>x0)return 1;
	return 0;
}
int main(){
	freopen("rainbow.in","r",stdin);
	freopen("rainbow.out","w",stdout);
	scanf("%lf%lf",&h,&x0);
	for(int i=1;i<=7;++i){
		scanf("%lf%lf",&s[i].x,&s[i].r);
	}
	db l=0,r=x0;
	while(l+eps<=r){
		db mid=(l+r)/2.0;
		if(ck(mid))r=mid;
		else l=mid;
	}
	printf("%.2lf\n",l);
	return 0;
}
题意：探险队员们跟随两位护法来到了七色虹前。 七色虹， 就是平面直角坐标系中赤橙黄绿青
蓝紫七个半圆，第 i 座(1<=i<=7)半圆形彩虹的圆心是(xi,0)，半径是 ri，半圆上所有点的纵坐
标均为非负数。探险队员可以看做一条竖直的、长度等于身高的线段，线段的底端纵坐标为
0，最高的一位探险队员的身高为 h。
现在探险队员们要从(0,0)穿越七色虹到达(x0,0)，穿越七色虹的过程中，探险队员的整
个身体必须始终在至少一个半圆形彩虹的内部。由于彩虹的半径 ri 可能太小了，不足以满
足这个条件，因此两位护法决定帮助他们把所有彩虹的半径都增大一个非负实数 r。探险队
员们想知道，r 最小是多少呢？
思路：二分答案
