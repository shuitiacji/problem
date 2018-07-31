#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
#define l first
#define r second
const int maxn = 4e5 + 10;
void ckmin(int &a, int b) { a = min(a, b); }
int n, m;
namespace BIT
{
	int c[maxn];
	int lowbit(int x) { return x & (-x); }
	void upt(int x, int v) { while(x <= n) { c[x] += v; x += lowbit(x); } }
	int que(int x) { int ret = 0; while(x) { ret += c[x]; x -= lowbit(x); } return ret; }
}
priority_queue <pair<int, int>, vector<pair<int, int> >, less<pair<int, int> > > q;
pair<int, int> s[maxn], p[maxn];
int a[maxn], b[maxn];
vector<int> vec[maxn];
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	m = read(); n = read();
	for(int i = 1; i <= m; ++i) s[i].l = read(), s[i].r = read();
	for(int i = 1; i <= n; ++i) { a[i] = read(); p[i] = make_pair(a[i], read()); }
	sort(a + 1, a + n + 1);
	int N = unique(a + 1, a + n + 1) - a - 1;
	N++;
	a[N] = INT_MAX;
	memset(b, 0x3f, sizeof(b));
	for(int i = 1; i <= n; ++i)
		ckmin(b[lower_bound(a + 1, a + N + 1, p[i].first) - a], p[i].second);
	for(int i = 1; i <= m; ++i)
	{
		s[i].l = lower_bound(a + 1, a + N + 1, s[i].l) - a;
		int tmp = s[i].r;
		s[i].r = lower_bound(a + 1, a + N + 1, s[i].r) - a - 1;
		if(tmp == a[s[i].r + 1]) s[i].r++;
		if(s[i].l <= s[i].r) vec[s[i].l].push_back(s[i].r);
	}
	int ans = m;
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 0; j < vec[i].size(); ++j) { 
			q.push(make_pair(vec[i][j], i)); 
			BIT::upt(i, 1); BIT::upt(vec[i][j] + 1, -1); 
		}
		int sum = BIT::que(i);
		while(sum > b[i])
		{
			pair<int, int> u = q.top(); q.pop();
			BIT::upt(u.second, -1); BIT::upt(u.first + 1, 1);
			sum--; ans--;
		}
	}
	cout << ans << endl;
	return 0;
}
/*
题意：
Koishi喜欢线段。
她的 n 条线段都能表示成数轴上的某个闭区间 [l,r] 。Koishi喜欢在把所有线段都放在数轴上，然后数出某些点被多少线段覆盖了。
Flandre看她和线段玩得很起开心，就抛给她一个问题：
数轴上有 m 个点突然兴奋，如果自己被身上覆盖了超过 x 条线段，这个点就会浑身难受然后把Koishi批判一番。
Koishi十分善良，为了不让数轴上的点浑身难受，也为了让自己开心，她想在数轴上放入尽量多的线段。
按照套路，Koishi假装自己并不会做这道题，所以她就来求你帮忙。并承诺如果你解决了问题就给你打一通电话。

思路：
正解是贪心 从左到右考虑每一个点和线段 这个点不满足条件就删除覆盖它的且r最大的线段
实现起来有好多做法，标程用了set维护覆盖当前考虑点的所有线段
其实加减线段 询问一个点覆盖次数直接差分后用树状数组就好了.....然后用一个堆维护当前加入的所有线段为了取出r最大的线段
暴力的话可以跑网络流

*/
