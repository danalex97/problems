#include <cstdio>
#include <queue>
#include <cmath>
#include <vector>
using namespace std;
#define maxn 60
#define cd const int&

int mat[maxn][maxn];
double best[maxn][maxn];
bool viz[maxn][maxn];
int n,m;
double Lmax;
const int dx[] = {0,1,0,-1};
const int dy[] = {1,0,-1,0};
int xi,yi,xf,yf;
struct state{
    int x,y;
    double efort,dist;
};

struct comp
{
    public:
    bool operator() (const state &a,const state &b)
    {
        if(a.efort == b.efort)
            return a.dist > b.dist;
        return a.efort > b.efort;
    }
};


priority_queue<state,vector<state>,comp> Q;

double dist(cd a,cd b)
{
    double ret = b-a;
    ret = (ret*ret)+1;
    return sqrt(ret);
}

double eft(cd a,cd b)
{
    if(a==b)
        return 1;
    if(a > b)
        return 0.5 * eft(b,a);
    double d= dist(a,b);
    d *= (b-a);
    return d;
}

state dij()
{
    state C;
    state Add;
    int i,x,y;
    while(!Q.empty()){
        C = Q.top();
        Q.pop();
        if(C.x == xf && C.y == yf)
            return C;


        for(i=0;i<4;++i){

            x = C.x + dx[i];
            y = C.y + dy[i];

            if(x >= 1 && x <= n && y >= 1 && y <= m){
                Add.x = x;
                Add.y = y;
                Add.dist = C.dist + dist(mat[C.x][C.y],mat[x][y]);
                Add.efort = C.efort + eft(mat[C.x][C.y],mat[x][y]);
                if((Add.efort < best[x][y] || !viz[x][y])){
                    Q.push(Add);
                    viz[x][y]=1;
                    best[x][y] = Add.efort;
                }
            }
        }
    }

}

int main()
{
    freopen("excursie.in","r",stdin);
    freopen("excursie.out","w",stdout);

    scanf("%d %d %lf\n",&n,&m,&Lmax);

    int i,j;
    for(i=1;i<=n;++i)
        for(j=1;j<=m;++j)
            scanf("%d",&mat[i][j]);

    scanf("%d %d",&xi,&yi);
    scanf("%d %d",&xf,&yf);

    state C;
    C.x = xi;C.y = yi;
    viz[xi][yi]=1;


    C.dist = C.efort = 0.0;
    Q.push(C);

    C = dij();

    printf("%lf %lf\n",C.efort,C.dist <= Lmax ? C.dist : -1);

    return 0;
}
