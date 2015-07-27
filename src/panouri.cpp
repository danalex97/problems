#include <fstream>
using namespace std;
ifstream in("order.in");
ofstream out("order.out");
int n;
int logN;
int poz;
int A[1<<17];

void update(int nod,int &seek,int lo,int hi,int val)
{
    if(lo == hi)
    {
        A[nod] = val;
        return ;
    }
    int mid = (lo+hi)>>1;
    if(seek <= mid)
        update(nod<<1,seek,lo,mid,val);
    else
        update((nod<<1)|1,seek,mid+1,hi,val);
    A[nod] = A[nod<<1] + A[(nod<<1)|1];
}

int query(int nod,const int &seek,int lo,int hi)
{
    if(lo == hi)
        return lo;
    int mid = (lo+hi)>>1;
    if(seek <= A[nod<<1])
        return query(nod<<1,seek,lo,mid);
    return query((nod<<1)|1,seek - A[nod<<1],mid+1,hi);
}

int main()
{
    int i,x=1,show;
    in >> n;
    for(logN = 1 ; logN < n ; logN <<= 1);
    for(i=1;i<=n;++i)
        update(1,i,1,n,1);
    for(i= 1 ; i <= n ; ++ i)
    {
        x = (x+i) % A[1];
        if(!x)
            x = A[1];
        show = query(1,x--,1,n);
        out << show << " ";
        update(1,show,1,n,0);
    }
    return 0;
}
