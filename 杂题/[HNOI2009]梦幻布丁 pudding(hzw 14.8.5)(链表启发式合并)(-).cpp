    #include<iostream>
    #include<cstdio>
    #include<cstring>
    #include<ctime>
    #include<cstdlib>
    #include<algorithm>
    #include<set>
	#include<vector>
    using namespace std;
    #define ls T[now].ch[0]
    #define rs T[now].ch[1]
    const int MAXN=1e6+10;
    inline char nc()
    {
        static char buf[MAXN],*p1=buf,*p2=buf;
        return p1==p2&&(p2=(p1=buf)+fread(buf,1,MAXN,stdin),p1==p2)?EOF:*p1++;
    }
    inline int read()
    {
        char c=nc();int x=0,f=1;
        while(c<'0'||c>'9'){if(c=='-')f=-1;c=nc();}
        while(c>='0'&&c<='9'){x=x*10+c-'0',c=nc();}
        return x*f;
    }
    vector<int>s[MAXN];
    int a[MAXN],f[MAXN],ans;
    void unionn(int x,int y)
    {
        for(vector<int>::iterator i=s[x].begin();i!=s[x].end();i++)
        {
            if(a[*i-1]==y)  ans--;
            if(a[*i+1]==y)    ans--;
            s[y].push_back(*i);
        }
        for(vector<int>::iterator i=s[x].begin();i!=s[x].end();i++)
            a[*i]=y;
        s[x].clear();
    }
    int main()
    {
        freopen("pudding.in","r",stdin);
		freopen("pudding.out","w",stdout);
        int n=read(),m=read();
        for(int i=1;i<=n;i++)
        {
            a[i]=read();
            if(a[i]!=a[i-1]) ans++;
            f[a[i]]=a[i];
            s[a[i]].push_back(i);
        }
        while(m--)
        {
            int opt=read();
            if(opt==2)    { printf("%d\n",ans);continue;}
            int a=read(),b=read();
            if(a==b)    continue;
            if(s[f[a]].size()>s[f[b]].size())    swap(f[a],f[b]);
            unionn(f[a],f[b]);
        }
        return 0;
}
/*
题意：N 个布丁摆成一行,进行 M 次操作.每次将某个颜色的布丁全部变成另一种颜色的,然后再询
问当前一共有多少段颜色.例如颜色分别为 1,2,2,1 的四个布丁一共有 3 段颜色.

思路：
我感觉我是暴力啊。。。
直接启发式合并一下vector就搞完了？
*/
