#include<bits/stdc++.h>
using namespace std;
struct node{
	int val,pos1,pos2;
	node(int a,int b,int c): val(a),pos1(b),pos2(c){}
	bool operator > (const node &b) const {
		if(val==b.val)return pos1>b.pos1;
		return val>b.val;
	}
};
char s[200010];
int nex[200010],pre[200010],c[200010],v[200010],ans1[200010],ans2[200010],mak[200010];
int cnt;
priority_queue<node,vector<node>,greater<node> > q;
int main(){
	freopen("DancingLessons.in","r",stdin);
	freopen("DancingLessons.out","w",stdout);
	int n;
	scanf("%d",&n);
	scanf("%s",s);
	for(int i=1;i<=n;++i){
		scanf("%d",&v[i]);
		c[i]=(s[i-1]=='B')?1:0;
		if(i!=1)pre[i]=i-1;
		if(i!=n)nex[i]=i+1;
	}
	for(int i=1;i<n;++i){
		if(c[i]!=c[i+1]){
			q.push(node(abs(v[i]-v[i+1]),i,i+1));
		}
	}
	while(!q.empty()){
		node u=q.top();q.pop();//printf("%d %d\n",u.pos,nex[u.pos]);
		if(mak[u.pos1]||mak[u.pos2])continue;
		cnt++;
		ans1[cnt]=u.pos1;ans2[cnt]=u.pos2;	
		mak[u.pos1]=1;mak[u.pos2]=1;
		int tmp1=pre[u.pos1],tmp2=nex[u.pos2];
		if(tmp1!=0)nex[tmp1]=tmp2;
		if(tmp2!=0)pre[tmp2]=tmp1;
/**/	if(c[tmp1]!=c[tmp2]&&(long long )tmp1*tmp2!=0){
			q.push(node(abs(v[tmp1]-v[tmp2]),tmp1,tmp2));
		}
	}
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;++i){
		printf("%d %d\n",ans1[i],ans2[i]);
	}
	return 0;
}
/*
有 n 个人参加一个舞蹈课。每个人的舞蹈技术由整数 来决定。在舞
蹈课的开始,他们从左到右站成一排。当这一排中至少有一对相邻的
异性时,舞蹈技术相差最小的那一对会出列并开始跳舞。如果相差最
小的不止一对,那么最左边的那一对出列。一对异性出列之后,队伍中的空白按原顺序补上(即:若队伍为 ABCD,那么 BC 出列之后队
伍变为 AD)。舞蹈技术相差最小即是 的绝对值最小。
你的任务是,模拟以上过程,确定跳舞的配对及顺序。

思路：
链表，堆，模拟

debug：
注意链表边界
*/
