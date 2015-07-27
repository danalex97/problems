#include <fstream>
#include <iostream>

using namespace std;
const int maxn = 100001;

int v[maxn];
int cab[365];
int ord[365];

void dec(int * n , const int * much)
{
    for(int i = 1 ; i <= *n ; ++ i)
    {
        cab[ i ] -= *much;
    }
}

int main()
{
    ifstream in("roata.in");
    ofstream out("roata.out");
    int n,p,i,j;
    long long S = 0;
    in >> n >> p;
    for(i = 1 ; i <= p ; ++ i)
    {
        in >> v[i];
        S += v[i];
    }
    out << S << "\n";

    int c_min,p_min;
    c_min = 1 << 30;

    for(i = 1 ; i <= p && i <= n ; ++ i)
    {
        cab[ i ] = v[ i ];
        ord[ i ] = i;
        if(v[ i ] < c_min)
        {
            c_min = v[ i ];
            p_min = i;
        }
    }
    out << ord[ p_min ] << " ";
    cab[p_min] = -1;
    dec(&n,&c_min);
    if(i <= p)
    {
        cab[p_min] = v[i];
        ord[p_min] = i;
        ++i;
    }

    for( ; i <= p ; ++ i)
    {
        c_min = 1 << 30;
        for(j = 1 ; j <= n ; ++ j)
        {
            if(cab[j] < c_min)
            {
                c_min = cab[ j ];
                p_min = j;
            }
        }
        out << ord[p_min] << " ";
        dec(&n,&c_min);
        cab[p_min] = v[i];
        ord[p_min] = i;
    }

    for(i = 1 ; i <= n && i <= p-1 ; ++ i)
    {
        c_min = 1 << 30;
        for(j = 1 ; j <= n ; ++ j)
        {
            if(cab[j] < c_min && cab[j] >= 0)
            {
                c_min = cab[j];
                p_min = j;
            }
        }
        out << ord[p_min] << " ";
        cab[p_min] = -1;
        dec(&n,&c_min);
    }
    out << "\n" << p_min << "\n";
}
