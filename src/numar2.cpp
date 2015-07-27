#include <cstdio>
#include <cstring>
using namespace std;
//(X+1) choose Y

struct num_mare
{
    char cif;
    char c[101];
}a[2][251];

const num_mare unu = {1,{0,1}};
void add(num_mare &a,const num_mare &b)
{
    int i,t;
    for(i=1,t=0;i<=a.cif || i <= b.cif || t;++i,t/=10)
        a.c[i] = (t+=a.c[i]+b.c[i])%10;
    a.cif = i-1;
}
int main()
{
    int x,y;
    int i,j;
    freopen("pm.in","r",stdin);
    freopen("pm.out","w",stdout);
    scanf("%d %d",&x,&y);
    bool c = 1;
    if(y > x+1)
    {
        printf("0\n");
        return 0;
    }
    a[0][1].cif = 1;
    a[0][1].c[1] = 1;
    for(i=2;i<=x+1;++i,c^=1)
    {
        memset(a[c],0,sizeof(a[c]));
        add(a[c][1],unu);
        add(a[c][1],a[!c][1]);
        for(j=2;j<=y && j <= i;++j)
        {
            add(a[c][j],a[!c][j]);
            add(a[c][j],a[!c][j-1]);
        }
    }
    c^=1;
    for(i=a[c][y].cif;i;--i)
        printf("%d",a[c][y].c[i]);
    printf("\n");
    return 0;
}
