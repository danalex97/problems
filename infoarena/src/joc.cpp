#include <cstdio>
using namespace std;
const int maxn = 100010;
short unsigned int a[maxn];
short unsigned int b[maxn];
bool reached[maxn];
int k;
int show = 1;
int gcd(int a,int b)
{
    if(b>a)
        return gcd(b,a);
    int r = a % b;
    while(r)
    {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

int main()
{
    freopen("perm2.in","r",stdin);
    freopen("perm2.out","w",stdout);
    scanf("%d\n",&k);
    int i;
    for(i=1;i<=k;++i)
    {
        scanf("%d\n",&a[i]);
        b[i]=a[i];
    }
    int pasi=1;
    for(i=1;i<=k;++i)
    {
        if(!reached[i])
        {
            pasi = 1;
            reached[i]|=1;
            while(!reached[b[i]])
            {
                reached[b[i]]|=1;
                b[i] = a[b[i]];
                ++pasi;
            }
            show = show * pasi / gcd(show,pasi);
        }
    }
    printf("%d\n",show);
    return 0;
}
