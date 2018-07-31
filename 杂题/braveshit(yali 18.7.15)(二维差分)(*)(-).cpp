#include<bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
int read()
{
	uint x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if( c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
const int maxn = 2e3 + 10;
int n, m;
uint a[maxn][maxn], add1[maxn][maxn], add2[maxn][maxn];
void ADD(int x0, int y0, int x1, int y1, int v)
{
	if(x0 > x1) return ;
	if(y0 > y1) return ;
	add2[x0][y0] += v;
	add2[x1 + 1][y0] -= v;
	add2[x0][y1 + 1] -= v;
	add2[x1 + 1][y1 + 1] += v;
}
int main()
{
	freopen("braveshit.in", "r", stdin);
	freopen("braveshit.out", "w", stdout);
	n = read(); m = read();
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			a[i][j] = read();
	int q = read();
	for(int i = 1; i <= q; ++i)
	{
		uint x0 = read(), y0 = read(), x1 = read(), y1 = read(), v = read(); 
		uint r = x1 - x0 + 1, c = y1 - y0 + 1;
		ADD(x0, y0, x1, y1, v);
		ADD(x1 + 1, y0 + 1, x1 + 1, y1, -r * v);
		ADD(x0 + 1, y1 + 1, x1, y1 + 1, -c * v);
		add1[x1 + 1][y0] -= r * v; add1[x0][y1 + 1] -= c * v; add1[x1 + 1][y1 + 1] += r * c *v;
	}
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= m; ++j)
		{
			add2[i][j] += add2[i - 1][j] + add2[i][j - 1] - add2[i - 1][j - 1];
			add1[i][j] += add2[i][j];
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 1; j <= m; ++j)
		{
			add1[i][j] += add1[i - 1][j] + add1[i][j - 1] - add1[i - 1][j - 1];
			a[i][j] += add1[i][j];
			printf("%u ", a[i][j]);
		}
		puts("");
	}
	return 0;
}
/*
题意：
月亮中学的勇石博士最近收了一个比他低一级徒弟,他的名字是勇矢博士,人如其名,他们两个都非常的勇敢,所以勇石博士喜欢做勇敢者游戏来训练自己徒弟的勇敢程度。
勇敢者游戏是这样操作的,一开始有个 n · m 的矩阵 A,每次勇石博士
选定一个子矩阵 ((x 0 , y 0 ), (x 0 + r − 1, y 0 + c − 1)),考虑每次一个矩阵加上:
v 2v 3v · · · cv
2v 4v 6v · · · 2cv
3v 6v 9v · · · 3cv
rv 2rv 3rv · · · rcv
现在勇石博士执行了 q 次操作,需要勇矢博士求出最后每个点的值对 2 ^ 32取模的结果

思路：
由于只有一次询问，考虑差分
但是它加的东西比较奇怪，但是它也是有规律的，把它二维差分后：
v v v ... v
v v v ... v
v v v ... v
v v v ... v
主要这是加的矩形的差分，相当于原矩形差分的差分。
也就是多阶差分，考虑把原矩形差分两次，对一次修改操作，打上4个简单的差分标记（区间加v），注意这是原矩形差分的差分（二阶差分），对它最后总的搞回来，得到一阶差分，再搞一次得到原矩形。
这个东西有一点不好搞，也就是在得到一阶差分后，原先简单的在两个角打上停止标记（负标记）的方法失效了，如已得到了一阶差分：
1 1 1 0
1 1 1 0
0 0 0 0

打上-标记
 1 1 1-3
 1 1 1 0
-2 0 0 0

再差分回到原矩形
 1 2 3 0
 2 4 6 3
 0 2 4 1

发现两个角虽然变成了0, 但还是把值扩散出去了。
因为这个东西已经差分过一次，加上的值不再都一样，而是递增的，所以打上的停止标记必须也是递增的（也就是停止标记也要差分一次）
比如说把一阶差分变成这样：
1 1 1 -3
1 1 1 -3
-2 -2 -2 6

回到原矩形
1 2 3 0
2 4 6 0
0 0 0 0
*/
