#include <fstream>
#include <tr1/unordered_map>
using namespace std;
int n,S;
int v[1050];
tr1::unordered_map <int,int> sum_hash;
int main()
{
    ifstream in("oite.in");
    ofstream out("oite.out");
    int i,j,s_cr;
    int show = 0;
    in >> n >> S;
    for(i=1;i<=n;++i)
        in >> v[i];
    for(i = 1 ; i <= n ; ++ i)
    {
        for(j = i + 1 ; j <= n ; ++ j)
        {
            s_cr = S - v[i] - v[j];
            if(s_cr < 0)
                continue;
            if(sum_hash.count(s_cr))
            {
                show += sum_hash[s_cr];
            }
        }
        for(j = 1 ; j < i ; ++ j)
        {
            ++sum_hash[v[i]+v[j]];
        }
    }
    out << show;
    return 0;
}
