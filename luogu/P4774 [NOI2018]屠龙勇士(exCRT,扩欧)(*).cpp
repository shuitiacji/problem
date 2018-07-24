#include<bits/stdc++.h>
using namespace std;
#define int long long 
multiset<int> S;
typedef long long LL;
const int maxn = 1e5 + 10;
int n, m, p[maxn], atk[maxn], gain[maxn];
int rest[maxn], mod[maxn];
LL a[maxn];
void init()
{
	S.clear();
}
int ans;
void Exgcd (int a, int b, int &d, int &x, int &y)
{
	if (!b) d = a, x = 1, y = 0;
	else { Exgcd(b, a % b, d, y, x); y -= x * (a / b); }
}
int Inv (int a,int n)
{
	int d, x, y;
    Exgcd (a, n, d, x, y);
    return d == 1 ? (x + n) % n : -1;
}

/**/LL mul(LL a, LL b, LL Mod)
{
	LL ret = 0;
/**/a = ((a % Mod) + Mod) % Mod;
/**/b = ((b % Mod) + Mod) % Mod;
	while(b)
	{
		if(b & 1) ret = (ret + a) % Mod;
		a = (a + a) % Mod; b >>= 1;
	}
	return ret;
}
int Solve()
{
	for (int i = 1; i < n; ++i)
	{
        int a = mod[i], b = mod[i + 1], c = rest[i + 1] - rest[i], gcd = __gcd(a, b), k1, k2, g;
        if (c % gcd) return - 1;
        a /= gcd; b /= gcd; c /= gcd;
        Exgcd(a, b, g, k1, k2);
        k1 = (mul(k1, c, b) + b) % b;
        mod[i + 1] = mod[i] / __gcd(mod[i], mod[i + 1]) * mod[i + 1] ;
        rest[i + 1] = (mul(mod[i], k1, mod[i + 1]) + rest[i]) % mod[i + 1];
	}
    return rest[n];
}
LL nogcd(LL a, LL b)
{
	if(a == 0) return b;
	else return nogcd(b, a % b);
}

main()
{
	freopen("dragon.in", "r", stdin);
	freopen("dragon.out", "w", stdout);
	int T;
	scanf("%lld", &T);
	while(T--)
	{
		init();
		scanf("%lld%lld", &n, &m);
		int fg = 0;
		for(int i = 1; i <= n; ++i)
			scanf("%lld", &a[i]);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%lld", &p[i]);
			if(p[i] != 1) fg = 1;
		}
		for(int i = 1; i <= n; ++i)
			scanf("%lld", &gain[i]);
		for(int i = 1; i <= m; ++i)
			scanf("%lld", &atk[i]), S.insert(atk[i]);
		ans = -1;
		for (int i = 1; i <= n; ++i)
		{
/**/		multiset <int> :: iterator it = S.upper_bound(a[i]);
			if (it != S.begin())
				it--;
			rest[i] = *it;
			ans = max(ans, (int)ceil((double)(1.0 * a[i] / rest[i])));
/**/		S.erase(it);
			S.insert(gain[i]);
		}
		if(!fg) cout << ans << endl;
		else 
		{
			int FG = 0;
			for(int i = 1; i <= n; ++i)
			{
				mod[i] = p[i];
				int x = Inv(rest[i], mod[i]);
				if(x == -1)
				{
					int tmp = __gcd(rest[i], mod[i]);
					if(__gcd(tmp, a[i]) != tmp) FG = 1;
					else {
						a[i] /= tmp; rest[i] /= tmp; mod[i] /= tmp;
						x = Inv(rest[i], mod[i]);
					}
				}
				rest[i] = mul(a[i] % mod[i], x % mod[i], mod[i]);
			}
			if(FG) puts("-1");
			else cout << Solve() << endl;
		}
	}
	return 0;
}

/*
思路：
给了一个神奇的条件lcm(pi) <= 10 ^ 12,引导我们往扩展中国剩余定理上想
考虑这个东西可以写成一个方程的形式：
ai + atk * x = pi * y
ai = atk * x (mod pi)
为了变成CRT的形式，把atk的逆元除过去
ai * atk ^ (-1) = x
但要注意，因为这里的pi不是质数，所以有可能没有逆元，但方程仍是有解的：
2 = 4 * x (mod 2)
显然4在mod 2意义下没有逆元，但该方程显然有解
在这种情况下，我们要判一下，是否gcd(atk,pi) 也为ai的因数，这样就可以除掉这个gcd，使得逆元存在，若不满足，则无解

还有一个任务，就是得到方程的系数，由于条件很特殊，用set维护一下即可。

最后是合并方程
对于：
x = y1 (mod p1) -> x = y1 + p1 * k1
x = y2 (mod p2) -> x = y2 + p2 * k2
p1 * k1 - p2 * k2 = y2 - y1
用扩欧求出一个最小整数解k1，带入可以解出一个x0的特解
因为x要最小，k1与其相邻解的间距为p2 / gcd(p1, p2), 又x = p1 * k1 + y1, 所以x与其相邻解的距离为p1 * p2 / gcd(p1, p2) == lcm(p1, p2)
所以x = x0 (mod lcm(p1, p2))
于是将两个方程合并为一个，一直做下去就可以解出来了

debug:
1.27行,要写快速乘
2.30,31必须要mod，不然会有负数，会死循环
3.84行，必须要用set自带的upper_bound，不然是O(n)的
4.89，multiset必须要erase迭代器，不能删键值
*/


