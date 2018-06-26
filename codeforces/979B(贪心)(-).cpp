#include<bits/stdc++.h>
using namespace std;
int m;
int cnt[1000];
int gao(char *s){
	int n=strlen(s);
	memset(cnt,0,sizeof(cnt));
	for(int i=0;i<n;++i){
		cnt[s[i]-'A']++;
	}
	int Max=0;
	for(int i='A';i<='z';++i){
		int j=i-'A';
		if(!cnt[j])continue;
		int tmp;
		if(m>n-cnt[j]){
			tmp=n;
			if(cnt[j]==n&&m==1)
				tmp=n-1;
		}
		else tmp=m+cnt[j];
		Max=max(tmp,Max);
	}
	return Max;
}
char a[4][1000000];
int main(){
	int Max=0,Maxid;
	scanf("%d",&m);
	int fg=0;
	for(int i=1;i<=3;++i){
		scanf("%s",a[i]);
		int tmp=gao(a[i]);
		if(tmp>Max){
			Max=tmp;Maxid=i;fg=0;
		}
		else if(tmp==Max)fg=1;
	}
	if(fg==1){puts("Draw");return 0;}
	if(Maxid==1)puts("Kuro");
	if(Maxid==2)puts("Shiro");
	if(Maxid==3)puts("Katie");
	return 0;
}
/*
题意:题意：给你3个字符串，3个人各对自己的字符串执行n轮操作，每一次选择一个字符变为任意一个和原来不同的字符。最后问你谁能使自己的串中的任意重复子串出现的次数最大化。
分析：只需关注字符，子串是用来吓你的
debug：很不容易想到的一点是从a变到a，有两种方式a -> 其它 -> a，或者a -> 其它 -> 其它 -> a，即变2次或者变3次。
唯一可能变少的情况就是这个字符串全部字母相同并且n = 1，那么最后的美丽度要减一
*/
