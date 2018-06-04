#include<bits/stdc++.h>
using namespace std;
const int maxn=10010,maxm=maxn<<1;
int to[maxm],next[maxm],head[maxn],w[maxm],d[maxn],f[maxn];
int flag,e;
void add(int x,int y,int z){
	to[++e]=y;
	next[e]=head[x];
	head[x]=e;
	w[e]=z;
}
void spfa(int u){
	f[u]=1;
	for(int i=head[u];i;i=next[i]){
		int v=to[i];
		if(d[v]>d[u]+w[i]){
			if(f[v]||flag){flag=1;return ;}
			d[v]=d[u]+w[i];
			spfa(v);
		}
	}
	f[u]=0;
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int x,y,z,t;
		scanf("%d%d%d",&x,&y,&z);
		if(x==1)scanf("%d",&t),add(y,z,-t);
		if(x==2)scanf("%d",&t),add(y,z,t);
		if(x==3)add(y,z,0),add(z,y,0);
	}
	flag=0;
	for(int i=1;i<=n;++i){
		d[i]=0;
		spfa(i);
		if(flag==1)break;
	}
	if(flag==1)puts("No");
	else puts("Yes");
	return 0;
}
