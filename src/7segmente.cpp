#include <fstream>
#include <iostream>
using namespace std;

int cost[10];


int v[20];
int afis[20];
void best_fit(int left,int i,int cif,bool tight)
{
    static int k;
        for(k = 1 ; k <= v[i] || (!tight && k <= 9); ++ k)
        {
            if((left - cost[k]) >= (cif - i)*2)
            {
                afis[i] = k;
            }
        }
}

int main()
{
    ifstream in("7segmente.in");
    ofstream out("7segmente.out");
    cost[1] = 2;
    cost[2] = 5;
    cost[3] = 5;
    cost[4] = 4;
    cost[5] = 5;
    cost[6] = 6;
    cost[7] = 3;
    cost[8] = 7;
    cost[9] = 6;
    unsigned long long int n,p,c;
    in >> n >> p;
    c = n;
    int show = 0;
    int cif = 0;
    int i;
    while(c)
    {
        show += cost[c % 10];
        c /= 10;
        ++cif;
    }
    out << show << " ";
    c = n;
    show = cif;
    while(c)
    {
        v[cif--] = c % 10;
        c /= 10;
    }
    cif = show;
    int left = p;
    bool tight = 1;
    for(i = 1 ; i <= cif ; ++ i)
    {
        best_fit(left,i,cif,tight);
        if(afis[i] < v[i])
            tight = 0;
        if(!afis[i])
        {
            --cif;
            --i;
            continue;
        }
        left -= cost[afis[i]];
    }
    for(i = 1 ; i <= cif ; ++ i)
        out << afis[i];
    return 0;
}
