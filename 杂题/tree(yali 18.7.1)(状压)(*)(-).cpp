#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int ANS[25]={0,1,2,3,3,3,4,4,4,4,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6};
int mod;int n;
LL Pow(LL x,int p){
	LL r=1;
	while(p){
		if(p&1)r=r*x%mod;
		x=x*x%mod;p>>=1;
	}
	return r;
}
void rw(int &x,int y){
	x=(x+y)%mod;
}
int f[2][(1<<24)+5];int pos[30],c[30];
void put(int x){
	vector<int> a;
	while(x){
		a.push_back(x%2);
		x/=2;
	}
	for(int i=a.size()-1;i>=0;--i)printf("%d",a[i]);
	cout<<endl;
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%d%d",&n,&mod);
	f[0][1]=1;
	for(int i=1;i<n;++i){
		int p=i&1,q=(i+1)&1;
		memset(f[p],0,sizeof(int)*(1<<(i+1)));
		for(int j=1;j<(1<<i);++j){
			if(f[q][j]){
				int cnt=1;
				for(int k=0;k<i;++k){
					c[cnt]++;
					if(j&(1<<k)){
						pos[cnt]=k;++cnt;
					}
				}
				for(int k=2;k<cnt-1;++k){
					rw(f[p][((j^(j&((1<<(pos[k-1]+1))-1)))<<1)+(j&((1<<(pos[k-1]+1))-1))],1LL*c[k+1]*f[q][j]%mod);
				}
				rw(f[p][j<<1],1LL*c[2]*f[q][j]%mod);
				rw(f[p][(j<<1)|1],1LL*c[1]*f[q][j]%mod);
				memset(c,0,sizeof(int)*(cnt));
			}
		}
	}
	int ans=0;
	for(int i=1;i<(1<<n);++i){
		if(f[((n+1)&1)][i]){
			int cnt=0;
			for(int j=0;j<n;++j)if(i&(1<<j))cnt++;
			rw(ans,1LL*cnt*f[((n+1)&1)][i]%mod);
		}
	}
	LL fac=1;
	for(int i=1;i<n;++i)fac=fac*i%mod;
	printf("%d\n%lld\n",ANS[n],1LL*ans*Pow(fac,mod-2)%mod);
	return 0;
}
/*
题意：
有一棵n个点的有根树，点编号为1-n，其中1号点为根，除了1号点外，i号点的父亲在1～i-1内均匀随机。
定义一棵树的深度为所有节点到根路径上节点数的最大值，求这棵树的期望深度。

思路：
首先要明确，因为是求节点数的最大值，而期望的线性性质只在加法上有效，这题就无法用期望来做，只能转化成记数问题，最后乘个逆元。
考虑还要看节点深度，我们的状态必须要记前面节点的深度，而这样不好处理。
我们研究一下题目性质，这里会有一个十分套路的状压：
我们要最好将这些个点的深度变成二进制，同时会发现，深度一定是连续的（每次加一个点，深度最多增加1），也就是说如果将前面点深度从小到大排序，每个点之间都会只差1或0,如果把这个东西差分一下，就完美把深度序列变成了二进制的01串。
转移的话，每次加点进来，枚举这个点的深度，直接在状态中找到那个深度，往后加个0即可，当然也有可能是新的深度，往最后加个1：
如11001转移：
深度为2：1100+0+1 ——> 110001
深度为4（新的深度） 11001+1 ——> 110011
这个实现的话很简单，加1的直接加，加0的话，把它这个深度后面的全减掉，左移，再加上刚减掉的。
同时一个深度i点只有可能通过深度i-1的父亲转移，只要找深度i-1的有多少个，就可以很方便的计数。

这种非01序列，如果差只为01,可以差分转成二进制状压。

debug:
45行
减掉这个深度后面的时，是可以直接^1111....，但后面加上来时，必须用当前状态&一下，不然会直接加上1111....。
*/
