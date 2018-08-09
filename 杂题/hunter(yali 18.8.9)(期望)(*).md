### Desription

“猎人杀” 是风靡一时的游戏 “狼人杀” 的一个变种.
游戏开始时场上有 N 个猎人, 每个猎人的技能都是一样的, 即在死后随机选择一个场上存活的猎人开一枪将其杀死. 更具体地, 每一个猎人有一个仇恨指数 W i , 每一轮猎人开枪的时候, 每一个存活的猎人被选中的概率
均与其仇恨指数成正比.
现在你按照同样的方式随机开出了第一枪, 接下来 N 轮之后所有猎人都会死, 但是 1 号猎人想知道自己期望下会在开第几枪时死掉, 如果你不能告诉他正确答案他死的时候就会朝你开出一枪.

<!--more-->

### Solution

1 号猎人死亡的轮数等于在 1 号之前死亡的猎人数 +1, 根据期望的线性性, 就等于每个猎人比 1 号猎人先死的概率和, 不难发现第 i 个猎人比 1号猎人先死的概率是: $\frac{w[i]}{w[i] + w[1]}$

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
const int mod = 998244353;
int n, w[maxn];
int Pow(int x, int p)
{
	int r = 1;
	while(p)
	{
		if(p & 1) r = 1LL * x * r % mod;
		x = 1LL * x * x % mod; p >>= 1;
	}
	return r;
}
int main()
{
	freopen("hunter.in", "r", stdin);
	freopen("hunter.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", &w[i]);
	int ans = 0;
	for(int i = 2; i <= n; ++i)
		ans = (ans + 1LL * w[i] * Pow(w[i] + w[1], mod - 2) % mod) % mod;
	cout << (ans + 1) % mod << endl;
	return 0;
}
```

