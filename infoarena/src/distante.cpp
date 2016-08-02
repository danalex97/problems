#include <iostream>
#include <cstdio>

using namespace std;

    long long unsigned  n,p;
int main()
{
    freopen("suma.in","r",stdin);
    freopen("suma.out","w",stdout);
    scanf("%d%d",&n,&p);
    n = n % p;
    long long unsigned s = (n-1)*n*(n+1)/3;
    cout << (s%p);
    return 0;
}
