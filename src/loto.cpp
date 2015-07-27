#include <fstream>
using namespace std;

ifstream in("munte.in");
ofstream out("munte.out");

long long dp[102][52][52][2];

int v[52];
int n,d,x;
int main()
{
    int i,j,k,c;
    in >> n >> d >> x;
    for(i=1;i<=x;++i)
        in >> v[i];
    dp[1][1][v[1] == 1][n == 1]=1;
    for(i=1;i<=d;++i)
        for(j=1;j<=n && j <= i;++j)
            for(k=0;k<=x;++k)
                for(c = 0; c <= 1 ; ++ c)
                {
                    dp[i+1][j][k + (k + 1 <= x ? v[k+1] == j : 0)][j == n || c] += dp[i][j][k][c];
                    dp[i+1][j+1][k + (k + 1 <= x ? v[k+1] == j + 1 : 0)][j+1 == n || c] += dp[i][j][k][c];
                    dp[i+1][j-1][k + (k + 1 <= x ? v[k+1] == j - 1 : 0)][c] += dp[i][j][k][c];
                }
    out << dp[d][0][x][1];
    return 0;
}
