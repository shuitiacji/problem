#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define Long LLLlll
const int maxn=210;
struct Long{
	LL q[20000];int sz;
	Long operator + (const Long &b) const{
		Long A;
		int tmp=sz>b.sz?sz:b.sz;//int k=tmp==sz;
		for(int i=1;i<=tmp;++i){
			A.q[i]=q[i]+b.q[i];
		}
		A.sz=1;
		int j=1;
		while(1){
			if(j>sz+b.sz||j>19010)break;
			if(A.q[j]!=0)A.sz=j;
			A.q[j+1]+=A.q[j]/1000;
			A.q[j]%=1000;
			++j;
		}
		return A;
	}
	void mul(LL a){
		for(int i=1;i<=sz;++i){
			q[i]=q[i]*a;
		}
		for(int i=1;i<=19010;++i){
			q[i+1]+=q[i]/1000;
			q[i]%=1000;
			if(q[i]!=0)sz=i;
		}
	}
	void print(){
		int a,b,c;
		a=q[sz]/100;q[sz]%=100;b=q[sz]/10;q[sz]%=10;c=q[sz];
		if(a>0){
			printf("%d%d%d",a,b,c);
		}
		else {
			if(b>0)printf("%d%d",b,c);
			else {
				printf("%d",c);
			}
		}
		for(int i=sz-1;i>=1;--i){
			a=0;b=0;c=0;
			a=q[i]/100;q[i]%=100;b=q[i]/10;q[i]%=10;c=q[i];
			printf("%d%d%d",a,b,c);
		}
	}
}f[maxn];
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int n;
	scanf("%d",&n);
	f[1].q[1]=0;f[1].sz=1;f[2].q[1]=1;f[2].sz=1;f[3].q[1]=2;f[3].sz=1;
	for(LL i=4;i<=n;++i){
		f[i]=f[i-2]+f[i-1];
//		cout<<i<<endl;
		f[i].mul(i-1);
	}
	f[n].print();
	return 0;
}
/*
题意：

给你一个N*N的矩阵，每行有一个障碍，数据保证任意两个障碍不在同一行，任意两个障碍不在同一列，要求你在这个矩阵上放N枚棋子（障碍的位置不能放棋子），要求你放N个棋子也满足每行只有一枚棋子，每列只有一枚棋子的限制，求有多少种方案。

思路：
正解：组合数学+高精度。
因为每一行和每一列都只有一个障碍，所以不难发现行和列是可以交换的。
我们把障碍移动到主对角线上，发现答案就是错排公式。
看上去这就是一个递推问题，那么递推式是如何推出来呢？ 当 n 个编号元素放在n个编号位置，元素编号与位置编号各不对应的方法数用 D(n) 表示，那么 D(n−1) 就表示 n−1 个编号元素放在 n−1 个编号位置，各不对应的方法数，其它类推.
第一步，把第 n 个元素放在一个位置，比如位置 kk ，一共有 n−1 种方法；
第二步，放编号为 k 的元素，这时有两种情况：(1把它放到位置 n ，那么，对于剩下的 n−1 个元素，由于第 k 个元素放到了位置 n ，剩下 n−2 个元素就有 D(n−2) 种方法；(2第 kk 个元素不把它放到位置 n ，这时，对于这 n−1 个元素，有 D(n−1) 种方法；
综上得到
D(n) = (n-1) *(D(n-2) + D(n-1))
特殊地， D(1) = 0, D(2) = 1
*/
