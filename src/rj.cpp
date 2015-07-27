#include <iostream>
#include <deque>
#include <stdio.h>
#include <fstream>
using namespace std;

#define max 200

struct cord
{
    int y,x;
};
deque<cord> r;
deque<cord> j;
int n,m;
bool a[max][max] = {0};

FILE * in , * out;
cord R,J;

int cost_R[max][max] = {0};
int cost_J[max][max] = {0};

void p_find()
{
    cost_R[R.y][R.x] = 1;
    cost_J[J.y][J.x] = 1;
    r.push_back(R);
    j.push_back(J);
    int delY,delX,cst;
    do
    {
        R = r.front();
        r.pop_front();
        cst = cost_R[R.y][R.x]+1;
        for(delY = -1;delY <= 1;++delY)
        {
            if(R.y + delY <= n && R.y + delY >= 1)
                for(delX = -1;delX <=1;++delX)
                {
                    if(R.x + delX <=m && R.x + delX >= 1 && a[R.y+delY][R.x+delX] == 0 && (cost_R[R.y + delY][R.x + delX] == 0))
                    {
                        cost_R[R.y+delY][R.x+delX] = cst;
                        r.push_back((cord){R.y+delY,R.x+delX});
                    }
                }
        }
    }
    while(r.size());
    do
    {
        J = j.front();
        j.pop_front();
        cst = cost_J[J.y][J.x]+1;
        for(delY = -1;delY <=1;++delY)
        {
            if(J.y + delY <= n && J.y + delY >= 1)
                for(delX = -1;delX <=1;++delX)
                    if(J.x + delX <= m && J.x + delX >=1 && a[J.y+delY][J.x+delX] == 0 && (cost_J[J.y+delY][J.x+delX] == 0))
                    {
                        if(cost_R[J.y+delY][J.x+delX] == cst)
                        {
                            fprintf(out,"%d %d %d",cst,J.y+delY,J.x+delX);
                            return ;
                        }
                        cost_J[J.y+delY][J.x+delX] = cst;
                        j.push_back((cord){J.y+delY,J.x+delX});
                    }
        }
    }
    while(j.size());
}

int main()
{
    int i,j;
    char c;
    in = fopen("rj.in","r");
    out = fopen("rj.out","w");
    fscanf(in," %d %d", &n , &m);
    for(i=1;i<=n;++i)
        for(j=1;j<=m;++j)
        {
            fscanf(in,"%c",&c);
            if(c == '\n')
                fscanf(in,"%c",&c);
            if(c == 'R')
            {
                R.x = j;
                R.y = i;
            }
            else if(c == 'J')
            {
                J.x = j;
                J.y = i;
            }
            else if(c == 'X')
                a[i][j] = 1;
        }
    p_find();
    return 0;
}
