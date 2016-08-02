#include <fstream>
#include <algorithm>
using namespace std;

ifstream in("economie.in");
ofstream out("economie.out");
short unsigned v[1001];
short unsigned show[1001];
short unsigned found = 0;
bool reach[50005];
int n;
int main()
{
    in >> n;
    int i;
    for(i =  1 ; i <= n ; ++ i )
    {
        in >> v [ i ];
        if(v[ i ] == 1 )
        {
            out << "1\n1\n";
            return 0;
        }
    }
    sort(v+1,v+n+1);
    reach[0] = 1;
    int j;
    for(i = 1 ; i <= n ; ++ i)
    {
        if(!reach[v[i]])
        {
            reach[v[i]] = 1;
            show[++found] = v[i];
        }
        for(j = 0 ; j + v[i] <= v[n] ; ++ j)
        {
            if(reach[j])
                reach[v[i]+j] = 1;
        }
    }
    out << found << "\n";
    for(i = 1 ; i <= found ; ++ i)
        out << show[i] << "\n";
    return 0;
}
