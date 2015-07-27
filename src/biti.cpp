#include <stdio.h>

int main()
{
    freopen("adunare.in","r",stdin);
    freopen("adunare.out","w",stdout);
    int a,b,rez;
    scanf("%d%d",&a,&b);
    __asm__
    (
        "movl %1 , %%eax;"
        "addl %2 , %%eax;"
        "movl %%eax , %0;"
        :"=r"(rez)
        :"r"(a),"r"(b)
        :"%eax"
    );
    printf("%d\n",rez);
}
