#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

struct punct
{
    int x,y;
}v[1002];

struct arc
{
    int x,y;
    double c;
}last[1002],now[1002*2];

int root[1002];

const int tata(int nod)
{
    int aux = nod,y;
    for(nod = root[nod];root[nod] != nod;nod = root[nod]);
    while(aux != nod)
    {
        y = root[aux];
        root[aux] = nod;
        aux = y;
    }
    return nod;
}

bool unite(int a,int b)
{
    a = tata(a);
    b = tata(b);
    if(a == b)
        return 0;
    root[a] = b;
    return 1;
}

inline const double dist(const punct &a,const punct &b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

struct comp
{
    inline bool operator () (const arc &a,const arc &b)
    {
        return a.c < b.c;
    }
};

void query(int care,double & show)
{

    int i;
    show = 0;
    memcpy(now,last,sizeof(now));
    root[care]=care;
    for(i=1;i<care;++i)
    {
        root[i] = i;
        now[i+care-2].x = i;
        now[i+care-2].y = care;
        now[i+care-2].c = dist(v[care],v[i]);
    }
    memset(last,0,sizeof(last));
    sort(now+1,now+2*care-1,comp());
    int cr = 0;
    for(i=1;i<2*care;++i)
    {
        if(unite(now[i].x,now[i].y))
        {
            last[++cr] = now[i];
            show += now[i].c;
        }
    }
}

int main()
{
    freopen("desen.in","r",stdin);
    freopen("desen.out","w",stdout);

    int n,i;
    double show;
    scanf("%d",&n);
    for(i=1;i<=n;++i)
    {
        scanf("%d %d",&v[i].x,&v[i].y);
        query(i,show);
        printf("%.6lf\n",show);
    }
}

