#include<bits/stdc++.h>
using namespace std;
#define pb push_back 
#define next Next
const int maxn=100100;
int q[maxn],n;
int top=0,e,tot,Q;
vector<int> QUE[maxn];
int ans[maxn];
int tmp[maxn];
int to[maxn],head[maxn],next[maxn];
char A[maxn];
void ins(int u,int v){
	to[++e]=v;
	next[e]=head[u];
	head[u]=e;
}
void dfs(int u){
	if(A[u])tmp[++top]=A[u]-'a';
	for(int i=0;i<QUE[u].size();++i){
		ans[QUE[u][i]]=tmp[ans[QUE[u][i]]];
	}
	for(int i=head[u];i;i=next[i]){
		int v=to[i];
		dfs(v);
		if(v==u+1)top--;
	}
}
int main(){
	freopen("type.in","r",stdin);
	freopen("type.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		char a[10],x[10];
		scanf("%s",a);
		if(a[0]=='T'){
			scanf("%s",x);
			A[++tot]=x[0];
			ins(tot-1,tot);
		}
		if(a[0]=='Q'){
			int t;
			scanf("%d",&t);
			QUE[tot].pb(++Q);
			ans[Q]=t;
		}
		if(a[0]=='U'){
			int t;
			scanf("%d",&t);
			++tot;
			ins(tot-t-1,tot);
		}
	}
	dfs(0);
	for(int i=1;i<=Q;++i)printf("%c\n",ans[i]+'a');
	return 0;
}
/*
题意:早苗入手了最新的高级打字机。最新款自然有着与以往不同的功能,那就是
它具备撤销功能,厉害吧。
请为这种高级打字机设计一个程序,支持如下 3 种操作:
1.T x:在文章末尾打下一个小写字母 x。(type 操作)
2.U x:撤销最后的 x 次修改操作。(Undo 操作)
(注意 Query 操作并不算修改操作)
3.Q x:询问当前文章中第 x 个字母并输出。(Query 操作)
文章一开始可以视为空串。

思路：首先这题可以算是可持久化的裸题，但对于不要求在线，我们考虑把它的每次修改操作版本建出来，对于T，把版本i与i+1连一条线，U把i与i-x-1连线，就可以愉快地在这个版本树上离线跑dfs(需要回溯，操作必须可逆） O(n)解决。
能解决这类题目的条件是:
1.允许使用离线算法,进而求出版本树,并允许把询问挂到树的节点上。
2.所有操作都是可逆的。只有所有操作都是可逆的,才能按欧拉序依次求
出各版本。如本题的 Type 操作的逆操作就是弹出栈顶,Undo 操作则根本不需
要修改(Undo 前后 2 个版本相同)。
*/
