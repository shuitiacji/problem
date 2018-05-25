#include<bits/stdc++.h>
using namespace std;
const int maxn=500010;
struct node{
	int id,val;
}q[maxn];
int dis[maxn],val[maxn],dp[maxn];
int n,d,k;
void print(int l,int r){
	for(int i=l;i<=r;++i)printf("%d ",q[i].val);
	cout<<endl;
}
int ck(int x){
	int l=1,r=0,tmp=0,ans=-0x3f3f3f3f;q[1].val=0;q[1].id=0;
	for(int i=1;i<=n;++i){
		while(tmp<=i-1&&(dis[tmp]+max(1,d-x)<=dis[i])){
			tmp++;
			if(dp[tmp-1]==-0x3f3f3f3f)continue;
			while(l<=r&&(q[r].val<=dp[tmp-1]))--r;
			q[++r].id=dis[tmp-1];q[r].val=dp[tmp-1];
		}
		while(l<=r&&(q[l].id+max(1,d-x)>dis[i]||q[l].id+d+x<dis[i]))++l;
		if(l>r)
			dp[i]=-0x3f3f3f3f;			
		else dp[i]=q[l].val+val[i];
		ans=max(dp[i],ans);
	}
	return k<=ans;
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d%d",&n,&d,&k);
	for(int i=1;i<=n;++i){
		scanf("%d%d",&dis[i],&val[i]);
	}
	int l=0,r=dis[n]+1,ans;	
	if(!ck(r)){ans=-1;goto nxt;}
	while(l<=r){
		int mid=(l+r)>>1;
		if(ck(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	nxt:;
	printf("%d\n",ans);	
	return 0;
}
/*
思路：单调队列+dp，二分答案
debug：看清题！！不是从第一个格子开始，而是从第0个开始
*/
