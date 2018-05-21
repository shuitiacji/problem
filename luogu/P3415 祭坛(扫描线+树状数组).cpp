#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
int c[maxn<<1],down[maxn],up[maxn],a[maxn],b[maxn],l[maxn],r[maxn],val[maxn],cnt[maxn];
vector<int> poi[maxn];
int n,m;
int lowbit(int x){return x&(-x);}
void Add(int x,int v){
	while(x<=m){
		c[x]+=v;x+=lowbit(x);
	}
}
void add(int x,int p){
	if(val[x]==p)return ;
	if(p)Add(x,1);
	else Add(x,-1);
	val[x]=p;
}
int Que(int x){
	int ret=0;
	while(x){
		ret+=c[x];x-=lowbit(x);
	}
	return ret;
}
int que(int l,int r){
	if(l>r)return 0;
	return Que(r)-Que(l);
}
void init(){
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(val,0,sizeof(val));
	memset(c,0,sizeof(c));
}	
int ck(int t){
	if(t==0)return 0;
	init();
	for(int i=1;i<=m;++i)up[i]=0,down[i]=cnt[i];
	for(int i=1;i<=m;++i){
		if(poi[i].size()<2*t)l[i]=m+1,r[i]=0;
		else {
			l[i]=poi[i][t-1]+1;
			r[i]=poi[i][poi[i].size()-t]-1;
		}
	}
	int sum=0;
	for(int i=1;i<=m;++i){
		vector<int> vis;
		for(int j=0;j<poi[i-1].size();++j){
			int y=poi[i-1][j];
			up[y]++;
			vis.push_back(y);
			if(t<=up[y])a[y]=1;
			else a[y]=0;
		}
		for(int j=0;j<poi[i].size();++j){
			int y=poi[i][j];
			vis.push_back(y);
			down[y]--;
			if(t<=down[y])b[y]=1;
			else b[y]=0;
		}
		for(int j=0;j<vis.size();++j){
			int y=vis[j];
			add(y,a[y]+b[y]==2);
		}
		sum+=que((l[i]-1),r[i]);
	}
	return sum;
}
int read(){
	int x=0;char c=getchar();
	while(!isdigit(c))c=getchar();;
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x;
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	n=read();
	for(int i=1;i<=n;++i){
		int x,y;
		x=read();y=read();
		x++;y++;
		poi[x].push_back(y);
		cnt[y]++;
	}
	m=n+1;
	for(int i=1;i<=m;++i)sort(poi[i].begin(),poi[i].end());
	int l=0,r=m,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(ck(mid))l=mid+1,ans=mid;
		else r=mid-1;
	}
	printf("%d\n%d\n",ans,ck(ans));
	return 0;
}
/*
题意:在平面内找一点，使得它的四个正方向上的点的数量的最小值最大
思路：先考虑二分一个答案，扫描线维护一个行的维度，自上而下扫下来，并根据二分的答案处理当前线上可行的一个区间，用一个BIT维护列的维度，同时可以处理出每个当前线上的点的up和down即这个点上面有多少与下面有多少，根据up与down确定这列所在是否可行，用此更新BIT，最后求一下这个扫描线上可行区间内的区间和，加到总的答案当中。
debug：
1.41行，l[i]与r[i]搞反
2.65行，y=poi[i][j]
*/
