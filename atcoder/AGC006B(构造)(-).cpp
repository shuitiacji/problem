#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int m,x;
	scanf("%d%d",&m,&x);
	int n=2*m-1;
	if(x==1||x==n){
		puts("No");
		return 0;
	}
	puts("Yes");
	if(n==3){
		printf("1\n2\n3\n");
		return 0;
	}
	if(x==2){
		int cnt=4;
		for(int i=1;i<=m-2;++i)printf("%d\n",++cnt);
		printf("3\n2\n1\n4\n");
		for(int i=m+3;i<=n;++i)printf("%d\n",++cnt);
		return 0;
	}
	vector<int> tmp;
	for(int i=1;i<=n;++i)
		if(i!=x-1&&i!=x&&i!=x+1&&i!=x-2)
			tmp.push_back(i);
	int cnt=-1;
	for(int i=1;i<=m-2;++i)printf("%d\n",tmp[++cnt]);
	printf("%d\n%d\n%d\n%d\n",x-1,x,x+1,x-2);
	for(int i=m+3;i<=n;++i)printf("%d\n",tmp[++cnt]);
	return 0;
}
/*
题意：
给一个m层的金字塔，给出顶部的方块数字x，其他未知，要求每一个方块都是其下方，下左方和下右方的中位数，输出最底层符合要求的情况，不行就输出No。
思路：
手玩几次后，发现只有在倒数第二层上第m位与第m+1位都为x时（或第m-1与m），才能使最后为x。
*/
