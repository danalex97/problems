#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;


struct cuv
{
    char s[105];
    int len;
    cuv()
    {
        memset(s,0,sizeof(s));
    }
    inline char operator[] (const int &x) const
    {
        return s[x];
    }
}v[25005];

struct comp
{
    bool operator() (const cuv &a,const cuv &b) const
    {
        int i;
        for(i=0;i < a.len && i < b.len && a[i] == b[i]; ++ i);
        return a[i] < b[i];
    }
};


int main()
{
    freopen("dictree.in","r",stdin);
    freopen("dictree.out","w",stdout);

    int show;
    int n,i,j;

    scanf("%d\n",&n);

    for(i=1;i<=n;++i)
    {
        scanf("%s",v[i].s);
        v[i].len = strlen(v[i].s);
    }

    sort(v+1,v+n+1,comp());
    show = v[1].len + 1;
    for(i=2;i<=n;++i)
    {
        for(j=0;j < v[i-1].len && j < v[i].len && v[i-1][j] == v[i][j]; ++ j );

        if(j < v[i].len)
            show += v[i].len-j;

    }

    printf("%d\n",show);

    return 0;
}
