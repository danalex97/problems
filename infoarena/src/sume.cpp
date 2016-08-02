#include <cstdio>
#include <cstring>
using namespace std;

const int baza = 10;

int a[150],b[150],rez[150];
int unu[150] = {1,1};
void big_add(int *a,int *b)
{
    int i,t;
    for(i= 1 , t = 0 ; i <= a[0] || i <= b[0] || t; ++ i , t/= baza)
    {
        a[i] = (t += a[i] + b[i]) % baza;
    }
    a[0] = i - 1;
}

void big_mul(int *a,int *b)
{
    int i,j,t;
    int *c = new int[1000];
    memset(c,0,1000);
    for(i = 1 ; i <= a[0] ; ++ i)
    {
        for(j = 1 , t = 0 ; j <= b[0] || t ; ++ j , t/= baza)
            c[i + j - 1] = (t += c[i + j - 1] +  a[i] * b[j]) % baza;
        if(c[0] < i + j - 2)
            c[0] = i + j - 2;
    }
    memcpy(a,c,1000);
    delete[] c;
}
void big_sub(int *a,int *b)
{
    int i,t;
    for(i = 1 , t = 0 ; i <= a[0] || i <= b[0] ; ++ i)
    {
        a[i] -= ( i <= b[0] ? b[i] : 0 ) + t;
        a[i] += (t = a[i] < 0) * baza;
    }
    for(;a[0] > 1 && !a[a[0]];--a[0]);
}

void small_div(int *a,int b)
{
    int i,t;
    for(i = a[0],t=0; i  ; --i,t%=b)
        a[i] = (t = t * 10 + a[i])/b;

    for(;a[0] > 1 && a[a[0]] == 0;--a[0]);
}

void small_eq(int *a,int b)
{
    int i;
    for(i = 1 ; b ; ++ i , b/= baza)
        a[i] = b % baza;
    a[0] = i-1;
}

void print(int *a)
{
    int i;
    printf("%d",a[a[0]--]);
    for(i = a[0]; i ; -- i)
        printf("%.1d",a[i]);
}


int main()
{
    int x,y;
    freopen("tort.in","r",stdin);
    freopen("tort.out","w",stdout);
    scanf("%d %d\n",&x,&y);
    small_eq(a,x);
    small_eq(b,y);

    big_add(a,unu);
    big_add(b,unu);

    big_add(rez,a);
    big_add(rez,b);

    big_mul(rez,a);
    big_mul(rez,b);

    small_div(rez,2);
    print(rez);
    return 0;
}
