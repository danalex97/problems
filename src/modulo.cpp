#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

ifstream in("tablite.in");
ofstream out("tablite.out");

const int mod = 60106;
const int maxn = 1001;

short unsigned best[2][maxn][10];


vector <short> good[10];
short len[10];
int main()
{
    short n,s,i,j,k,l;
    int show = 0;
    in >> n >> s;
    for( i = 1 ; i <= 9 ; ++ i )
        best[1][i][i] = 1;

    for( i = 0 ; i <= 9 ; ++ i )
    {
        good[ i ].push_back(0);
        good[ i ].push_back(1);
        for ( j = 2 ; j <= 9 ; ++ j )
            if(i <= 1 || ( i % j && j % i ))
            {
                good[ i ].push_back(j);
            }
    }


    for( i = 2 ; i <= n ; ++ i)
    {
        memset(&best[i%2][0][0],0,sizeof(best[i%2]));
        for ( j = 1 ; j <= s ; ++ j )
        {
            for ( k = 0 ; k <= 9 && k <= j ; ++ k)
                if( best [ ( i + 1 ) % 2 ][ j ][ k ])
                    for( l = good[ k ].size() - 1 ; l >= 0 ; -- l )
                    {
                        if( j + good[k][l] <= s)
                            best [ i % 2 ][ j + good[ k ][ l ] ][good[k][l]]  = ( best [ i % 2 ][ j + good[k][l]][good[k][l]] + best [ ( i + 1  ) % 2 ][ j ][ k ] ) % mod;
                    }
        }
    }

    for( k = 0 ; k <= 9 ; ++ k)
       show = (show + best [ (i + 1) % 2  ][s][k]) % mod;


    out << show;
    return 0;
}
