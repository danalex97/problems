#include <cstdio>
using namespace std;
char *p;
const int maxn = 250005;
const int log2 = 18;
int A[log2+1][maxn];
int n,m;

void update(int care,int mos)
{
    int i;
    A[0][care] = mos;
    for(i = 1 ; i <= log2 && A[i-1][care]; ++ i )
        A[i][care] = A[i-1][A[i-1][care]];
}
int query(int care,int mos)
{
    int i;
    for(i = 0 ; (1 << i) <= mos; ++ i)
    {
        if( (1 << i) & mos)
        {
            mos ^= (1<<i);
            care = A[i][care];
        }
    }
    return care;
}
void read(int &a)
{
    a ^= a;
    while(*p && (*p > '9' || *p < '0'))
        ++p;
    while(*p >= '0' && *p <= '9')
        a = a * 10 + *(p++) - 48;
}


int main()
{
    freopen("stramosi.in","r",stdin);
    freopen("stramosi.out","w",stdout);
    fseek(stdin,0,SEEK_END);
    int x,y,i,len = ftell(stdin);
    p = new char[len];
    rewind(stdin);
    fread(p,1,len,stdin);
    read(n);
    read(m);
    for(i = 1 ; i <= n ; ++ i)
    {
        read(x);
        update(i,x);
    }
    while(m--)
    {
        read(x);
        read(y);
        printf("%d\n",query(x,y));
    }
    return 0;
}
