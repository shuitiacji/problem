#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
const int maxn = 1e5 + 10;
struct node
{
	int x, y, z;
	bool operator < (const node &b) const
	{
		if(x == b.x) return y < b.y;
		return x < b.x;
	}
}poi[maxn];
int n, m, k;
int X[maxn], Y[maxn], lenx, leny;
typedef long long LL;
namespace BIT
{
	LL c[maxn];
	LL Max(LL x, LL y) { return x > y ? x : y; }
	int lowbit(int x) { return x & (-x); }
	void add(int x, LL v)
	{
		while(x <= leny)
			c[x] = Max(v, c[x]), x += lowbit(x);
	}
	LL que(int x)
	{
		LL r = 0;
		while(x)
			r = Max(r, c[x]), x -= lowbit(x); 
		return r;
	}
}
int main()
{
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
	n = read(); m = read(); k = read();
	for(int i = 1; i <= k; ++i)
	{
		poi[i].x = read(); poi[i].y = read(); poi[i].z = read();
		X[i] = poi[i].x;
		Y[i] = poi[i].y;
	}
	sort(X + 1, X + k + 1); sort(Y + 1, Y + k + 1);
	lenx = unique(X + 1, X + k + 1) - X - 1;
	leny = unique(Y + 1, Y + k + 1) - Y - 1;
	sort(poi + 1, poi + k + 1);
	for(int i = 1; i <= k; ++i)
	{
		LL tmp = BIT::que(lower_bound(Y + 1, Y + leny + 1, poi[i].y) - Y) + poi[i].z;
		BIT::add(lower_bound(Y + 1, Y + leny + 1, poi[i].y) - Y, tmp);
	}
	cout << BIT::que(leny) << endl;
	return 0;
}
/*
题目:
小 H 是一个喜欢旅行的女孩子。
她来到了一个国家,这个国家可以被看做 n × m 的方格,这个国家有 k 个景点,每个景
点用一个三元组 (x i , y i , w i ) 表示位置在 (x i , y i )、小 H 对它的好感度为 w i 。小 H 从 (1, 1) 出发,以一条最短路径走到 (n, m)。小 H 希望你帮她计算她可以获得的最大的好感度是多少。

思路:
考虑就是个二维的dp
直接做是k^2的(离散化一下)
考虑你在转移时,考虑的是之前一个二维矩形内(只能走上和右)的dp最大值.
你可以先按x排序所有景点,减去一维,再用树状数组维护y的维度.
*/
