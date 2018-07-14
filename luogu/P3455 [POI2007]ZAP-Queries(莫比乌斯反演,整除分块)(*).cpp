#include<bits/stdc++.h>
using namespace std;
const int maxn = 50100;
typedef long long LL;
int mu[maxn], vis[maxn], prime[maxn], sum[maxn];
int cnt;
void mathinit()
{
	mu[1] = 1;
	for(int i = 2; i <= maxn - 10; ++i)
	{
		if(!vis[i]) mu[i] = -1, prime[++cnt] = i;
		for(int j = 1; j <= cnt && prime[j] * i <= maxn - 10; ++j)
		{
			vis[prime[j] * i] = 1;
			if(i % prime[j]) mu[i * prime[j]] = -mu[i], vis[i * prime[j]] = 1;
			else 
			{
				mu[i * prime[j]] = 0;
				break;
			}
		}
	}
	for(int i = 1; i <= maxn - 10; ++i)
		sum[i] += sum[i - 1] + mu[i];
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	mathinit();
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		int a, b, d;
		scanf("%d%d%d", &a, &b, &d);
		int Min = min(a, b);
		LL ans = 0;
/**/	for(int l = 1, r; l <= Min; )
		{
			r = min(a / (a / l), b / (b / l));
///			r = Min / (Min / l);
			ans += 1LL * (sum[r] - sum[l - 1]) * (a / (l * d)) * (b / (l * d));
			l = r + 1;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
/*
题意：
FGD正在破解一段密码，他需要回答很多类似的问题：对于给定的整数a,b和d，有多少正整数对x,y，满足x<=a，y<=b，并且gcd(x,y)=d。作为FGD的同学，FGD希望得到你的帮助。

思路:
可以先把d化掉，即求gcd(i, j) == 1 (i <= a/d, j <= b/d)  
设f(n) 为 gcd == n的对数，则设F(n) 为 gcd == k * n 的对数
F(n) = sigma(f(i)) (n | i)
f(n) = sigma(mu[i / n] * F[i]) (n | i)

ans = f(1)
F(n) = (a / d) / n * (b / d) / n
f(1) = sigma(mu[i] * (a / d) / i * (b / d) / i) (i <= min(a /d, b / d))
可以O(n)求，但也有更优的做法。
对于每一个⌊n/i⌋我们可以通过打表(或理性的证明)可以发现：有许多⌊n/i⌋的值是一样的，而且它们呈一个块状分布；再通过打表之类的各种方法,我们惊喜的发现对于每一个值相同的块，它的最后一个数就是n/(n/i)。得出这个结论后，我们就可以做的O(√n)处理了。

debug:
1.40行，不要误打++j
2.42行不要写成43行的形式，因为43行不一定是最小的，这样有可能越过r<=Min的限制
*/
