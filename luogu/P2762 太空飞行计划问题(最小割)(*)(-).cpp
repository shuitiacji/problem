#include<bits/stdc++.h>
using namespace std;
#define next Next
const int maxn=2000,maxm=maxn;
int s,t;
struct Dinic{
	int e;
	int to[maxm],head[maxn],cur[maxn],cap[maxm],next[maxm],flow[maxm],d[maxn],vis[maxn];
	void add(int x,int y,int z){
		to[++e]=y;
		next[e]=head[x];
		head[x]=e;
		cap[e]=z;
		to[++e]=x;
		next[e]=head[y];
		head[y]=e;
		cap[e]=0;
	}
	int bfs(){
		memset(vis,0,sizeof(vis));
		vis[s]=1;d[s]=0;
		queue<int> q;q.push(s);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=head[u];i!=-1;i=next[i]){
				int v=to[i];
				if(!vis[v]&&flow[i]<cap[i]){
					vis[v]=1;
					d[v]=d[u]+1;
					q.push(v);
				}
			}
		}
		return vis[t];
	}
	int dfs(int x,int a){
		if(x==t||a==0)return a;
		int FLOW=0,f;
		for(int &i=cur[x];i!=-1;i=next[i]){
			int v=to[i];
			if(d[v]==d[x]+1&&(f=dfs(v,min(a,cap[i]-flow[i])))>0){
				FLOW+=f;
				flow[i]+=f;
				flow[i^1]-=f;
				a-=f;
				if(a==0)break;
			}
		}
		return FLOW;
	}
	int gao(){
		int ret=0;
		while(bfs()){
			for(int i=s;i<=t;++i)cur[i]=head[i];
			ret+=dfs(s,0x3f3f3f3f);
		}
		return ret;
	}
}T;
char c[10010];
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	T.e=-1;
	memset(T.head,-1,sizeof(T.head));
	int m,n;
	scanf("%d%d",&m,&n);
	s=0;t=m+n+1;
	int sum=0;
	for(int i=1;i<=m;++i){
		int C;
		scanf("%d",&C);
		sum+=C;
		T.add(s,i,C);
		memset(c,0,sizeof(c));
        cin.getline(c,10000);
        int ulen=0,num;
        while (sscanf(c+ulen,"%d",&num)==1)
        {
			T.add(i,num+m,0x3f3f3f3f);
            if (num==0) ulen++;
            else while (num)
            {
                num/=10;
                ulen++;
            }
            ulen++;
        }
    }
	for(int i=1;i<=n;++i){
		int C;
		scanf("%d",&C);
		T.add(i+m,t,C);
	}
	int ans=sum-T.gao();
	for(int i=1;i<=m;++i){
		if(T.vis[i]){
			printf("%d ",i);
		}
	}
	cout<<endl;
	for(int i=m+1;i<=m+n;++i){
		if(T.vis[i]){
			printf("%d ",i-m);
		}
	}
	cout<<endl;
	printf("%d\n",ans);
	return 0;
}
/*
题意：
做实验可以得钱，每个实验都需要使用一些仪器，买仪器也要钱，仪器可以共用不同需要它的实验。问最大收益与方案。

思路：
这种东西可以取或不取的题目，可以转化为最小割来求。
这题的状态有点奇妙，可以理解成仪器的状态是反的（因为取仪器不会得到权值，而会失去权值）（类比一下方格取数，每个数的权值对于结果来说都是得到，也就是”加“的关系，不像本题出现”减“的关系）
想通这点就很简单了，sum表示所有实验的收益，连s到实验为实验的权值，连仪器到t为仪器的权值，连相关的实验到仪器为0x3f3f3f3f表示这个实验选，则仪器也必须要选（虽然仪器的边被割了，看上去没选，实际上因为仪器的权值相当于负的，状态是反的，相当于选了）
还有一个问题就是求方案。
这题比较好处理，因为仪器状态是反的，直接看vis即可（因为虽然vis不能代表它的这个边有没有被割，只能代表它所对应的实验的边没有被割，但此题状态反转，选了实验仪器也选了）
*/
