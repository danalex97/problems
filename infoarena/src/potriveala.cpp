#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;
const int mod = 2011;
ifstream in("minusk.in");
ofstream out("minusk.out");
int n,k;
const int maxn = 1000005;
int p[maxn];
int m[maxn];
int main()
{
    int i;
    in >> n >> k;
    p[1] = 1;
    p[0] = 1;
    m[1] = 1;
    for(i= 2 ; i<= n; ++ i)
    {
        p[i] = p[i-1] + m[i-1];
        p[i] %= mod;
        m[i] = p[i];
        if(i - k >= 0)
            m[i] -= p[i-k];
        if(m[i] < 0)
            m[i] += mod;
        else
            m[i] %= mod;
    }
    out << (m[n]+p[n])%mod;
    return 0;
}
