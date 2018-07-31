#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 50;
int vis1[4][maxn], vis2[4][maxn];
vector<int> e1[4][maxn], e2[4][maxn];
int n, m, k;
void dfs1(int u, int k1)
{
	vis1[k1][u] = 1;
	for(int i = 0; i < e1[k1][u].size(); ++i)
	{
		int v = e1[k1][u][i];
		if(vis1[k1][v]) continue;
		dfs1(v, k1);
	}
}
void dfs2(int u, int k1)
{
	vis2[k1][u] = 1;
	for(int i = 0; i < e2[k1][u].size(); ++i)
	{
		int v = e2[k1][u][i];
		if(vis2[k1][v]) continue;
		dfs2(v, k1);
	}
}
int main()
{
	freopen("ask.in", "r", stdin);
	freopen("ask.out", "w", stdout);
	scanf("%d%d%d", &n, &k, &m);
	for(int i = 1; i <= m; ++i)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		e1[z][x].push_back(y); e2[z][y].push_back(x);
	}
	for(int i = 1; i <= k; ++i)
		dfs1(1, i), dfs2(1, i);
	int cnt1 = 0, cnt2 = 0;
	for(int i = 2; i <= n; ++i)
	{
		int fg1 = 1, fg2 = 1;
		for(int j = 1; j <= k; ++j)
		{
			if(!vis1[j][i]) fg1 = 0;
			if(!vis2[j][i]) fg2 = 0;
		}
		cnt1 += fg1; cnt2 += fg2;
	}
	cout << n - cnt1 << ' ' << cnt2 + 1 << endl;
	return 0;
}
/*
题意:
众所周知，gkk是一个热衷于询问成绩的好孩子。这天刚刚考试完，他就偷听到了m条成绩关系。他听到的成绩关系中ai,bi,ci分别表示第ai个人的第ci门课成绩高于第bi个人。一直班上一共有n个人，考试科目为k门。已知gkk的编号为1，则根据他听到的这m条成绩，他的最坏排名与最好排名分别是多少。注意一个人的排名严格高于另一个人当且仅当他的每一门都比另一个人高。

思路:
首先我们可以考虑一下排名最高和最低分别是什么情况。
排名最高时，肯定是只有所有科目排名均比他高的在他的前面；排名最低时，肯定是只有一定比自己排名低的排在自己后面。
对于k = 1的情况，我们可以建两个图，一个图每条边u,v,表示u比v高，另一个图表示u比v低。
那么从1号点开始dfs时，在第一个图中能走到的点都比1低，第二个图中走到的都比1高。
对于k > 1的情况，每一门分别建图得到比1高的和比1低的,求出在所有情况都比1高的,和都比1低的即可
*/
