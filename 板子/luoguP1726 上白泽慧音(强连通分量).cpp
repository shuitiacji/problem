#include<bits/stdc++.h>
using namespace std;
#define next Next 
#define pb push_back
const int maxn=5010,maxm=5000000;
int e;
int to[maxm],next[maxm],head[maxn];
void add(int x,int y){
	to[++e]=y;
	next[e]=head[x];
	head[x]=e;
}	
int dfn[maxn],low[maxn],tim,vis[maxn],ins[maxn],sta[maxn],top,tot,ansz,anssz,ans;
vector<int> scc[maxn];
void dfs(int u){
	dfn[u]=low[u]=++tim;
	ins[u]=1;
	sta[++top]=u;
	for(int i=head[u];i;i=next[i]){
		int v=to[i];
		if(!dfn[v]){
			dfs(v);
			low[u]=min(low[v],low[u]);
		}
		else {
			if(ins[v])low[u]=min(dfn[v],low[u]);
		}
	}
	if(dfn[u]==low[u]){
		tot++;
		int z=0x3f3f3f3f;
		while(1){
			scc[tot].pb(sta[top]);
			z=min(z,sta[top]);
			ins[sta[top]]=0;
			if(sta[top]==u)break;
			top--;
		}
		top--;
		if(scc[tot].size()>anssz){
			anssz=scc[tot].size();
			ans=tot;
			ansz=z;
		}
		else if(scc[tot].size()==anssz&&z<ansz){
			ans=tot;
			ansz=z;
		}
	}
}
int main(){
	freopen("classroom.in","r",stdin);
	freopen("classroom.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y);
		if(z==2)add(y,x);
	}
	for(int i=1;i<=n;++i){
		if(!dfn[i])dfs(i);
	}
	printf("%d\n",scc[ans].size());
	sort(scc[ans].begin(),scc[ans].end());
	for(int i=0;i<scc[ans].size();++i){
		printf("%d ",scc[ans][i]);
	}
	return 0;
}
