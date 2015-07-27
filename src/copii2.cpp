#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cstring>
using namespace std;

ifstream in("ubuntzei.in");
ofstream out("ubuntzei.out");

const int maxn = 2002;
int n,m,k;
int best[25][25];
int dp[1<<17][25];
int cost[maxn];
bool viz[maxn];
int must[25];
struct edge
{
    int to,cost;
};

class comp
{
    public:
    bool operator() (const edge &a,const edge &b)
    {
        if(a.cost == b.cost)
            return a.to < b.to;
        return a.cost < b.cost;
    }
};

vector<edge> graf[maxn];
vector<edge> :: iterator it;

set<edge,comp> q;
void dijkstra(int & root)
{
    q.clear();
    memset(cost,0,sizeof(cost));
    memset(viz,0,sizeof(viz));
    int i;
    for(i=1;i<=n;++i)
        cost[i] = 1 << 30;
    edge c;
    q.insert((edge){root,0});
    cost[root] = 0;
    while(!q.empty())
    {

        c = *q.begin();
        q.erase(q.begin());
        if(viz[c.to])
            continue;
        viz[c.to] = 1;
        for(it = graf[c.to].begin();it != graf[c.to].end();++it)
        {
            if(c.cost + it->cost < cost[it->to])
            {
                q.erase ((edge){it->to,cost[it->to]});
                cost[it->to] = c.cost + it->cost;
                q.insert((edge){it->to,cost[it->to]});
            }
        }
    }
}

void solve()
{
    int i,j,c;
    for(i=0;i < (1 << k); ++ i)
        for(j = 1 ; j <= k ; ++ j)
            dp[i][j] = 1 << 30;
    for(i=2;i<=k;++i)
        dp[ (1 << (i-1)) + 1][i] = best[1][i];
    for(i=1;i < (1<<k); i+=2)
        for(j = 1 ; j < k ; ++ j)
            if(dp[i][j] != (1<<30))
                for(c = 2 ; c <= k ; ++c)
                    if(!(i & (1 << (c-1))))
                        dp[i | (1 << c-1)][c] = min(dp[i | (1 << c-1)][c],dp[i][j] + best[j][c]);

    int show = 1 << 30;
    for(i=1;i<=k;++i)
        show = min(show,dp[(1<<k)-1][i]);
    out << show << "\n";
}
int main()
{
    int i,j,x,y,z;
    in >> n >> m >> k;
    must[1] = 1;
    ++k;
    for(i=2;i<=k;++i)
        in >> must[i];
    must[k+1] = n;
    ++k;
    sort(must+1,must+k+1);
    for(;m;--m)
    {
        in >> x >> y >> z;
        graf[x].push_back((edge){y,z});
        graf[y].push_back((edge){x,z});
    }
    for(i=1;i<=k;++i)
    {
        dijkstra(must[i]);
        for(j=1;j<=k;++j)
            best[i][j] = cost[must[j]];
    }

    solve();
    return 0;
}
