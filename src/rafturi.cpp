#include <cstdio>
#include <cstring>
using namespace std;
char s[200005];
int len;
int st;
#define mod1 666013
#define mod2 611953
#define p1 73
#define p2 79
int hash1,hash2;
int revhash1,revhash2;
void read()
{
    freopen("palindrom.in","r",stdin);
    freopen("palindrom.out","w",stdout);
    scanf("%s",s);
    len = strlen(s);
    st = len;
}
void solve()
{
    int i = len-1;
    int P1,P2;
    for(P1 = P2 = 1;i>=0;--i)
    {
        hash1 = (hash1 * p1 + s[i]) % mod1;
        hash2 = (hash2 * p2 + s[i]) % mod2;

        revhash1 = (s[i] * P1 + revhash1) % mod1;
        revhash2 = (s[i] * P2 + revhash2) % mod2;

        if(hash1 == revhash1 && hash2 == revhash2)
            st = i;


        P1 = (P1 * p1)% mod1;
        P2 = (P2 * p2)%mod2;
    }
}
void print()
{
    printf("%s",s);
    int i;
    for(i = st-1 ; i >= 0 ; -- i)
        printf("%c",s[i]);
    printf("\n");
}
int main()
{
    read();
    solve();
    print();
    return 0;
}
