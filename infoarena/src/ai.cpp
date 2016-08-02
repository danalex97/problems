#include <fstream>
#include <cstdio>

using namespace std;

int suma[1000010];
long long unsigned sumadiv[1000010];

void ciur(int m)
{
    int i,j;
    for(i=2;i<=m;++i)
        for(j=i;j<=m;j+=i)
            suma[j]+= i;
}

inline int max(int a,int b)
{
    if(a>b)
        return a;
    return b;
}
int main()
{
    ifstream in("sumdiv2.in");
    freopen("sumdiv2.out","w",stdout);
    int n,m;
    m = -(1<<30);
    in >> n;
    int a[100010];
    int b[100010];
    int i;
    for(i=0;i<n;++i)
    {
        in >> a[i] >> b[i];
        m = max(m,b[i]);
    }
    ciur(m+1);
    sumadiv[1] = 1;
    for(i=2;i<=m+1;++i)
        sumadiv[i] = suma[i] + sumadiv[i-1];
    for(i=0;i<n;++i)
        printf("%lld\n",sumadiv[b[i]] - sumadiv[a[i]-1] + b[i]-a[i]+1);
    return 0;
}
