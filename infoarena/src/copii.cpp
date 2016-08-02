#include <cstdio>
#include <cstring>
using namespace std;

const int baza = 1000000000;
struct num
{
    unsigned char cate;
    unsigned int cif[200];
}a[2][505];
const int bytes = sizeof(num);
void big_add(num &a,const num &b)
{
    int i,t;
    for(i=1,t=0;i<=a.cate || i <= b.cate || t;++i,t/=baza)
        a.cif[i] = (t+= a.cif[i] + b.cif[i])%baza;
    a.cate=i-1;
}

void solve(int n,int k)
{
    int i,j;
    bool now = 0;
    a[0][0].cate=1;
    a[0][0].cif[1]=1;
    a[1][0].cate=1;
    a[1][0].cif[1]=1;
    for(i=1;i<=n;++i,now^=1)
    {
        for(j=1;j<=k;++j)
        {
            memset(&a[now][j],0,bytes);
            big_add(a[now][j],a[!now][j]);
            big_add(a[now][j],a[now][j-1]);
        }
    }
    num * show = &a[!now][k];
    j = show->cate;
    printf("%d",show->cif[j--]);
    while(j)
        printf("%09d",show->cif[j--]);
    printf("\n");
}

int main()
{
    freopen("expozitie.in","r",stdin);
    freopen("expozitie.out","w",stdout);

    int n,d,k;
    scanf("%d %d %d\n",&n,&d,&k);
    n-=(k*d);
    if(!n)
    {
        printf("1\n");
        return 0;
    }
    else if(n<0)
    {
        printf("0\n");
        return 0;
    }
    solve(d,n);
    return 0;
}
