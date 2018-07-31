#include<bits/stdc++.h>
using namespace std;
const int maxn = 110;
int n;
double a[maxn][maxn];
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n + 1; ++j)
			scanf("%lf", &a[i][j]);
	for(int i = 1; i <= n; ++i)
	{
		int r = i;
		for(int j = i; j <= n; ++j)
			if(fabs(a[j][i]) > fabs(a[r][i])) r = j;
		if(r != i) for(int j = 1; j <= n + 1; ++j) swap(a[i][j], a[r][j]);
		if(a[i][i] == 0.) { puts("No Solution"); return 0; }
		for(int j = i + 1; j <= n; ++j)
		{
			double f = a[j][i] / a[i][i];
			for(int k = i; k <= n + 1; ++k)
				a[j][k] -= f * a[i][k];
		}
	}
	for(int i = n; i >= 1; --i)
	{
		for(int j = i + 1; j <= n; ++j)
/**/		a[i][n + 1] -= a[j][n + 1] * a[i][j];
		a[i][n + 1] /= a[i][i];
	}
	for(int i = 1; i <= n; ++i) printf("%.2lf\n", a[i][n + 1]);
	return 0;
}
/*
debug:
7.26
31行，a[j][n + 1]写成a[j][j]
*/
