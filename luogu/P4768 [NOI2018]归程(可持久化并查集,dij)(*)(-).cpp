#include<bits/stdc++.h>
using namespace std; const int maxn = 200010, maxm = 800100;
typedef long long LL;
int read()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return x * f;
}
struct node
{
	int u, v, l, a;
	bool operator < (const node &b) const
	{
		return a > b.a;
	}
}e[maxm];
int n, m;
int to[maxm], nxt[maxm], head[maxn], w[maxm], d[maxn], val[maxm], len;
int f[maxn], sz[maxn], ans[maxn], hs[maxm];
int E;
void add(int x, int y, int z)
{
	to[++E] = y; nxt[E] = head[x]; head[x] = E; w[E] = z;
	to[++E] = x; nxt[E] = head[y]; head[y] = E; w[E] = z;
}
struct SGT
{
	int rt[maxm];
	int tot, fg;
	int ls[maxn * 40], rs[maxn * 40], t[maxn * 40];
	void build(int &o, int l, int r)
	{
		o = ++tot;
		if(l == r) 
		{
			t[o] = fg ? ans[l] : f[l];
			return ;
		}
		int mid = (l + r) >> 1;
		build(ls[o], l, mid); build(rs[o], mid + 1, r);
	}
	void upt(int o, int &o1, int l, int r, int p, int v)
	{
		o1 = ++tot;
		ls[o1] = ls[o]; rs[o1] = rs[o];
		if(l == r) { t[o1] = v; return ; }
		int mid = (l + r) >> 1;
		if(p <= mid) upt(ls[o], ls[o1], l, mid, p, v);
		else upt(rs[o], rs[o1], mid + 1, r, p, v);
	}
	int que(int o, int l, int r, int p)
	{
		if(l == r) { return t[o]; }
		int mid = (l + r) >> 1;
		if(p <= mid) return que(ls[o], l, mid, p);
		else return que(rs[o], mid + 1, r, p);
	}
}S1, S2;
void dij()
{
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
	memset(d, -1, sizeof(d));
	q.push(make_pair(0, 1)); d[1] = 0;
	while(!q.empty())
	{
		int u = q.top().second; q.pop();
		for(int i = head[u]; i; i = nxt[i])
		{
			int v = to[i];
			if(d[v] == -1 || d[v] > d[u] + w[i])
			{
				d[v] = d[u] + w[i];
				q.push(make_pair(d[v], v));
			}
		}
	}
}
int find(int x)
{
	int r = x;
	while(r != f[r]) r = f[r];
	return r;
}
int k;
void uni(int u, int v)
{
	int f1 = find(u), f2 = find(v);
	if(f1 == f2) return ;
	if(sz[f2] > sz[f1]) swap(f1, f2);
	f[f2] = f1;
	S1.upt(S1.rt[k - 1], S1.rt[k], 1, n, f2, f1);
	int tmp = min(ans[f2], ans[f1]);
	if(ans[f1] != tmp) S2.upt(S2.rt[k - 1], S2.rt[k], 1, n, f1, tmp);
	ans[f1] = tmp;
	sz[f1] += sz[f2];
}
int XZ_AK_IOI(int x)
{
	if(x < val[len]) return len + 1;
	if(x > val[1]) return -1;
	int l = 1, r = len, Ans = len + 1;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(x >= val[mid]) Ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	return Ans;
}
int sp_find(int x, int y)
{
	int r = x;
	while(1)
	{
		int tmp = S1.que(S1.rt[y], 1, n, r);
		if (r == tmp) return r;
		r = tmp;
	}
}
void init()
{
	E = 0;
	memset(head, 0, sizeof(head));
	memset(S1.rt, 0, sizeof(S1.rt));
	memset(S1.t, 0, sizeof(S1.t));
	memset(S1.ls, 0, sizeof(S1.ls));
	memset(S1.rs, 0, sizeof(S1.rs));
	S1.tot = 0;
	memset(S2.rt, 0, sizeof(S2.rt));
	memset(S2.t, 0, sizeof(S2.t));
	memset(S2.ls, 0, sizeof(S2.ls));
	memset(S2.rs, 0, sizeof(S2.rs));
	S2.tot = 0;
}
bool cmp(int a, int b)
{
	return a > b;
}
main()
{
	freopen("return.in", "r", stdin);
	freopen("return.out", "w", stdout);
	int T = read();
	while(T--)
	{
		init();
		n = read(); m = read();
		for(int i = 1; i <= m; ++i)
		{
			int u = read(), v = read(), l = read(), a = read();
			e[i] = (node){u, v, l, a};
			val[i] = a;
			add(u, v, l);
		}
		dij();
		sort(e + 1, e + m + 1);
		sort(val + 1, val + m + 1, cmp);
		len = unique(val + 1, val + m + 1) - val - 1;
		for(int i = 1; i <= n; ++i) f[i] = i, ans[i] = d[i], sz[i] = 1;
		S1.fg = 0; S2.fg = 1;
		S1.build(S1.rt[0], 1, n); S2.build(S2.rt[0], 1, n);
		int cnt = 1;
		for(int i = 1; i <= m; ++i)
		{
			k = i;
			uni(e[i].u, e[i].v);
			if(e[i].a == val[cnt]) hs[cnt] = i;
			else cnt++, hs[cnt] = i;
			if(!S1.rt[i]) S1.rt[i] = S1.rt[i - 1], S2.rt[i] = S2.rt[i - 1];
			if(!S2.rt[i]) S2.rt[i] = S2.rt[i - 1];
		}
		int Q = read(), K = read(), S = read();
		int lasans = 0;
		for(int i = 1; i <= Q; ++i)
		{
			int v0 = read(), p0 = read();
			v0 = (v0 + K * lasans - 1) % n + 1;
			p0 = (1LL * p0 + 1LL * K * lasans) % (S + 1);	
			p0 = XZ_AK_IOI(p0);
			if(p0 == -1) 
				p0 = 1;
			p0 = hs[p0 - 1];
			int tmp = sp_find(v0, p0);
			printf("%d\n", lasans = S2.que(S2.rt[p0], 1, n, tmp));
		}
	}
	return 0;
}
/*
题意：
本题的故事发生在魔力之都，在这里我们将为你介绍一些必要的设定。 魔力之都可以抽象成一个 n 个节点、m 条边的无向连通图（节点的编号从 1 至 n）。我们依次用 l,a 描述一条边的长度、海拔。 作为季风气候的代表城市，魔力之都时常有雨水相伴，因此道路积水总是不可避免 的。由于整个城市的排水系统连通，因此有积水的边一定是海拔相对最低的一些边。我们用水位线来描述降雨的程度，它的意义是：所有海拔不超过水位线的边都是有积水的。
Yazid 是一名来自魔力之都的OIer，刚参加完ION2018 的他将踏上归程，回到他 温暖的家。 Yazid 的家恰好在魔力之都的1 号节点。对于接下来Q 天，每一天Yazid 都会告 诉你他的出发点v ，以及当天的水位线p。 每一天，Yazid 在出发点都拥有一辆车. 。这辆车由于一些故障不能经过有积水的边。 Yazid 可以在任意节点下车，这样接下来他就可以步行经过有积水的边。但车会被留在他下车的节点并不会再被使用。 需要特殊说明的是，第二天车会被重置，这意味着：
车会在新的出发点被准备好。
Yazid 不能利用之前在某处停放的车。 Yazid 非常讨厌在雨天步行，因此他希望在完成回家这一目标的同时，最小化他步行经过的边的总长度。请你帮助 Yazid 进行计算。 本题的部分测试点将强制在线，具体细节请见【输入格式】和【子任务】。

思路：
考虑离线，显然排序边的海拔与询问的海拔，一边做过去，只会加边，对于答案，显然是在同一个并查集内都可以开车到达，然后只需要查这个并查集内里离终点最近的点。这个可以在并查集合并的时候取个最小值。
考虑在线，能否把所有可能出现询问情况记下来，快速查询。
考虑把并查集持久化，（也就是用主席树维护f与ans的历史版本），对边排序，每加一条边记录一个历史版本。查询时把权值离散化，二分查到是哪个历史版本，跳回去查询即可。
*/
