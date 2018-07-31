#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;
int a[maxn], L[maxn], R[maxn], b[maxn];
pair<int, int> sta[maxn];
vector<pair<int, int> > vec[maxn];
int n, N;
/**/int find(int x)
{
	if(x >= b[N]) return N;
	return upper_bound(b + 1, b + N + 1, x) - b - 1;
}
namespace BIT
{
	LL c[maxn];
	int lowbit(int x) { return x & (-x); }
	void upt(int x)
	{
		while(x <= N)
			c[x]++, x += lowbit(x);
	}
	LL que(int x)
	{
		LL ret = 0;
		while(x)
			ret += c[x], x -= lowbit(x);
		return ret;
	}
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]), b[i] = a[i];
	int top = 0;
	for(int i = 1; i <= n; ++i)
	{
		while(top && sta[top].second < a[i]) top--;
		L[i] = top ? sta[top].first + 1 : 1;
		sta[++top] = make_pair(i, a[i]);
	}
	top = 0;
	for(int i = n; i >= 1; --i)
	{
		while(top && sta[top].second <= a[i]) top--;
		R[i] = top ? sta[top].first - 1 : n;
		sta[++top] = make_pair(i, a[i]);
	}
	for(int i = 1; i <= n; ++i)
	{
		if(i - L[i] <= R[i] - i)
		{
			for(int j = L[i]; j <= i; ++j)
			{
				vec[i - 1].push_back(make_pair(-1, a[i] / a[j]));
				vec[R[i]].push_back(make_pair(1, a[i] / a[j]));
			}
		}
		else 
		{	
			for(int j = i; j <= R[i]; ++j)
			{
				vec[L[i] - 1].push_back(make_pair(-1, a[i] / a[j]));
				vec[i].push_back(make_pair(1, a[i] / a[j]));
			}
		}
	}
	LL ans = 0;
	sort(b + 1, b + n + 1);
	N = unique(b + 1, b + n + 1) - b - 1;
	for(int i = 1; i <= n; ++i)
/**/	a[i] = lower_bound(b + 1, b + N + 1, a[i]) - b;
	for(int i = 1; i <= n; ++i)
	{
		BIT::upt(a[i]);
		for(int j = 0; j < vec[i].size(); ++j)
		{
		ans += vec[i][j].first * BIT::que(find(vec[i][j].second)); 
		}
	}
	cout << ans << endl;
	return 0;
}
/*
题意：
求数对(i,j)满足max(a[i], a[i + 1], a[i + 2], ..., a[j]) <= a[i] * a[j] (i <= j) 的个数。

思路：
考虑这个东西与一段区间的最大值有关，并且这个最大值将这段区间划成了两半，显然这个最大值只对跨过它的数对有影响，如果是没跨过它的，显然在左边一段与右边一段内，这个可以递归两边下去做。
这个东西的形式与分治很像，但是它不是严格按mid来划分为两半，而是由最大值划分，不管它的复杂度，先分析一下具体实现。
假设我们在计算区间 [l,r] 数对的数量，其中这个区间的最左端的最大值的位置为 mx ，那么我们可以先考虑处理 [l,mx-1] 区间数对的数量和 [mx+1,r] 区间数对的数量。
对于当前分治区间 [l,r]，当我们确定了 ai(i在[l, mx - 1]中) 时，只需要求 [mx+1,r] 中数字不大于 mx / ai的即是以 i 为左端点答案的对数，这个可以记录询问，离线二维数点。但是一个点对是由左右端点形成的，不仅可以枚举在[l, mx - 1]中的左端点，也可以枚举[mx + 1, r]中的右端点来获得跨越mx的点对数。
于是计算答案时，我们出现了两种算答案的方法，是枚举左端点，还是右端点。
显然看[l, mx - 1]与[mx + 1, r]哪个小枚举哪个。

接下来考虑这个东西的复杂度。
对于分治区间[l, r]，由于我们对它的操作数只是枚举小一点的那个区间，而这个小区间的大小一定是比原区间大小的一半还要小。我们可以联想到启发式合并中，也是只运算了小的那一部分，并且将两者合并起来，这个只不过是启发式合并的逆形式（只运算了小的一部分，将两者分裂开来），这种“启发式分治”的复杂度显然也是log的。

注意我们不能真正按分治的形式写，因为如果不预处理出一段区间的最小值，每次按分治区间大小去算，上述分析就失效了。

debug:
1.74，N写成n
2.9，要用upper_bound时，必须要判到end的情况

*/

