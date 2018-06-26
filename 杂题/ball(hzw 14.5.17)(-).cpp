#include<bits/stdc++.h>
using namespace std;
long long ans;
long long pow(long long  x,int y){
	long long ret=1;
	if(y==0)return 1;
	for(int i=1;i<=y;++i)ret*=x;
	return ret;
}
int main(){
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
	int n;
	scanf("%d",&n);
	getchar();getchar();
	for(int i=1;i<=n;++i){
		char a;
		scanf("%c",&a);
		if(a=='B')ans+=pow(2,i-1);
	}
	printf("%lld\n",ans);
	return 0;
}
/*
题意：
一个栈内初始有 n 个红色和蓝色的小球,请你按照以下规则进行操作
1. 只要栈顶的小球是红色的,将其取出,直到栈顶的球是蓝色
2. 然后将栈顶的蓝球变成红色
3. 最后放入若干个蓝球直到栈中的球数为 n
以上 3 步骤为一次操作
如栈中都是红色球,则操作停止,请问几次操作后停止
思路：找规律？
*/
