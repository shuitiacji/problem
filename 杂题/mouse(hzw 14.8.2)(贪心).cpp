#include<bits/stdc++.h>
using namespace std;
const int maxn=100100;
struct node{
	int t,v;
	bool operator < (const node &b) const {
		return t<b.t;
	}
}a[maxn];
priority_queue<int,vector<int>,greater<int> > q;
int main(){
	freopen("mouse.in","r",stdin);
	freopen("mouse.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&a[i].t);
	for(int i=1;i<=n;++i)scanf("%d",&a[i].v);
	sort(a+1,a+n+1);
	int now=0,sum=0;
	for(int i=1;i<=n;++i){
		if(now<a[i].t){
			now++;
			sum+=a[i].v;
			q.push(a[i].v);
		}
		else {
			sum+=a[i].v;
			q.push(a[i].v);
			sum-=q.top();q.pop();
		}
	}
	cout<<sum<<endl;
	return 0;
}
/*
题意:伟大的 2320 学长特别喜欢打地鼠游戏,这个游戏开始后,会在地板上冒出一些地鼠
来,你可以用榔头去敲击这些地鼠,每个地鼠被敲击后,将会增加相应的游戏分值。可是
所有地鼠只会在地上出现一段时间(而且消失后再也不会出现),每个地鼠都在 0 时刻冒
出,但停留的时间可能是不同的,而且每个地鼠被敲击后增加的游戏分值也可能是不同。最近 2320 学长经常玩这个游戏,以至于敲击每个地鼠只要 1 秒。他在想如何敲击能使
总分最大。

思路：
贪心，维护两个维度的最优，一是个数最优，可以把时间排序一个一个取，二是权值最优，不断用大的替换小的
按照时间排序，不断取，直到取得个数超过当前时间，把价值最小的删除
用堆维护
debug:
1.堆忘记greater<int>
*/
