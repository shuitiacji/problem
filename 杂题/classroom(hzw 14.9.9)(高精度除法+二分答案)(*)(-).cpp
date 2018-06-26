#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL m[500005],n[500005],t[500005];
int lm,ln;
int ck(LL x){
	memset(t,0,sizeof(t));
	for(int i=1;i<=ln;++i){
		t[i]=n[i]*x;
	}
	int lt=ln;
	for(int i=1;i<=lt;++i){
		if(t[i]>=10)lt=max(lt,i+1);
		t[i+1]+=t[i]/10;
		t[i]%=10;
	}
	if(lt>lm)return 0;
	if(lt<lm)return 1;
	for(int i=lt;i>=1;--i){
		if(t[i]>m[i])return 0;
		if(t[i]<m[i])return 1;
	}
	return 1;
}
char a[50005];
int main(){
	freopen("spring.in","r",stdin);
	freopen("spring.out","w",stdout);
	scanf("%s",a+1);
/**/lm=strlen(a+1);
	for(int i=1;i<=lm;++i){
		m[i]=a[lm-i+1]-'0';
	}
	scanf("%s",a+1);
	ln=strlen(a+1);
	for(int i=1;i<=ln;++i){
		n[i]=a[ln-i+1]-'0';
	}
	LL l=0,r=2000000000;
	LL ans;
	while(l<=r){
		LL mid=(l+r)>>1;
		if(ck(mid))ans=mid,l=mid+1;
		else r=mid-1;
	}
	cout<<ans<<endl;
	return 0;
}
/*
在幻想乡,西行寺幽幽子是以贪吃闻名的亡灵。不过幽幽子可不是只会吃,至少她还管理着
亡灵界。话说在幽幽子居住的白玉楼有一颗常年不开花的樱树——西行妖。幽幽子决定去收集
人间的春度,聚集起来让西行妖开花。很快,作为幽幽子家园艺师的魂魄妖梦收集到了 M 个
单位的春度。并且在这段时间里,幽幽子计算出要让西行妖开出一朵花需要 N 个单位的春度。
现在幽幽子想要知道,使用所有的春度,能够让西行妖开出多少朵花。

高精度除法，因为答案在ll内，二分答案，用乘法判断

debug:
30行应是a+1,写成a
*/
