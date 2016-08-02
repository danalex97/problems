#include <cstdio>
#include <algorithm>
using namespace std;

struct rct
{
    int T_min,T_max;
}v[8001];

bool comp(rct a,rct b)
{
    if(a.T_min < b.T_min)
        return 1;
    if(a.T_min == b.T_min)
        if(a.T_max > b.T_max)
            return 1;
    return 0;
}

int main()
{
    freopen("reactivi.in","r",stdin);
    freopen("reactivi.out","w",stdout);
    int i,N;
    int show=1;
    int c;
    scanf("%d",&N);
    for(i=1;i<=N;++i)
        scanf("%d %d\n",&v[i].T_min,&v[i].T_max);
    sort(&v[1],&v[N+1],comp);
    c = v[1].T_max;
    for(i=2;i<=N;++i)
    {



        if(v[i].T_min > c)
        {
            ++show;
            c = v[i].T_max;
        }
        if(v[i].T_max < c)
            c = v[i].T_max;
    }
    printf("%d\n",show);
}
