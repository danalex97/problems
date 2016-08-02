#include <fstream>
#include <iostream>

using namespace std;

ifstream in("eliminare.in");
ofstream out("eliminare.out");


int n,m;

#define cint const int&
#define bun(__nod) gt(AINT[__nod*2].first,AINT[__nod*2+1].first)
#define lsb(x) (x&(-x))
#define sum(nod) AINT[nod].second = AINT[2*nod].second + AINT[2*nod+1].second;
#define BS(val) register int nod=1,st=1,dr=n;while(st < dr){nod *= 2;if(AINT[nod].second >= val)dr = (st+dr)/2;else val -= AINT[nod++].second,st = (st+dr)/2+1;}

const int maxn = 1000100;
int v[maxn];
int logN;
pair<int,int> AINT[1<<21];
int lo,hi,poz;



inline int gt(cint v1,cint v2){
    if(v[v1] >= v[v2])
        return v1;
    else
        return v2;
}

void build(cint nod,cint st,cint dr){
    if(st == dr){
        AINT[nod].first = st;
        AINT[nod].second = 1;
    }else{
        register int mid = (st+dr)/2;
        build(2*nod,st,mid);
        build(2*nod+1,mid+1,dr);
        AINT[nod].first = bun(nod);
        sum(nod);
    }
}

void update(cint nod,cint st,cint dr){
    if(st == dr){
        AINT[nod].first = 0;
        AINT[nod].second = 0;
        v[st] = 0;
    }else{
        register int mid = (st+dr)/2;
        if(poz <= mid)
            update(2*nod,st,mid);
        else
            update(2*nod+1,mid+1,dr);
        AINT[nod].first = bun(nod);
        sum(nod);
    }
}

int query(cint nod,cint st,cint dr){
    if(lo <= st && dr <= hi){
        return AINT[nod].first;
    }else{
        register int mid = (st+dr)/2;
        int left = 0,right = 0;
        if(lo <= mid)
            left = query(2*nod,st,mid);
        if(mid < hi)
            right = query(2*nod+1,mid+1,dr);
        return gt(left,right);
    }
}

inline int search(int val){
    BS(val)
    return st;
}

inline void solve(){
    lo = search(lo);
    hi = search(hi);
    poz = query(1,1,n);
    update(1,1,n);
}


int main()
{
    in >> n >> m;
    v[0] = -(1<<30);
    for(logN=1;logN<n;logN<<=1);
    for(register int i = 1 ; i <= n ; ++ i)
        in >> v[i];
    build(1,1,n);
    while(m--){
        in >> lo >> hi;
        solve();
    }
    for(register int i = 1 ; i <= n ; ++ i)
        if(v[i])out << v[i] << "\n";
    return 0;
}
