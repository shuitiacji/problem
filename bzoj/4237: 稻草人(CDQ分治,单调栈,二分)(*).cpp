#include<bits/stdc++.h>
using namespace std;
const int maxn = 200011;
typedef long long LL;
LL ans = 0;
int n, sta[maxn], sta2[maxn];
struct node
{
	int x, y;
}poi[maxn];
int cmpx(const node &a, const node &b) { return a.x < b.x; }
int cmpy(const node &a, const node &b) { return a.y < b.y; }
void gao(int l, int r)
{
	if(l == r) return ;
	int mid = (l + r) >> 1;
	sort(poi + l, poi + r + 1, cmpy);
/**/sort(poi + l, poi + mid + 1, cmpx);
	sort(poi + mid + 1, poi + r + 1, cmpx);
	int top = 0, now = l, tail = 0; 
	for(int i = mid + 1; i <= r; ++i)
	{
		while(top > 0 && poi[sta[top]].y >= poi[i].y) --top;
		sta[++top] = i;
		while(now <= mid && poi[now].x < poi[i].x)
		{
			while(tail > 0 && poi[sta2[tail]].y <= poi[now].y) --tail;
			sta2[++tail] = now;
			now++;
		}
		int L = 1, R = tail, pos = -1, tmp = poi[sta[top - 1]].x;
		while(L <= R)
		{
			int Mid = (L + R) >> 1;
			if(poi[sta2[Mid]].x > tmp) pos = Mid, R = Mid - 1;
			else L = Mid + 1;
		}
		if(pos != -1) { ans += tail - pos + 1; }
	}
/**/gao(l, mid); gao(mid + 1, r);
}
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", &poi[i].x, &poi[i].y);
/**/poi[0].x = poi[0].y = -1;
	gao(1, n);
	cout << ans << endl;
	return 0;
}
/*
题意：
JOI村有一片荒地，上面竖着N个稻草人，村民们每年多次在稻草人们的周围举行祭典。
有一次，JOI村的村长听到了稻草人们的启示，计划在荒地中开垦一片田地。和启示中的一样，田地需要满足以下条件：
田地的形状是边平行于坐标轴的长方形；
左下角和右上角各有一个稻草人；
田地的内部(不包括边界)没有稻草人。
给出每个稻草人的坐标，请你求出有多少遵从启示的田地的个数

思路：
考虑这种两维的题目，想办法用CDQ分治降维然后变成序列问题。
对y坐标分治，每次分成两半，我只考虑上面一半的点对下面的影响（也就是田地的左下角在下面一半，右上角在上面一半）。
　对于上下的内部分别按x排序，我枚举上面的点，考虑以它为右上角的矩形个数：显然这个矩形要受上半部分中离它最近的x、y都比它小的点的制约，同时下半部分的点也需要满足之间没有别的点，纵坐标已经满足条件了，只需要考虑横坐标即可。
　根据上面的条件，不难看出只需要对上半部分维护一个纵坐标单增（纵坐标大于它的无法约束）的单调栈，下半部分维护一个纵坐标单减的单调栈，每次枚举上面的点的时候，把横坐标小于它的下半部分的点全部加入下面的单调栈，在下面的单调栈二分一下就能得到答案了。

debug:
1.18行，poi + mid 要+1
2.40行，要在17行后再分治
3.49行忘写
*/
