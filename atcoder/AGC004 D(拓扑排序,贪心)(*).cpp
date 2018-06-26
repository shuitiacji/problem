#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
struct node{
	int x,y;
	node(int a,int b):x(a),y(b){}
};
int vis[maxn],f[maxn],l[maxn];
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n,k;
	scanf("%d%d",&n,&k);
	scanf("%d",&f[1]);
	for(int i=2;i<=n;++i){
		int x;
		scanf("%d",&x);
		f[i]=x;
		vis[x]++;
	}
	int ans=0;
	if(f[1]!=1)ans++;
	queue<int> q;
	for(int i=1;i<=n;++i){
		if(!vis[i])q.push(i),l[i]=0;
	}
	while(!q.empty()){
		int v=q.front(),h=l[v];q.pop();
		if(h==k-1&&f[v]!=1){
			ans++;
			h=-1;
		}
		if(f[v]!=0&&f[v]!=1){
			l[f[v]]=max(l[f[v]],h+1);
			vis[f[v]]--;
			if(vis[f[v]]==0)q.push(f[v]);
		}
	}
	cout<<ans<<endl;
	return 0;
}
