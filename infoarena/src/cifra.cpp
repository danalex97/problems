#include <cstdio>
using namespace std;

struct nrmare
{
    public:
        char c[500];
        short int nrcif;
        nrmare()
        {
            nrcif = 0;
        }
        void operator = (int a)
        {
            nrcif = 0;
            while(a)
            {
                c[++nrcif] = (a % 10);
                a/=10;
            }
        }
        void operator = (nrmare a)
        {
            int i;
            nrcif = a.nrcif;
            for(i=1;i<=nrcif;++i)
                c[i] = a.c[i];
        }
        nrmare operator + (nrmare a)
        {
            nrmare ret;
            int i,t;
            for(i=1,t=0;i<=nrcif || i <= a.nrcif || t;++i,t/=10)
                ret.c[i] = (t+= c[i] + a.c[i])%10;
            ret.nrcif = i;
            return ret;
        }
        void operator *= (int a)
        {
            int i;
            int t = 0;
            for(i=1;i<=nrcif || t;++i,t/=10)
                c[i] = ((t += c[i] * a)%10);
            nrcif = i-1;
        }
       void operator *= (nrmare b)
        {
            int i,j,t;
            nrmare cf;
            for(i=1;i<=nrcif;++i)
            {
                for(t=0,j=1;j<=b.nrcif || t;++j,t/=10)
                    cf.c[i+j-1] = (t+=cf.c[i+j-1] + c[i] * b.c[j]) % 10;
                if(i + j - 2 > cf.nrcif)
                    cf.nrcif = i + j -2;
            }
            nrcif = cf.nrcif;
            for(i=1;i<=nrcif;++i)
                c[i] = cf.c[i];
        }
        void operator += (nrmare b)
        {
            int i,t;
            for(i=1,t=0;i<=nrcif || i <= b.nrcif || t;++i,t/=10)
                c[i] = (t+=c[i] + b.c[i])%10;
            nrcif = i-1;
        }
}s[201][201];

int main()
{
    freopen("perm.in","r",stdin);
    freopen("perm.out","w",stdout);
    int n,k;
    int i,j;
    scanf("%d %d",&n,&k);
    s[1][1] = 1;
    for(i=2;i<=n;++i)
    {
        for(j=1;j<=i && j <= k;++j)
        {
            s[i][j] = s[i-1][j];
            s[i][j] *= (i-1);
            s[i][j] += s[i-1][j-1];
        }
    }
    int len = s[n][k].nrcif;
    for(;len>=1;--len)
        printf("%d",s[n][k].c[len]);
    return 0;
}
