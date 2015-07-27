#include <fstream>
#include <algorithm>
using namespace std;
int n;
char s[550];
int dp[550][550];
int cost[55][55];
void read()
{
    ifstream in("redu.in");
    in >> n;
    in >> s+1;
    int i,j;
    for(i=0;i<='z'-'a';++i)
        for(j=0;j<='z'-'a';++j)
            in >> cost[i][j];
}
void solve()
{
    int len,i,j,k;
    int x,y;
    for(i=1;i<n;++i)
        dp[i][i+1] = cost[s[i]-'a'][s[i+1]-'a'];
    for(len = 4 ; len <= n ; len+=2)
    {
        for(i = 1 ; i <= n - len + 1; ++ i)
        {
            j = i + len - 1;
            dp[i][j] = 1 << 29;
            for(k = i+1;k<=j;++k)
            {
                if(k-1 < i-1)
                    x = 0;
                else if(((k-1)-(i+1)+1) % 2 == 1)
                    x = 1 << 29;
                else
                    x = dp[i+1][k-1];
                if(j < k+1)
                    y = 0;
                else if( (j - (k+1) + 1 % 2) == 1)
                    y = 1 << 29;
                else
                    y = dp[k+1][j];
                dp[i][j] = min(dp[i][j],x+y+cost[s[i]-'a'][s[k]-'a']);
            }
        }
    }
}
void print()
{
    ofstream out("redu.out");
    out << dp[1][n] << "\n";
}
int main()
{
    read();
    solve();
    print();
    return 0;
}
