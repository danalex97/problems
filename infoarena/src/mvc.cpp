#include <cstdio>
#include <algorithm>

using namespace std;

struct incant
{
    public:
    char cuv[10];
    inline char operator [](const int &i) const
    {
        return cuv[i];
    }
}v[1000000];

class comp
{
    public:
    bool operator()(const incant &a,const incant &b)const
    {
        int i=0;
        while(a[i] == b[i] && i < 10)
            ++i;
        return a[i] < b[i];
    }
};

int main()
{
    freopen("incantatii.in","r",stdin);
    freopen("incantatii.out","w",stdout);

    int n;
    int i;
    scanf("%d\n",&n);
    for(i=0;i<n;++i)
        scanf("%s\n",v[i].cuv);

    sort(v,v+n,comp());

    for(i=0;i<n;++i)
        printf("%s\n",v[i].cuv);
    return 0;
}
