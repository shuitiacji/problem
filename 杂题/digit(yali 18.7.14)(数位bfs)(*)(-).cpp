#include<bits/stdc++.h>
using namespace std;
const int maxk = 1e6 + 10;
struct node
{
	int x, y, pre;
}xz[maxk];
int cnt, tot;
int vis[maxk], b[12], a[12];
int k, t;
void bfs()
{
	queue<int> q;
	for(int i = 1; i <= cnt; ++i)
		if(b[i])
		{
			xz[++tot] = (node){b[i], b[i] % k, 0};
			q.push(tot); vis[b[i]] = 1;
			if(!(b[i] % k))
			{
				cout << b[i] << endl;
				return ;
			}
		}	
	while(!q.empty())
	{
		int U = q.front(); q.pop();
		node u = xz[U]; 
		if(!u.y)
		{
			stack<int> sta;
			sta.push(u.x);
			for(int i = u.pre; i; i = xz[i].pre)
				sta.push(xz[i].x);
			while(!sta.empty())
			{
				printf("%d", sta.top()); 
				sta.pop();
			}
			return ;
		}
		for(int i = 1; i <= cnt; ++i)
		{
			int tmp = (u.y * 10 + b[i]) % k;
			if(!vis[tmp])
			{
				vis[tmp] = 1;
				xz[++tot] = (node){b[i], tmp, U};
				q.push(tot);
			}
		}
	}
	puts("-1");
}
int main()
{
	freopen("digit.in", "r", stdin);
	freopen("digit.out", "w", stdout);
	scanf("%d%d", &k, &t);
	for(int i = 1; i <= t; ++i)
	{
		int x;
		scanf("%d", &x);
		a[x] = 1;
	}
	for(int i = 0; i <= 9; ++i)
		if(!a[i]) b[++cnt] = i;
	bfs();
	return 0;
}
/*
题意：
给一个数n,求n的最小倍数,倍数数位上要求不含有给出的m个数位

思路：
考虑贪心，从小到大枚举不存在不合法数位的数，找到第一个是n倍数的即为答案。
这个枚举也就是从低位到高位,每一位从小到大来放数。
考虑优化减枝。
因为条件是恰好整除，引导我们往余数上想。
考虑数位 dp,也就是令 dp i 为 mod k = i 时候的最小数。
我们发现每次选余数相同最小数一定是优的，可以利用这个来减枝，即若当前数字mod k的余数已经出现过了，就可以不用选了。

因为答案太大可能存不下。
考虑用bfs代替上述过程，bfs每个节点只记当前选了1-9中哪一个，找到一个合法的节点就往上跳，把途经的数字倒序输出。
*/
