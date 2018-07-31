#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10, maxm = 1e5 * 4;
struct node
{
	int x1, x2, x3, x4;
	char s1[3], s2[3];
	void init() 
	{
		for(int i = 0; i < 3; ++i) if(s1[i] != ' ') { x2 = s1[i] - 'A'; break; }
		for(int i = 0; i < 3; ++i) if(s2[i] != ' ') { x4 = s2[i] - 'A'; break; }
	}
}q[maxm];
int e, to[maxm], nxt[maxm], head[maxn], sccno[maxn], dfn[maxn], low[maxn], hs[maxn][4], p[maxn], sta[maxn], top, scc_cnt, tot;
int FG, n, d, m;
vector<int> vec;
void add(int x, int y)
{
	if(x == 0) return ;
	to[++e] = y; nxt[e] = head[x]; head[x] = e;
	to[++e] = x ^ 1; nxt[e] = head[y ^ 1]; head[y ^ 1] = e;
}
void tarjan(int u)
{
	dfn[u] = low[u] = ++tot; sta[++top] = u;
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if(!sccno[v]) low[u] = min(low[u], dfn[v]);
	}
	if(dfn[u] == low[u])
	{
		scc_cnt++;
		while(1)
		{
			int tmp = sta[top--];
			sccno[tmp] = scc_cnt;
			if(tmp == u) break;
		}
	}
}
void dfs(int x)
{
	if(FG) return ;
	if(x == d)
	{
		memset(head, 0, sizeof(head));
		e = 0; scc_cnt = 0; tot = 0; top = 0;
		memset(sccno, 0, sizeof(sccno));
		memset(dfn, 0, sizeof(dfn));
		for(int i = 1; i <= m; ++i)
			add(hs[q[i].x1][q[i].x2], hs[q[i].x3][q[i].x4] == 0 ? hs[q[i].x1][q[i].x2] ^ 1: hs[q[i].x3][q[i].x4]);
		for(int i = 1; i <= n; ++i)
		{
			if(!dfn[i << 1]) tarjan(i << 1);
			if(!dfn[i << 1 | 1]) tarjan(i << 1 | 1);
		}
		for(int i = 1; i <= n; ++i)
			if(sccno[i << 1] == sccno[i << 1 | 1]) return ;
		FG = 1;
		for(int i = 1; i <= n; ++i)
			if(sccno[i << 1] > sccno[i << 1 | 1]) printf("%c", p[i << 1 | 1]);
			else printf("%c", p[i << 1]);
		return ;
	}
	for(int j = 0; j <= 1; ++j)
	{
		int i = vec[x];
		if(j == 0) { hs[i][1] = i << 1; p[i << 1] = 'B'; hs[i][2] = i << 1 | 1; p[i << 1 | 1] = 'C'; }
		if(j == 1) { hs[i][0] = i << 1; p[i << 1] = 'A'; hs[i][2] = i << 1 | 1; p[i << 1 | 1] = 'C'; }
		dfs(x + 1);
		if(FG) return ;
		hs[i][0] = 0; p[i << 1] = 0; hs[i][2] = 0; p[i << 1 | 1] = 0; hs[i][1] = 0;
	}
}
char s[50100];
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d", &n, &d);
	scanf("%s", s + 1);
	for(int i = 1; i <= n; ++i)
	{
		if(s[i] == 'x') vec.push_back(i);
		else {
			if(s[i] == 'a') { hs[i][1] = i << 1; p[i << 1] = 'B'; hs[i][2] = i << 1 | 1; p[i << 1 | 1] = 'C'; }
			if(s[i] == 'b') { hs[i][0] = i << 1; p[i << 1] = 'A'; hs[i][2] = i << 1 | 1; p[i << 1 | 1] = 'C'; }
			if(s[i] == 'c') { hs[i][0] = i << 1; p[i << 1] = 'A'; hs[i][1] = i << 1 | 1; p[i << 1 | 1] = 'B'; }
		}
	}
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i) { scanf("%d", &q[i].x1); scanf("%s", q[i].s1); scanf("%d", &q[i].x3); scanf("%s", q[i].s2); q[i].init(); }
	dfs(0);
	if(!FG)  puts("-1");
	return 0;
}
/*
题意：
有三种数,每个位置只能填一种数(赛车),有 d∈[0,8] 个位置有三种选择,其他位置只有两种选择
给你一些限制,表示第 i 个位置选了某种数,那么第 j 个位置就只能选规定的数
输出一组合法的选数方案,无解输出 −1 

思路：
考虑没有特殊位置d，本题就是个2-sat板子
然后对于那些二元关系 (i,hi,j,hj)，就如下考虑。
    i可以选择 hi 这种赛车
    j无法选择 hj 这种赛车，那么 i 就必不能选 hi 了，就连一条 hi→¬hi 的边（此处 ¬hi 表示 i可以选择的另一种赛车）
	j可以选择 hj 这种赛车，那么就只要连 hi→hj的边就好了
	i不可以选择 hi 这种赛车：那就直接跳过就行了。
对于特殊位置，我们反着来考虑，dfs出每个位置不能选的位置，就又转化成了2-sat问题
O(3 ^ d * (n + m))
其实没必要对每个d枚举全部3个数，因为 (A,B) 和 (B,C) 的两种选择你都已经考虑过了，那么剩下一种 (A,C) 你前面一定会在前面一种选过。
O(2 ^ d * (n + m))

考虑怎么输出方案
根据背结论，如果对于一个点i，它为真的sccno < 它为假的sccno，就选真
因为这样可以尽可能地避免一个点的一个状态推出这点另一个状态(口胡)

debug:
注意一定要有逆否命题等价的一条边，21行
*/

