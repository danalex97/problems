#include <fstream>
#include <iostream>
using namespace std;
ifstream in("triunghi3.in");
ofstream out("triunghi3.out");
#define maxn 1005
#define cint const int&
int n;
int cr;
int mat[maxn][maxn];
int best[maxn][maxn];
bool viz[maxn][maxn];
int sum_col[maxn][maxn];
int sum_diag[maxn][maxn];
inline int min(cint a,cint b){return a < b ? a : b;}
void read()
{
    int i,j;
    in >> n;
    for(i=1;i<=n;++i)
        for(j=1;j<=i;++j)
            in >> mat[i][j];

    for(j=1;j<=n;++j)
        viz[n][j]=1;


    for(i=n;i>0;--i)
        for(j=1;j<=i;++j)
        {
            sum_col[j][i] = sum_col[j][i+1] + mat[i][j];
            sum_diag[i-j+1][i] = sum_diag[i-j+1][i+1] + mat[i][j];
        }


}


int T(cint x,cint y,int len)
{
    if(viz[x][y])
        return best[x][y];
    viz[x][y]=1;
    int i,a=0,b=0;
    int dela=0,delb=0;
    --len;

    a += sum_diag[x-y+1][x];
    a -= sum_diag[x-y+1][x+len];
    a += sum_diag[x-y+2][x+1];

    b += sum_col[y][x];
    b -= sum_col[y][x+len];
    b += sum_col[y+1][x+1];


    a *= len;
    b *= len;


    dela += sum_diag[x-y+1][x];
    dela *= 2;
    dela -= mat[x][y] + sum_diag[x-y+1][x+len];

    delb += sum_col[y][x];
    delb *= 2;
    delb -= mat[x][y] + sum_col[y][x+len];


    a += dela;
    b += delb;
    a += T(x+1,y,len);
    b += T(x+1,y+1,len);

    best[x][y] = min(a,b);

    return best[x][y];

}

int main()
{
    read();
    out << T(1,1,n);
}
