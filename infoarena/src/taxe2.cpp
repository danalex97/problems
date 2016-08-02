#include <iostream>
#include <stdio.h>
#include <deque>

using namespace std;

int n,a[100][100],cost[100][100];
bool been[100][100] = {0};
#define max(a,b) (((a) > (b)) ? (a) : (b))
struct cord
{
    int y,x;
};

deque<cord> c;

void p_find()
{
    cord act;
    int acost;
    while(c.size()>0)
    {
        act = c.front();
        c.pop_front();
        acost = cost[act.y][act.x];
        if(act.x-1 >= 0)
        {
            if(been[act.y][act.x-1] == 0)
            {
                been[act.y][act.x-1] = 1;
                cost[act.y][act.x-1] = acost + a[act.y][act.x-1];
                c.push_back((cord){act.y,act.x-1});
            }
            else if(acost+a[act.y][act.x-1] < cost[act.y][act.x-1])
            {
                cost[act.y][act.x-1] = acost + a[act.y][act.x-1];
                c.push_back((cord){act.y,act.x-1});
            }
        }
        if(act.x+1 < n)
        {
            if(been[act.y][act.x+1] == 0)
            {
                been[act.y][act.x+1] = 1;
                cost[act.y][act.x+1] = acost + a[act.y][act.x+1];
                c.push_back((cord){act.y,act.x+1});
            }
            else if(acost + a[act.y][act.x+1] < cost[act.y][act.x+1])
            {
                cost[act.y][act.x+1] = acost + a[act.y][act.x+1];
                c.push_back((cord){act.y,act.x+1});
            }
        }
        if(act.y-1 >= 0)
        {
            if(been[act.y-1][act.x] == 0)
            {
                been[act.y-1][act.x] = 1;
                cost[act.y-1][act.x] = acost+a[act.y-1][act.x];
                c.push_back((cord){act.y-1,act.x});
            }
            else if(acost + a[act.y-1][act.x] < cost[act.y-1][act.x])
            {
                cost[act.y-1][act.x] = acost+a[act.y-1][act.x];
                c.push_back((cord){act.y-1,act.x});
            }
        }
        if(act.y+1 < n)
        {
            if(been[act.y+1][act.x] == 0)
            {
                been[act.y+1][act.x] = 1;
                cost[act.y+1][act.x] = acost+a[act.y+1][act.x];
                c.push_back((cord){act.y+1,act.x});
            }
            else if(acost + a[act.y+1][act.x] < cost[act.y+1][act.x])
            {
                cost[act.y+1][act.x] = acost+a[act.y+1][act.x];
                c.push_back((cord){act.y+1,act.x});
            }
        }
    }
}

int main()
{
    int s,i,j;
    FILE * in , * out;
    in = fopen("taxe2.in","r");
    out = fopen("taxe2.out","w");
    fscanf(in," %d %d ",&s,&n);
    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
        fscanf(in," %d ",&a[i][j]);
    cost[0][0] = a[0][0];
    c.push_back((cord){0,0});
    p_find();
    fprintf(out,"%d",max(s-cost[n-1][n-1],-1));
    return 0;
}
