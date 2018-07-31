#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e6 + 10;
int n, m, k;
int No[maxn], a[maxn], anc[maxn][25];
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	int tmp = 1; LL sum = a[1];
	for(int i = 1; i <= n; ++i)
	{
		No[i] = No[i - 1];
		while(tmp<=n && sum <= k)
		{
			++tmp;
			sum += a[tmp];
		}
		sum -= a[i];
		anc[i][0] = tmp;
		if(tmp == i) No[i]++;
	}
	anc[n + 1][0] = n + 1;
	for(int i = n; i >= 1; --i)
		for(int j = 1; j <= 22; ++j)
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
	for(int i = 1; i <= m; ++i)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		if(No[r] - No[l - 1]) puts("Chtholly");
		else 
		{
			int ans = 0;
			int pos = l;
			for(int j = 22; j >= 0; --j)
			{
				if(anc[pos][j] && anc[pos][j] - 1 < r) pos = anc[pos][j], ans += (1 << j);
			}
			ans++;
			printf("%d\n", ans);
		}
	}
	return 0;
}
/*
题意：
给你一个长为n的序列a和一个常数k
有m次询问，每次查询一个区间[l,r]内所有数最少分成多少个连续段，使得每段的和都 <= k
如果这一次查询无解，输出"Chtholly"

思路：
先考虑贪心，显然可以每次跳到最远的点，这样搞是对的。
先预处理出每个的nxt，显然可以维护两个指针，线性扫一遍处理出以每个为开头的块可以跳到的下一个块。
可以倍增一下，每个询问log级回答。
这种区间上的区间覆盖+分块问题，会被询问的l，r影响，都可以贪心找跳一次最远，预处理出倍增数组，log级回答询问
*/
