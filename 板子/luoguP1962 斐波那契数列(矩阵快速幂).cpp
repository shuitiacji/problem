#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1e9 + 7;
struct matrix
{
	LL a[5][5]; int N, M;
	matrix(int x, int y) { N = x; M = y; }
	matrix operator * (const matrix &b) const
	{
		matrix tmp = matrix(N, b.M);
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= b.M; ++j)
			{
				tmp.a[i][j] = 0;
				for(int k = 1; k <= M; ++k)
				{
					tmp.a[i][j] += a[i][k] * b.a[k][j];
					tmp.a[i][j] %= mod;
				}
			}
		return tmp;
	}
};
matrix ans = matrix(2, 2);
void Pow(matrix x, LL k)
{
	while(k)
	{
		if(k & 1) ans = ans * x;
		x = x * x; k >>= 1;
	}
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
/**/LL n;
	scanf("%lld", &n);
	ans.a[1][1] = 1; ans.a[1][2] = 1;
	ans.a[2][1] = 1; ans.a[2][2] = 0;
	matrix pre = matrix(2, 1);
	pre.a[1][1] = 1; pre.a[2][1] = 1;
	if(n - 3 < 0) { cout << 1 << endl; return 0; }
	Pow(ans, n - 3);
	ans = ans * pre;
	printf("%lld", ans.a[1][1]);
	return 0;
}
/*
debug:
7.29
1.38行，写成int
*/
