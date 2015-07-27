#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
struct state{
    int nod,timp,watt;
};
#define maxn 55
#define maxk 1010
#define pb push_back
#define forEach(G) for( typeof(G.begin()) it = G.begin() ; it != G.end() ; ++it)
vector<state> G[maxn];
int n,k,best[maxn][maxk];
bool viz[maxn][maxk];
bool prieten[maxn];
int FND = (1<<30)-1;
void prep()
{
    freopen("lanterna.in","r",stdin);
    freopen("lanterna.out","w",stdout);
    int m,i;
    state C;
    int a,b,timp,watt;
    scanf("%d %d",&n,&k);
    for(i=1;i<=n;++i)
        scanf("%d",prieten+i);
    scanf("%d",&m);
    while(m--){
        scanf("%d %d %d %d",&a,&b,&C.timp,&C.watt);
        C.nod=a;G[b].pb(C);
        C.nod=b;G[a].pb(C);
    }

}


queue<state> Q;

int BF(int min)
{
    int ret = (1<<30)-1;
    state P,C;
    P.nod = 1,P.timp=0,P.watt=0;
    Q.push(P);
    memset(&viz[0][0],0,sizeof(viz));
    memset(&viz[1],1,sizeof(viz[1]));

    while(!Q.empty()){

        C = Q.front();Q.pop();

        if(prieten[C.nod])
            C.watt = 0;

        if(C.nod == n ){
            if( C.timp < ret)
                ret = C.timp;
            continue;
        }

        forEach(G[C.nod]){
            P.watt = C.watt + it->watt;
            if(P.watt > min)continue;
            P.nod = it->nod;
            P.timp = C.timp + it->timp;
            if(P.timp < best[P.nod][P.watt] || (P.timp <= best[P.nod][P.watt] && !viz[P.nod][P.watt])){
                best[P.nod][P.watt]=P.timp;
                viz[P.nod][P.watt]=1;
                Q.push(P);
            }
        }
    }
    return ret;
}

int bs(int val)
{
    int i,step;
    for(step=1;step<k;step<<=1);
    for(i=k;step;step>>=1){
        if(i-step >= 1 && BF(i-step) <= val)
            i -= step;
    }
    return i;
}

void solve()
{
    memset(&best[0][0],0x7f,sizeof(best));
    memset(&best[1],0,sizeof(best[1]));
    FND = BF(k);
    printf("%d %d\n",FND,bs(FND));
}

int main()
{
    prep();
    solve();
    return 0;
}
