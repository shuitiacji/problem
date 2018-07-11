#include<bits/stdc++.h>
using namespace std;
const int maxn = 4e5 + 10;
int a[maxn];
namespace BIT
{
	int c[maxn];
	int lowbit(int x) { return x & (-x); }
	void upt(int x)
	{
		while(x <= maxn)
		{
			c[x]++; x += lowbit(x);
		}
	}	
	int que(int x)
	{
		int ret = 0;
		while(x) 
		{
			ret += c[x]; x -= lowbit(x);
		}
		return ret;
	}
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	int t = n + 1;
	long long ans = 0;
	BIT::upt(n+1);
	for(int i = 1; i <= n; ++i)
	{
		t += a[i] <= m ? 1 : -1;
		BIT::upt(t);
		ans += BIT::que(t);
	}
	memset(BIT::c, 0, sizeof(BIT::c));
	t = n + 1;
	BIT::upt(n+1);
	for(int i = 1; i <= n; ++i)
	{
		t += a[i] < m ? 1 : -1;
		BIT::upt(t);
		ans -= BIT::que(t);	
	}
	cout << ans << endl;
	return 0;
}
/*
题意：
给你一个序列，和一个数m，询问这个序列中存在多少个子区间满足这个区间的中位数等于m（个数为偶的区间，中位数为中间那个靠左的

思路：
这种区间与排序有关的，可以一个东西作为关键字，把小于它的数置成一个东西，大于它的数置成一个东西。
询问有多少个子区间，可以先确定一个端点，利用题目性质再用一些数据结构的东西快速处理出满足的左端点有多少个。
考虑这题，如果对于第1个部分分，序列为排列的情况，可以考虑把小于m的置成1,大于m的置成-1,等于m的置成0，看区间的值是否为1或-1（先扫一遍分别把扫到的点当作右端点，可以开一个桶记前缀和，在桶中找到那个能使当前区间值符合的前缀和，即为左端点）,再特殊判一下。发现这样搞对等于m特别多的情况特别不好处理。
上述做法中，我们找的是中位数恰好为m的，在判断m的值到底是1还是-1上特别不好搞（因为m过多时会占去一部分为-1的值，过少时会占去一部分为1的值），如果能有办法使得能m为1搞一次，m为-1再搞一次就好了。
其实我们会发现ans = 中位数<=m的方案数 - 中位数<m的方案数，如果将两个分别算一下，刚好可以将m为1搞一次，m为-1搞一次。
只要像之前一样，不过把桶换成BIT，查之前有没有前缀和能小于现在的前缀和，因为只要区间的和大于0即可。
*/

