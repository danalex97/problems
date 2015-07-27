#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

ifstream in("aby.in");
ofstream out("aby.out");
char win[1<<13][13][2];
bool G[2][13][13];
int n;
#define Abu 0
#define pb push_back
#define forEach(G) for( typeof(G.begin()) it = G.begin() ; it != G.end(); ++ it)
#define cint const int&
bool solve(cint nod,cint conf,const bool &who)
{
    if(win[conf][nod][who] >= 2)
        return win[conf][nod][who]-2;
    win[conf][nod][who] = 2;

    if(nod == n-1){
        win[conf][nod][who] = 3;
        return 1;
    }
    if(who == Abu){
        int x,i,y;
        x = bool(conf & (1 << nod));
        for(i=n-1;i>=0;--i){
            if(i==nod)continue;

            y = bool(conf & (1 << i));
            y ^= x;

            if(G[y][nod][i]){

                win[conf][nod][who] = solve(i,conf,who^1)+2;
                if(win[conf][nod][who] == 3)
                    return 1;
            }
        }
        return 0;
    }else{
        int i;
        for(i=0;i<n;++i){
            if(solve(nod,conf ^ (1 << i),who^1 ) == 0){
                win[conf][nod][who] = 2;
                return 0;
            }
        }
        win[conf][nod][who] = 3;
        return 1;
    }
}
int main()
{
    int T;in >> T;int x,y,m,i;
    while(T--){
        in >> n >> m;
        memset(&G[0][0][0],0,sizeof(G));
        while(m--){
            in >> x >> y;
            G[0][x][y]=1,G[1][y][x]=1;
        }
        memset(&win[0][0][0],0,sizeof(win));
        out << solve(0,0,0) << "\n";
    }
    return 0;
}
