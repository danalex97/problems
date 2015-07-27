#include <cstdio>
using namespace std;
#define maxn 505
int RMQ[9][maxn][maxn];
int LG[maxn];
const inline int max(const int &a,const int &b){return a > b ? a : b;}
const inline int max(const int&a,const int &b,const int &c,const int &d){return max(max(max(a,b),c),d) ;}

int main()
{
    freopen("plantatie.in","r",stdin);
    freopen("plantatie.out","w",stdout);
    int i,j,k,n,m;
    int x,y,lat;
    int a,b,c,d,len;
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;++i){
        for(j=1;j<=n;++j){
            scanf("%d",&RMQ[0][i][j]);
        }
    }for(i=2;i<=n;++i){
        LG[i] = LG[i/2]+1;
    }for(k=1;(1<<k)<=n;++k){

        for(i=1;i + (1 << k)-1<=n;++i){
            for(j=1;j + (1 << k)-1<=n;++j){
                len = 1 << (k-1);

                a = RMQ[k-1][i][j];
                b = RMQ[k-1][i+len][j];
                c = RMQ[k-1][i][j+len];
                d = RMQ[k-1][i+len][j+len];

                RMQ[k][i][j] = max(a,b,c,d);
            }
        }
    }while(m--){
        scanf("%d %d %d",&x,&y,&lat);
        k = LG[lat],len = 1 << k;
        len = lat - len;

        a = RMQ[k][x][y];
        b = RMQ[k][x+len][y];
        c = RMQ[k][x][y+len];
        d = RMQ[k][x+len][y+len];

        printf("%d\n",max(a,b,c,d));
    }
    return 0;
}
