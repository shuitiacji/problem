#include<bits/stdc++.h>
using namespace std;
const int maxn = 100;
#define eps 1e-10
int n, m;
double a[maxn][maxn], ans[maxn];
int id[maxn << 1];
void pivot(int x, int y)
{
	swap(id[n + x], id[y]);
	double t = a[x][y]; a[x][y] = 1;
	for(int i = 0; i <= n; ++i) a[x][i] /= t;
	for(int i = 0; i <= m; ++i)
		if(i != x && abs(a[i][y]) > eps)
		{
			t = a[i][y]; a[i][y] = 0;
			for(int j = 0; j <= n; ++j) a[i][j] -= t * a[x][j];
		}
}
int init()
{
	while(1)
	{
		int x = 0, y = 0;
		for(int i = 1; i <= m; ++i)
			if(a[i][0] < -eps && (!x || (rand() & 1))) x = i;
		if(!x) break;
		for(int i = 1; i <= n; ++i)
			if(a[x][i] < -eps && (!y || (rand() & 1))) y = i;
		if(!y) { puts("Infeasible"); return 0; }
		pivot(x, y);
	}
	return 1;
}
int simplex()
{
	while(1)
	{
		int x = 0, y = 0; double mn = 1e15;
		for(int i = 1; i <= n; ++i)
			if(a[0][i] > eps) { x = i; break; }
		if(!x) break;
		for(int i = 1; i <= m; ++i)
			if(a[i][x] > eps && a[i][0] / a[i][x] < mn)
				mn = a[i][0] / a[i][x], y = i;
		if(!y) { puts("Unbounded"); return 0; }
		pivot(y, x);
	}
	return 1;
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	srand(19660813);
	for(int i = 1; i <= 5; ++i) srand(rand());
	int t;
	scanf("%d%d%d", &n, &m, &t);
	for(int i = 1; i <= n; ++i) scanf("%lf", &a[0][i]);
	for(int i = 1; i <= m; ++i)
	{
		for(int j = 1; j <= n; ++j)
			scanf("%lf", &a[i][j]);
		scanf("%lf", &a[i][0]);
	}
	for(int i = 1; i <= n; ++i) id[i] = i;
	if(init() && simplex())
	{
		printf("%.8lf\n", -a[0][0]);
		if(t)
		{
			for(int i = 1; i <= m; ++i) ans[id[n + i]] = a[i][0];
			for(int i = 1; i <= n; ++i) printf("%.8lf ", ans[i]);
		}
	}
	return 0;
}
/*
debug:
18.8.3
1.eps搞小一些
*/
