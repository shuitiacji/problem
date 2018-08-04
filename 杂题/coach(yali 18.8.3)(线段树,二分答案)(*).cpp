#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
int TMP;
int n, m, k;
int a[maxn];
int t[maxn << 2], tag[maxn << 2];
int top;
pair<int, int> sta[maxn];
#define ls o << 1, l, mid
#define rs o << 1 | 1, mid + 1, r
void maintain(int o){
	t[o]=t[o<<1]+t[o<<1|1];
}
void build(int o,int l,int r){
	tag[o]=-1; t[o] = 0;
	if(l==r){
		t[o]=(a[l]<=TMP?0:1);
		return ;
	}
	int mid=(l+r)>>1;
	build(ls);build(rs);
	maintain(o);
}
void pushdown(int o,int l,int r){
	if(tag[o]==-1)return ;
	int mid=(l+r)>>1;
	tag[o<<1]=tag[o];t[o<<1]=(mid-l+1)*tag[o];
	tag[o<<1|1]=tag[o];t[o<<1|1]=(r-mid)*tag[o];
	tag[o]=-1;
}	
void upt(int o,int l,int r,int X,int Y,int v){
	if(X<=l&&r<=Y){
		tag[o]=v;
		t[o]=(r-l+1)*v;
		return ;
	}
	pushdown(o,l,r);
	int mid=(l+r)>>1;
	if(X<=mid)upt(ls,X,Y,v);
	if(Y>mid)upt(rs,X,Y,v);
	maintain(o);
}
int que(int o,int l,int r,int X,int Y){
	if(X<=l&&r<=Y){
		return t[o];
	}
	pushdown(o,l,r);
	int mid=(l+r)>>1,ret=0;
	if(X<=mid)ret+=que(ls,X,Y);
	if(Y>mid)ret+=que(rs,X,Y);
	return ret;
}
int gao(int X)
{
	TMP = X;
	build(1, 1, n);
	for(int i = 1; i <= top; ++i)
	{
		int x = sta[i].first, y = sta[i].second;
		int tmp = que(1, 1, n, x, y);
		upt(1, 1, n, x, y, 0);
/**/	if(tmp == 0) continue;
		if(tmp & 1)
		{
			tmp >>= 1;
			upt(1, 1, n, x, x + tmp, 1);
			upt(1, 1, n, y - tmp + 1, y, 1);
		}
		else {
			tmp >>= 1;
			upt(1, 1, n, x, x + tmp - 1, 1);
			upt(1, 1, n, y - tmp + 1, y, 1);
		}
	}
	return que(1, 1, n, k, k) ^ 1;
}
int main()
{
	freopen("coach.in", "r", stdin);
	freopen("coach.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	for(int i = 1; i <= m; ++i)
	{
		int opt;
		scanf("%d", &opt);
		if(opt == 1)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			sta[++top] = make_pair(x, y);
		}
		else
		{
			int x;
			scanf("%d", &x);
			if(top == 0) goto nxt;
/**/		if(x == 0) goto nxt;
			while(1)
			{
				--x; --top;
				if(top == 0 || x == 0) break;
			}
			nxt:;
		}
	}
	int l = 0, r = 200010, ans;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(gao(mid)) { ans = mid; r = mid - 1; }
		else l = mid + 1;
	}
	cout << ans << endl;
	return 0;
}
/*
题意：
一列数a
两种操作
1.[l,r]，把l,r中间的数从大到小排，一左一右穿插
1, 2, 3, 4, 5
变成
5, 3, 1, 2, 4
2.撤销x个1操作

思路：
考虑二分答案。
那么如何check。
假设二分的数为 x ,那么将原序列中大于 x 的数变成 1 ,小于等于 x 的数
变成 0 。于是对于1操作不再需要排序,因为变换之后,l 到 r 的形状一定是两
边各一段连续的 1 ,中间一段 0 。
利用线段树区间查询和与区间赋值。
最后判断第 k 位是否是 0 就好了。
对于2操作,直接用栈维护。

debug:
1.63
2.100
*/
