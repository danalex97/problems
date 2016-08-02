#include <vector>
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;
const int maxn = 36005;
ifstream in("catun.in");
ofstream out("catun.out");
int best[maxn];
int root[maxn];
struct edge
{
    int nod,cost;
};
vector<edge> graf[maxn];
vector<edge> :: iterator it;
queue<int> q;
void b_ford()
{
    int nod;
    while(!q.empty())
    {
        nod = q.front();
        q.pop();
        for(it = graf[nod].begin();it != graf[nod].end(); ++ it)
        {
            if(best[nod] + it->cost < best[it->nod] || (best[nod] + it->cost == best[it->nod] && root[nod] < root[it->nod]))
            {
                best[it->nod] = best[nod] + it->cost;
                root[it->nod] = root[nod];
                q.push(it->nod);
            }
        }
    }
}
void afis(const int &n)
{
    int i;
    for(i = 1 ; i<= n; ++ i)
        out << (root[i] ? (root[i] == i ? 0 : root[i]) : 0) << " ";
}
int main()
{
    int n,m,k,i,x,y,z;
    in >> n >> m >> k;
    for(i=1;i<=n;++i)
        best[i] = 1 << 29;
    for(i = 1 ; i <= k ; ++ i)
    {
        in >> x;
        best[x] = 0;
        root[x] = x;
        q.push(x);
    }
    for(i = 1 ; i <= m ; ++ i)
    {
        in >> x >> y >> z;
        graf[x].push_back((edge){y,z});
        graf[y].push_back((edge){x,z});
    }
    b_ford();
    afis(n);
    return 0;
}
