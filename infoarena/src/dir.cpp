#include <cstdio>
#include <algorithm>
using namespace std;
#define maxn 50001
int N,M;
struct street
{
    int D,L;
}v[maxn];
bool comp(street a,street b)
{
    if(a.D <= b.D)
        return 1;
    return 0;
}
int show;
int lonL,lonD;
int main()
{
    freopen("orase.in","r",stdin);
    freopen("orase.out","w",stdout);
    scanf("%d %d\n",&M,&N);
    int i;
    for(i=1;i<=N;++i)
        scanf("%d %d\n",&v[i].D,&v[i].L);
    sort(v+1,v+N+1,comp);
    lonL = v[1].L;
    lonD = v[1].D;
    for(i=2;i<=N;++i)
    {
        show = max(show,lonL + v[i].L +v[i].D - lonD );
        if(v[i].L > lonL + v[i].D - lonD)
        {
            lonL = v[i].L;
            lonD = v[i].D;
        }
    }
    printf("%d\n",show);
}
