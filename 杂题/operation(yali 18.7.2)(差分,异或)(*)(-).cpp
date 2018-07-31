#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long LL;
LL x;
LL Random() {
	x ^= (x << 5); x ^= (x >> 12); x ^= (x << 6);
	return x;
}
const int maxn = 2000100;
char S[maxn];
LL z[maxn], Z[maxn];
int s[maxn], b[maxn], c[maxn], d[maxn], sum[maxn];
int main()
{
	freopen ("operation.in", "r", stdin);
	freopen ("operation.out", "w", stdout);
//	srand(time(NULL));
	int n, k, q;
	scanf ("%d %d %d", &n, &k, &q);
	scanf ("%s", S+1);
	for(int i = 1; i <= n; ++i) S[i] -= '0';
	for(int i = 1; i <= n; ++i) 
		s[i] = S[i] ^ S[i - 1];
	x = 1;
	for(int i = 0; i < k; ++i)
		z[i] = Random();
	for(int i = 1; i <= n; ++i) {
		sum[i] = sum[i - 1]; Z[i] = Z[i - 1];
		if(s[i])
			Z[i] ^= z[i % k], sum[i] -= b[i % k], sum[i] += b[i % k] = i / k - b[i % k];
		c[i] = b[(i + 1) % k]; d[i] = b[i % k];
	}
	while(q--) {
		int l, r;
		scanf("%d %d", &l, &r);
		if(Z[r] ^ Z[l] ^ (S[r] * z[(r + 1) % k]) ^ (S[l] * z[l % k])) {puts("-1"); continue ;}
		LL ans = sum[r] - sum[l];
		if(S[r]) ans += (r + 1) / k - 2 * c[r];
		if(S[l]) ans += 2 * d[l] - l / k;
		printf("%lld\n", ans);
	}
}
/*
题意：
有一个长度为n的01序列，m次询问，每次询问给出一个区间，你可以进行若干次操作，每次选择这个区间的一个长度为k的子区间，并将这个子区间内所有01取反，求至少需要几次操作才能将这个区间内的所有元素变为0。
每次询问都是独立的，你在一个询问中进行的操作不会影响到另一个询问。

思路：
区间取反，想到差分，即解决将一段区间内的差分1通过每次移动k，与其它1相消的最小步数。
因为只能移动k，只要看这段区间模k意义下数字相同的个数是否为偶数，就知道是否有解，有解再贪心取离自己最近的模k相等的数。
可以莫队，但是有更优秀的做法。
可以先记一个前缀和，表示移动步数，如果暴力去减出一段区间的答案，若这段区间本身都是偶数就没有关系，有奇数输-1即可
问题转化成快速判断一个区间内是否存在奇数个模k意义下相同的数。
考虑只要求奇偶，什么东西偶数次操作为0,奇数次操作非0 —— 异或
我们可以对异或也记一个前缀和，这样可以快速得到一段区间内所有数模k后的异或和。
但这样会有问题，比如说 1010 可以被1000与10搞掉，而不是他自己。
因为k较小，单纯用模k后的值搞，范围小，容易像上面这样搞掉。
可以对每种数随机出一个较大的值来防止这种冲突
最后特殊考虑区间左端点右端点的情况。

*/
