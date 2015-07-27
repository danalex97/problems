#include <fstream>
using namespace std;
int n;
int v[5005];
int best[5005];
int hi;
int st;
int next[5005];
bool follow[5005];

ifstream in("subsir2.in");
ofstream out("subsir2.out");

void cmlsc()
{
    int i,j;
    int minimel;
    for(i = n ; i ; -- i)
    {
        best[i] = 1<<30;
        minimel = 1 << 30;
        for(j = i + 1 ; j <= n; ++ j)
            if(v[j] >= v[i] && v[j] < minimel)
            {
                follow[j] = 1;
                if(best[j] + 1 < best[i] || best[j] + 1 == best[i] && v[j] < v[next[i]])
                {
                    next[i] = j;
                    best[i] = best[j]+1;
                }
                minimel = v[j];
            }
        if(best[i] == 1<<30)
            best[i] = 1;
    }
    hi = 1 << 30;
    for(i=1;i<=n;++i)
    {
        if(!follow[i] && (best[i] < hi || best[i] == hi && v[i] < v[st]))
        {
            hi = best[i];
            st = i;
        }
    }
}

void write()
{
    out << hi << "\n";
    int x = st;
    do
    {
        out << x << " ";
        x = next[x];
    }
    while(x);
}

int main()
{
    int i;
    in >> n;
    for(i=1;i<=n;++i)
        in >> v[i];
    cmlsc();
    write();
    return 0;
}
