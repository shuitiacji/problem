#include<bits/stdc++.h>
using namespace std;
const int Mod = 998244353;
typedef long long LL;
namespace Get_Inv {
	LL fpm(LL x, int power) {
		LL res = 1;
		for (; power; power >>= 1, x = 1ll * x * x % Mod)
			if (power & 1) res = 1ll * res * x % Mod;
		return res;
	}
	LL Inv(LL x) { return fpm(x, Mod - 2); }
}
int main()
{
	freopen("paint.in", "r", stdin);
	freopen("paint.out", "w", stdout);
	LL n;int k;
	scanf("%lld%d", &n, &k);
	LL tmp = n * n;
/**/tmp %= Mod;
	tmp = Get_Inv::Inv(tmp);
	tmp = Get_Inv::fpm(tmp, k);
	LL Ans = 0;
	for(int i = 1; i <= n; ++i)
	{
		LL TMP = 1LL * (i - 1) * (i - 1) + 1LL * (n - i) * (n - i);
		TMP %= Mod;
		TMP = Get_Inv::fpm(TMP, k);
		(Ans += 1 - TMP * tmp) %= Mod;
	}
/**/(Ans += Mod) %= Mod;
	cout << Ans << endl;
	return 0;
}
/*
题意：
小猪佩奇很喜欢画画,尤其喜欢天马星空地乱画。有一天,它又用它的
小手拿起了它的小笔开始在画板上瞎涂啦。
这个画板是一个长为 n 的初始全为白色的序列(即有 n 个白色的点)。
佩奇会将其涂色,一共会涂 k 次,每次过程如下:
1. 在 [1, n] 随机等概率选择一个点 a;
2. 在 [1, n] 随机等概率选择一个点 b(可以与前面的那个重复);
3. 令 l = min(a, b), r = max(a, b) 将 [l, r] 的这一段序列涂黑。
佩奇对艺术颇有建树,它对画作的评价就是最后有多少个点被涂黑了。
现在你需要告诉佩奇它对于它画作的期望评价,也就是求最后序列中
被染黑点的期望个数。

思路：
对于这种贡献只是简单加法（只要看最后黑点的总和）的题，利用期望的线性性质，考虑一个点被涂的期望。
从反面考虑，一个点没被涂的期望。
对于点x，每一次涂的时候，当l,r都在1~(x-1)或(x+1)~n时，x没被涂
那么它的期望贡献就是：
1-(((x-1)^2 + (n-x) ^2) / (n*n))^k

debug:
1.21没mod
2.32行%=没等号
*/

