#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e6 + 10;
int vis[maxn], mu[maxn], prime[maxn];
void mathinit()
{
	mu[1] = 1; 
	int cnt = 0;
	for(int i = 2; i <= maxn - 5; ++i)
	{
		if(!vis[i])
			mu[i] = -1, prime[++cnt] = i;
		for(int j = 1; j <= cnt && 1LL * i * prime[j] <= maxn - 5; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] > 0)
				mu[i * prime[j]] = -mu[i];
			else 
			{
				mu[i * prime[j]] = 0;
				break;
			}
		}
	}
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	mathinit();
	int T;
	scanf("%d", &T);
	for(int t = 1; t <= T; ++t)
	{
		int a, b, c, d, k;
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		if(k == 0)
		{
			printf("Case %d: 0\n", t);
			continue;
		}
		b /= k; d /= k;
		int mn = min(b, d);
		LL ans1 = 0, ans2 = 0;
		for(int i = 1; i <= mn; ++i)
		{
			ans1 += 1LL * mu[i] * (b / i) * (d / i);
			ans2 += 1LL * mu[i] * (mn / i) * (mn / i);
		}
		printf("Case %d: %lld\n", t, ans1 - ans2 / 2);
	}
	return 0;
}

