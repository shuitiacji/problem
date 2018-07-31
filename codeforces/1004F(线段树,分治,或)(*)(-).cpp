#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x = 0, f = 1; char c = getchar();
    while(!isdigit(c)) { if(c == -1) f = -1; c = getchar(); }
    while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
    return x * f;
}
struct node
{
    int x, v;
}L[21], R[21];
inline int cmp1(const node &a, const node &b)
{
    return a.x < b.x;
}
inline int cmp2(const node &a, const node &b)
{
    return a.x > b.x;
}
typedef long long LL;
const int maxn = 100010;
struct tree
{
    LL ans;
    int l[20], r[20];
}t[maxn << 2], now;
int nowl, x;
int n, m;
int a[maxn], sum[22];
int bit[21];
tree merge(const tree &a, const tree &b, int l, int r, int mid)
{
    tree c;
    c.ans = a.ans + b.ans;
    for(int i = 0; i <= 19; ++i)
    {
        L[i].x = b.l[i];
        L[i].v = bit[i];
        R[i].x = a.r[i];
        R[i].v = bit[i];
    }
    sort(L, L + 20, cmp1);
    if(L[0].x != mid + 1) L[20].x = mid + 1, L[20].v = 0;
    else L[20].x = n + 1;
    for(int i = 0; i < 19; ++i)
        if(L[i].x == L[i + 1].x) L[i + 1].v |= L[i].v, L[i].x = n + 1;
    sort(L, L + 21, cmp1);
    sum[0] = L[0].v;
    for(int i = 1; i <= 20; ++i)
        sum[i] = sum[i - 1] | L[i].v;
    sort(R, R + 20, cmp2);
    if(R[0].x != mid) R[20].x = mid, R[20].v = 0;
    else R[20].x = 0;
    for(int i = 0; i < 19; ++i)
        if(R[i].x == R[i + 1].x) R[i + 1].v |= R[i].v, R[i].x = 0;
    sort(R, R + 21, cmp2);
    int i = 0, j = 20;
    while(j >= 0 &&  R[j].x == 0) --j;
    R[j + 1].x = l - 1;
    j = 20;
    while(j >= 0 && L[j].x == n + 1) --j;
    L[j + 1].x = r;
    int nowsum = 0;
    while(i <= 20 && j >= 0)
    {
        if(R[i].x == l - 1) break;
        nowsum |= R[i].v;
        while(j > 0 && (nowsum | sum[j - 1]) >= x) --j;
/**/	if((nowsum | sum[j]) >= x) 
			c.ans += 1LL * (r - L[j].x + 1) * (R[i].x - R[i + 1].x);
        ++i;
    }
    for(int I = 0; I < 20; ++I)
    {
        c.l[I] = min(a.l[I], b.l[I]);
        c.r[I] = max(a.r[I], b.r[I]);
    }
    return c;
}
void build(int o, int l, int r)
{
    if(l == r)
    {
        for(int i = 0; i <= 19; ++i)
        {
            if(a[l] & (1 << i)) t[o].l[i] = t[o].r[i] = l;
            else t[o].l[i] = n + 1, t[o].r[i] = 0;
        }
        t[o].ans = (a[l] >= x);
        return ;
    }
    int mid = (l + r) >> 1;
    build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
    t[o] = merge(t[o << 1], t[o << 1 | 1], l, r, mid);
}
void upt(int o, int l, int r, int p, int v)
{
    if(l == r)
    {
        for(int i = 0; i <= 19; ++i)
        {
            if(v & (1 << i)) t[o].l[i] = t[o].r[i] = l;
            else t[o].l[i] = n + 1, t[o].r[i] = 0;
        }
        t[o].ans = (v >= x);
        return ;
    }
    int mid = (l + r) >> 1;
    if(p <= mid)upt(o << 1, l, mid, p, v);
	else upt(o << 1 | 1, mid + 1, r, p, v);
    t[o] = merge(t[o << 1], t[o << 1 | 1], l, r, mid);
}
void que(int o, int l, int r, int X, int Y)
{
    if(X <= l && r <= Y)
    {
        if(now.ans == -1) now = t[o];
        else now = merge(now, t[o], nowl, r, l - 1);
        return ;
    }
    int mid = (l + r) >> 1;
    if(X <= mid) que(o << 1, l, mid, X, Y);
    if(Y > mid) que(o << 1 | 1, mid + 1, r, X, Y);
}
int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    n = read(); m = read(); x = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 0; i <= 21; ++i) bit[i] = (1 << i);
    build(1, 1, n);
    for(int i = 1; i <= m; ++i)
    {
        int opt = read();
        if(opt == 1)
        {
            int X = read(), v = read();
            upt(1, 1, n, X, v);
        }
        else
        {
            int l = read(), r = read();
            nowl = l;
            now.ans = -1;
            for(int j = 0; j < 20; ++j) now.l[j] = n + 1, now.r[j] = 0;
            que(1, 1, n, l, r);
            printf("%lld\n", now.ans);
        }
    }
    return 0;
}
/*
题意：
有一个长度为 n 的数组 a1∼n，有 m
次操作，操作分两类：
将ai修改成y；
给定 l和 r，询问有多少个区间 [L,R] 满足 l≤L≤R≤r 且 aL∼R 按位或和至少为 x。（即：aL or aL+1 or ⋯ or aR≥x）
其中 x是一开始给定的一个整数。

思路：
我们称一个区间是好的当且仅当这个区间中的所有数按位或和至少为 x。一个显然的结论是，若 [l,r] 是好的，那么 [l,r′](r′>r) 也是好的；若 [l,r] 不是好的，那么 [l′,r](l′>l) 也不是好的。我们可以求出每个左端点有哪些右端点使得所选区间是好的，这个可以用双指针 O(n) 处理。
考虑分治
将 [l,r] 分成 [l,mid] 和 [mid+1,r] 后只考虑计算跨过区间的贡献。结合上面的结论，我们可以只花费 O(n) 就计算出跨区间的答案。一次查询的时间复杂度为 O(nlogn)。
考虑优化它，可根据ＯＲ的性质，设 prefixi 表示 a1∼i 的按位或和（即前缀和）。发现，从 prefix1 到 prefixn 只会变化 O(loga) 次，因此不会有一个二进制位被删除。这个性质对子区间、后缀和同样成立。考虑用这个性质优化分治查询的过程。对于一次扫描，我们只需要花费 O(logn) 的时间。
但这个分治竟然有修改操作，我们可以用善于修改的线段树来处理
因为线段树是个分治结构，考虑修改到叶子节点向上pushup时，同时要合并两个儿子区间保存答案，通过记录一个区间的前缀和中第一次出现位 i 的位置，一个区间的后缀和中第一次（靠右）出现位 i 的位置。用这两个东西就能够在 O(logn) 的时间复杂度内算出跨过中点的答案数量。用这个就可以做到log合并
神奇的用线段树解决动态分治问题
debug:
卡常技巧:对于不修改的函数参数, int x -> const int &x(对结构体有奇效)
*/
