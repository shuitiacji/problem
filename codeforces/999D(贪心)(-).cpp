#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=200077;
set<int> s;
LL t[maxn],a[maxn];
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	int tmp=n/m;
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		t[a[i]%m]++;
	}
	for(int i=0;i<m;++i){
		t[i]-=tmp;
		if(t[i]<0){
			s.insert(i);
		}
	}
	LL ans=0;
	for(int i=1;i<=n;++i){
		if(t[a[i]%m]>0){
			set<int>::iterator it=s.lower_bound(a[i]%m);
/**/		if(it==s.end())it=s.begin();
			ans+=*it-(a[i]%m);
			if(*it-(a[i]%m)<0)ans+=m,a[i]+=m;
			t[a[i]%m]--;
			t[*it]++;
			a[i]+=*it-(a[i]%m);
			if(t[*it]==0)s.erase(it);
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;++i)printf("%lld ",a[i]);
	return 0;
}
/*
题意：
n，m与n个数。
保证m是n的约数。
你可以对n个数任意一个数+1，这个操作可以很多次。
每个数最后除以m的余数必定属于{0,1,2,...,m-1}，令每个集合中的元素出现次数都为n/m，求操作最小次数。

思路：
贪心。

debug:
27行一定要加上，end()不属于原集合

*/
