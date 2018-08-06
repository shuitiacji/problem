#include<bits/stdc++.h>
using namespace std;
#define delta 0.99
#define squ(x) ((x) * (x))
const int maxn = 50;
double f[maxn][maxn], s[maxn], sum, ans;
int a[maxn];
int n, m;
double gao()
{
    for(int i = 1; i <= maxn - 28; ++i)
        for(int j = 1; j <= maxn - 28; ++j)
            f[i][j] = 1e17;
    s[0] = 0;
    for(int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i];
    f[0][0] = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= i; ++j)
            for(int k = 0; k < i; ++k)
                f[i][j] = min(f[i][j], f[k][j - 1] + squ(s[i] - s[k] - sum));
    ans = min(ans, f[n][m]);
    return f[n][m];
}
void sa()
{
    int T = 100010;
    double now = gao();
    while(T > 1e-6)
    {
        int x = rand() % n + 1, y = rand() % n + 1;
        if(x == y) continue;
        swap(a[x], a[y]);
        double tmp = gao();
/**/	if(tmp - now < 0 || exp((tmp - now) / T) * RAND_MAX < rand()) now = tmp;
        else swap(a[x], a[y]);
        T *= delta;
    }
}
double TIME() { return (double) clock() / CLOCKS_PER_SEC; }
int main()
{
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]), sum += 1. * a[i];
    sum /= m * 1.;
    srand(19260817);
    ans = 1e16;
    while(TIME() < 0.985) { sa(); }
    printf("%.2lf\n", sqrt(ans / (m * 1.)));
    return 0;
}
/*
题意：
已知N个正整数：A1、A2、……、An 。今要将它们分成M组，使得各组数据的数值和最平均，即各组的均方差最小。均方差公式如下：

思路：
这不连续分组看起来很不好弄，我们可以把它转化为一个熟悉的问题：连续分组问题。这个问题可以用简单DP完成（设状态为f[i][j]，表示前i个数分j组）。
怎么实现转化呢？用于连续分组的序列 改下顺序 不就成了不连续分组的问题吗?
所以，用模拟退火rand序列，再DP统计答案，取其小者即可。

debug:
1.34, <rand()写成>
*/
