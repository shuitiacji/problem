#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL Min(LL a, LL b)
{
	return a < b ? a : b;
}
char s[300100];
int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	int n, x, y;
	scanf("%d%d%d", &n, &x, &y);
	scanf("%s", s);
	int fg = 0, cnt = 0;
	for(int i = 0; i < n; ++i)
	{
		if(s[i] == '0')
		{
			if(!fg) { fg = 1; cnt++; } 
		}	
		else if(fg)  fg = 0;
	}
	LL ans = 0;
/**/if(cnt == 0) { cout << 1LL * cnt * y << endl; return 0; }
	ans += Min(1LL * cnt * y, 1LL * (cnt - 1) * x + 1LL * y);
	cout << ans << endl;
	return 0;
}
/*
题意：是一段只有0,1的字符串，变成全为1，有两种变法，一种花费x，使任意一段字符串逆转，一种花费是y，使任意一段字符串0变为1，1变0，求最小花费

思路：花费为x的只能改变0,1顺序，只有花费为y的操作能使0改1，但要经量使0连续在一块，要想得到全为1，要么先逆转使0都移到一起再变成1，要么直接让每部分0变1，观察010010可知当有n段字符串为0时（此时是n为3），只需改变n-1（2）次部分字符串就可使0都在一块，知道这个之后只需比较x，y大小即可
这种题目要发现题目中操作实际上减少了哪些量
debug:
26行
*/
