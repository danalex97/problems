#include <fstream>
using namespace std;
ifstream in("move.in");
ofstream out("move.out");
#define maxn int(1e5)+10
#define cint const int&
int n;
int v[maxn];
int best[maxn];
int lg[maxn];
int prev[maxn];
bool u[maxn];
int hi;
int bs(cint val)
{
    int i,step;
    for(step=1;step<hi;step<<=1);
    for(i=0;step;step>>=1)
        if(i + step <= hi && v[best[i+step]] <= val)
            i += step;
    return i;
}
int main()
{
    int i,x;
    in >> n;
    for(i=1;i<=n;++i)
        in >> v[i];
    hi = 1;
    best[1] = 1;
    lg[1]=1;
    for(i=2;i<=n;++i)
    {
        x = bs(v[i]);
        prev[i] = best[x];
        ++x;
        if(x > hi)
            hi = x;
        if(v[i] < v[best[x]] || best[x] == 0)
            best[x] = i;
    }
    out << n-hi << "\n";
    x = best[hi];
    for(;x;x = prev[x])
        u[v[x]] = 1;
    for(i=1;i<=n;++i)
        if(!u[i])
            out << i << " " << i-1 << "\n";
    return 0;
}
