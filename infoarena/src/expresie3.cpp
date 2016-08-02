#include <fstream>
#include <queue>
using namespace std;
#define maxn 1005
int mat[maxn][maxn];
bool viz[maxn][maxn];
int n,m,h;
int show;
struct cell
{
    int x,y;
};
queue<cell>q;
const int dx[] = {0,1,0,-1};
const int dy[] = {1,0,-1,0};
ifstream in("tsunami.in");
ofstream out("tsunami.out");
inline bool good(const int &x,const int &y)
{
    return x >= 1 && x <= n && y >= 1 && y <= m && !viz[x][y] && mat[x][y] < h;
}
void read()
{
    int i,j;
    in >> n >> m >> h;
    for(i=1;i<=n;++i)
        for(j=1;j<=m;++j)
        {
            in >> mat[i][j];
            if(mat[i][j] == 0)
            {
                q.push((cell){i,j});
                viz[i][j]=1;
            }
        }
}
void solve()
{
    cell c;
    int i;
    while(!q.empty())
    {
        c = q.front();
        q.pop();
        for(i=0;i<4;++i)
        {
            if(good(c.x + dx[i] , c.y+dy[i]))
            {
                q.push((cell){c.x+dx[i],c.y+dy[i]});
                viz[c.x+dx[i]][c.y+dy[i]]=1;
                ++show;
            }
        }
    }
}
int main()
{
    read();
    solve();
    out << show << "\n";
    return 0;
}
