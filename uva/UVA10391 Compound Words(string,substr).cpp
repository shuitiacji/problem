#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<set>
using namespace std;
string s;
set<string> S;
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	while(cin>>s){S.insert(s);}
	for(set<string>::iterator it=S.begin();it!=S.end();++it){
		s=*it;
		for(int i=0;i<s.size()-1;++i){
			string a=s.substr(0,i+1);
			string b=s.substr(i+1,s.size()-i-1);
			if(S.count(a)&&S.count(b)){
				cout<<s<<endl;
				break;
			}
		}
	}
	return 0;
}
/*
题意：给定一个词典，要求找出其中所有的复合词，即恰好由两个单词连接而成的单词

思路：暴力划分，set查询

debug：string的substr(位置，要复制的个数)
*/
