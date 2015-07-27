#include <cstdio>
using namespace std;
#define maxn 40005
int f[maxn];
int up[maxn];
int n;
int x0,y0;
int x1,y1;
inline int min(const int &a,const int &b)
{
    return a < b ? a : b;
}
int sum_cif(int x)
{
    int ret=0;
    while(x)
    {
        ret += x%10;
        x/=10;
    }
    return ret;
}

int sum_to(int lin,int col)
{
    if(col == 0)
        return 0;
    int ret=0;
    if(col >= lin)
        ret += up[col-lin+1];
    ret += up[min(n+col-lin+1,n)] - up[n-lin+1];
    return ret;
}

int main()
{
    freopen("piata.in","r",stdin);
    freopen("piata.out","w",stdout);

    scanf("%d",&n);

    scanf("%d %d",&x0,&y0);

    scanf("%d %d",&x1,&y1);

    int i;
    int show=0;
    for(i=1;i<=n;++i)
        f[i] = sum_cif(i);

    for(i=1;i<=n;++i)
        up[i] = up[i-1] + f[i];

    for(i=x0;i <= x1 ; ++ i)
    {
        show += sum_to(i,y1);
        show -= sum_to(i,y0-1);
    }

    printf("%d\n",show);
    return 0;
}
