#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e6 + 10, mod = 998244353;
LL bit[maxn];
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	int n;
	scanf("%d", &n);
	bit[0] = 1;
	for(int i = 1; i <= n + 1; ++i) bit[i] = bit[i - 1] * 2 % mod;
	LL ans = 0; 
	for(int i = 1; i <= n; ++i)
	{
		int x;
		scanf("%d", &x);
		LL time = 1LL * x * (bit[n - i] + (n - i) * (bit[n - i - 1]) % mod) % mod;
		ans = (ans + time) % mod;
	}
	cout << ans << endl;
	return 0;
}
/*
题意：数轴上从0出发到n，值为1 - （n-1）的点中均可以休息，也可以不休息。现在给定一个数组a[ ]，a[i]表示走长度为i的距离的困难度（保证a[i+1]>a[i]），设每种情况出现的可能性均相同，求所有可能性的期望困难度之和p*2^(n-1)。

思路：
由期望的线性性质，对每个a[i]求出现次数
所有情况从0 -> 1都需要a[1]  =>  需要 2^(n-1) 次
若1 -> 2需要a[1]，则1必须休息，其余各点均无所谓  =>  需要2^(n-2)
若2 -> 3需要a[1]，则2必须休息，其余各点均无所谓  =>  需要2^(n-2)
若3 -> 4需要a[1]，则3必须休息，其余各点均无所谓  =>  需要2^(n-2)
......
若(n-1) -> n需要a[1]，则n-1必须休息，其余各点均无所谓  =>  需要2^(n-2)
=> time[1]=2^(n-1)+(n-1)*2^(n-2)
 
tips: 这么算会不会有重复情况？可以看到算1-2时考虑过全为休息的情况，算2-3时又考虑了全为休息的情况。但实际这不是重复的，因为全为休息的情况本来就会在1-2、 2-3、 ...  (n-1)-n 时都产生一个a[1]的困难度。其他情况同理。


time[2]：
若0 -> 2需要a[2]，则1必须不休息，其余各点均无所谓 => 需要2^(n-2)
若1 -> 3需要a[2]，则1必须休息，2必须不休息，其余各点均无所谓 => 需要2^(n-3)
若2 -> 4需要a[2]，则2必须休息，3必须不休息，其余各点均无所谓 => 需要2^(n-3)
若3 -> 5需要a[2]，则3必须休息，4必须不休息，其余各点均无所谓 => 需要2^(n-3)
......
若(n-2) -> n需要a[2]，则n-2必须休息，n-1必须不休息，其余各点均无所谓 => 需要2^(n-3)
=> time[2]=2^(n-2)+(n-2)*2^(n-3)

=> time[i] = 2^(n-i) + (n-i)*2^(n-i-1)   (其中1<=i<=n)

*/
