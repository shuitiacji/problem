#include<bits/stdc++.h>
using namespace std;
#define next Next
typedef long long LL;
const int maxn=4010,maxm=maxn*10;
int s,t;
struct COST_FLOW{
	int e;LL COST;
	int to[maxm],next[maxm],head[maxn],from[maxm],cap[maxm],cost[maxm],inq[maxn],p[maxn],a[maxn],flow[maxm];/**/
	int d[maxn];
	void add(int x,int y,int z,int Z){
		to[++e]=y;
		next[e]=head[x];
		head[x]=e;
		cap[e]=z;
		cost[e]=Z;
		from[e]=x;
	}
	int spfa(){
		for(int i=s;i<=t;++i)inq[i]=0,d[i]=0x3f3f3f3f;
		a[s]=0x3f3f3f3f;inq[s]=1;p[s]=0;
/**/	d[s]=0;
		queue<int> q;
		q.push(s);
		while(!q.empty()){
			int u=q.front();q.pop();inq[u]=0;
			for(int i=head[u];i!=-1;i=next[i]){
				int v=to[i];
				if(flow[i]<cap[i]&&d[v]>d[u]+cost[i]){
					d[v]=d[u]+cost[i];
					p[v]=i;
					a[v]=min(a[u],cap[i]-flow[i]);
					if(!inq[v])inq[v]=1,q.push(v);
				}
			}
		}
		if(d[t]==0x3f3f3f3f)return 0;
		COST+=1LL*a[t]*d[t];
		int u=t;
		while(u!=s){
			flow[p[u]]+=a[t];
			flow[p[u]^1]-=a[t];
			u=from[p[u]];
		}
		return 1;
	}
	void gao(){
		while(spfa());
		printf("%lld\n",COST);
	}
}T;
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n;
	scanf("%d",&n);
	s=0;t=2*n+1;T.e=-1;
	memset(T.head,-1,sizeof(T.head));
	for(int i=1;i<=n;++i){
		int x;
		scanf("%d",&x);
		T.add(i,t,x,0);T.add(t,i,0,0);
		T.add(s,i+n,x,0);T.add(i+n,s,0,0);
		if(i!=n)T.add(i+n,i+n+1,0x3f3f3f3f,0),T.add(i+n+1,i+n,0,0);
	}
/**/int p,m,f,N,S;
	scanf("%d%d%d%d%d",&p,&m,&f,&N,&S);
	for(int i=1;i<=n;++i){
		T.add(s,i,0x3f3f3f3f,p);T.add(i,s,0,-p);
		if(i+m<=n)T.add(i+n,i+m,0x3f3f3f3f,f),T.add(i+m,i+n,0,-f);
		if(i+N<=n)T.add(i+n,i+N,0x3f3f3f3f,S),T.add(i+N,i+n,0,-S);
	}
	T.gao();
	return 0;
}
/*
题意:
一个餐厅在相继的 N 天里,每天需用的餐巾数不尽相同。假设第 i 天需要 ri块餐巾( i=1,2,...,N)。餐厅可以购买新的餐巾,每块餐巾的费用为 p 分;或者把旧餐巾送到快洗部,洗一块需 m 天,其费用为 f 分;或者送到慢洗部,洗一块需 n 天( n>m ),其费用为 s 分( s<f )。

每天结束时,餐厅必须决定将多少块脏的餐巾送到快洗部,多少块餐巾送到慢洗部,以及多少块保存起来延期送洗。但是每天洗好的餐巾和购买的新餐巾数之和,要满足当天的需求量。

试设计一个算法为餐厅合理地安排好 N 天中餐巾使用计划,使总的花费最小。编程找出一个最佳餐巾使用计划。

思路：
先确定模型，因为是要求在满足每天需求量下的最小花费，容易想到最小费用最大流，也是在满足最大流基础上的最小费用流。
为满足满流情况满足题意，自然的想到每一天当一个点，向t连容量为ri的弧，这样求最大流就是在满足题意了。
但这样做的缺陷是难以表示每个点洗毛巾得到的，如果从另一个点连过来，因为用掉的毛巾已是流走到t去了，不能从它那凭空得到流量；若从s连过来，可以凭空得到流量，但因为有两种方式洗毛巾，所以如果直接从s引两条，这两条之间没有约束，可能两条总流量会大于那天要洗的毛巾量。
在建模中出现矛盾，可能是状态不足，考虑分点。

首先，我们拆点，将一天拆成晚上和早上，每天晚上会受到脏餐巾（来源：当天早上用完的餐巾，在这道题中可理解为从原点获得），每天早上又有干净的餐巾（来源：购买、快洗店、慢洗店）。

1.从原点向每一天晚上连一条流量为当天所用餐巾x，费用为0的边，表示每天晚上从起点获得x条脏餐巾。

2.从每一天早上向汇点连一条流量为当天所用餐巾x，费用为0的边，每天白天,表示向汇点提供x条干净的餐巾,流满时表示第i天的餐巾够用 。 3.从每一天晚上向第二天晚上连一条流量为INF，费用为0的边，表示每天晚上可以将脏餐巾留到第二天晚上（注意不是早上，因为脏餐巾在早上不可以使用）。

4.从每一天晚上向这一天+快洗所用天数t1的那一天早上连一条流量为INF，费用为快洗所用钱数的边，表示每天晚上可以送去快洗部,在地i+t1天早上收到餐巾 。

5.同理，从每一天晚上向这一天+慢洗所用天数t2的那一天早上连一条流量为INF，费用为慢洗所用钱数的边，表示每天晚上可以送去慢洗部,在地i+t2天早上收到餐巾 。

6.从起点向每一天早上连一条流量为INF，费用为购买餐巾所用钱数的边，表示每天早上可以购买餐巾 。 注意，以上6点需要建反向边！3~6点需要做判断（即连向的边必须<=n）

debug:
1.9行，flow的maxm写成maxn
2.22行忘写
3.66行s定义重名
*/
