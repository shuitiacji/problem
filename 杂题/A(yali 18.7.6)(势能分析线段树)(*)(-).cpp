#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) {if(c == '-') f = -1; c = getchar();}
	while(isdigit(c)) {x = (x << 3) + (x << 1) + (c ^ 48); c = getchar();}
	return x * f;
}
const int maxn = 500100;
#define ls o << 1, l, mid
#define rs (o << 1) | 1, mid + 1, r
/**/const int ALL = INT_MAX;
int n, m, a[maxn], And[maxn << 2], Or[maxn << 2], Min[maxn << 2];
int tag1[maxn << 2], tag2[maxn << 2];
void maintain(int o)
{
	And[o] = And[o << 1] & And[o << 1 | 1];
	Or[o] = Or[o << 1] | Or[o << 1 | 1];
	Min[o] = min(Min[o << 1], Min[(o << 1) | 1]);
}
void build(int o, int l, int r)
{
	tag1[o] = ALL; tag2[o] = 0;
	if(l == r)
	{
		And[o] = Or[o] = Min[o] = a[l];
		return ;
	}
	int mid = l + r >> 1;
	build(ls); build(rs); maintain(o);
}
void AND_down(int o, int v)
{
	Min[o] &= v; And[o] &= v; Or[o] &= v; tag1[o] &= v; tag2[o] &= v;
}
void OR_down(int o, int v)
{
	Min[o] |= v; And[o] |= v; Or[o] |= v; tag2[o] |= v; tag1[o] |= v;
}
void pushdown(int o)
{
	if(tag1[o] != ALL)
	{
		AND_down(o << 1, tag1[o]); AND_down((o << 1) | 1 , tag1[o]);
		tag1[o] = ALL;
	}
	if(tag2[o])
	{
		OR_down(o << 1, tag2[o]); OR_down((o << 1) | 1, tag2[o]);
		tag2[o] = 0;
	}
}
void AND_upt(int o, int l, int r, int x, int y, int v)
{
	if(x <= l && r <= y && (And[o] & v) == (Or[o] & v))
	{
		AND_down(o, v);
		return ;
	}
	pushdown(o);
	int mid = (l + r) >> 1;
	if(x <= mid) AND_upt(ls, x, y, v);
	if(y > mid) AND_upt(rs, x, y, v);
	maintain(o);
}
void OR_upt(int o, int l, int r, int x, int y, int v)
{
	if(x <= l && r <= y && (And[o] & (v ^ ALL)) == (Or[o] & (v ^ ALL)))
	{
		OR_down(o, v);
		return ;
	}	
	pushdown(o);
	int mid = (l + r) >> 1;
	if(x <= mid) OR_upt(ls, x, y, v);
	if(y > mid) OR_upt(rs, x, y, v);
	maintain(o);
}
int que(int o, int l, int r, int x, int y)
{
	if(x <= l && r <= y) return Min[o];
	pushdown(o);
	int mid = (l + r) >> 1, ret = INT_MAX;
	if(x <= mid) ret = min(ret, que(ls, x, y));
	if(y > mid) ret = min(ret, que(rs, x, y));
	return ret;
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)	a[i] = read();
	build(1, 1, n);
	for(int i = 1; i <= m; ++i)
	{
		int opt = read(), l = read(), r = read();
		if(opt == 1)
		{
			int x = read();
			AND_upt(1, 1, n, l, r, x);
		}
		if(opt == 2)
		{
			int x = read();
			OR_upt(1, 1, n, l, r, x);
		}
		if(opt == 3)
		{
			printf("%d\n", que(1, 1, n, l, r));
		}
	}
	return 0;
}
/*
题意：
给定一个长度为n的序列A，下标从1开始。对其依次进行m次操作或询问，分为3种类型：
1 l r x ： 将Al～Ar中每个元素二进制AND一个数x
2 l r x ： 将Al～Ar中每个元素二进制OR一个数x
3 l r ： 求Al～Ar中的最小值

思路：
这个东西一看就像是线段树，但会发现这东西标记不好打，因为原来的ans值在upt后不一定还是最小值，例如：
1011 100   ans：100
AND 101 后
0001 100   ans：1
前后ans的位置发生了改变

这种普通标记无法解决的问题，类似吉司机线段树，尝试一下在线段树各种暴力操作，最后势能分析证明出均摊复杂度。
思考一下区间取min吉司机线段树中，思想即为能够直接修改max就直接修改，不能直接修改就递归下去修改。
这里也类似，先想一下什么情况能够不受影响的直接修改Min
先对每个线段树节点记一下区间的AND值和OR值
对于AND x操作，如果x&AND[o]==x&OR[o]，即三者共有的1必须是一样的，要不然区间中就会有部分值要不同程度地变小，就会有一些值变小的多一些，可能成为新的ans，满足这个条件显然可以直接修改Min，否则递归到儿子
对于OR x操作，如果((2^32-1)^x)&AND[o]==((2^32-1)^x)&OR[o]，即AND与OR在除去都会加上x的1之外，其他的1必须是一样的，要不然就会有值不同程度地变大，满足显然也可以直接修改

打标记时记两个tag OR/AND，注意不是区间覆盖，所以一个AND操作可能会影响到OR的tag

接下来势能分析一下复杂度：
先很天真地定义标记类，把一对OR[o]和AND[o]作为标记类，满足：
1.同一次upt操作中产生的新的标记(OR[o],AND[o])属于同一类
2.同一个标记下传产生的新标记属于同一类
3.不满足以上两个条件的任意两个标记不属于同一类
每一个标记类的权值等于所有子树中存在这一类标记的点的个数，势能函数就为线段树中所有标记类的权值总和。
接着我们便发现了问题，在暴力dfs时，因为修改不是直接置成当前的标记类的值，而是位运算一下(AND一个x,OR一个x)，dfs到这个节点时，有可能不一样的标记类还会存活下来（因为涉及到位运算，因为只是把OR，AND位运算一下，所以不能保证不一样的标记类一定会被搞掉，不像吉如一的例子中，不一样的一定会被搞掉），这样暴力dfs时势能不一定会减少，无法保证复杂度。
尝试更改标记类的定义
在位运算时，不能保证所有的位上都完全和原来的标记类不一样，但能保证至少有一位不同。
可以用位数作为标记类，这样的做法积累势能很快（一个数有很多位(log(w))，加一个新的就加log(w)个(还要算上路径上的log(n))），消耗很慢（每次暴力dfs到一个点只能保证至少消耗1）
总时间复杂度为O(nlog(n)log(w))

debug:
1.0x3f3f3f3f不是无穷大，因为本题权值范围比较大，要置成INT_MAX
*/
