#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
int n,mx;
int v[5010];
short best[100500];
#define cint const int&
inline int max(cint a,cint b){return a > b ? a : b;}
void read(){
    scanf("%d",&n);
    mx = 0;
    for(int i = 1 ; i <= n ; ++ i){
        scanf("%d",v+i);
        mx = max(mx,v[i]);
    }
}

int parc(cint R){
    memset(best,0,sizeof(best));
    int q,ret=0;

    for(int i = 1 ; i <= n ; ++ i){
        best[v[i]] = max(best[v[i]],1);
        if(v[i] % R ==0){
            q = v[i]/R;
            best[v[i]] = max(best[v[i]],best[q]+1);
        }ret = max(ret,best[v[i]]);
    }return ret;
}

void mark(int x){
    for(int q = x+x; q <= mx; q += x)
        best[q]=1;
}

int ciur(){
    memset(best,0,sizeof(best));
    for(int i = 1 ; i <= n ; ++ i){
        if(best[v[i]])return 2;
        mark(v[i]);
    }return 1;
}

int solve(){
    int i,ret=1,x;
    int root = sqrt(mx);
    for(i=2;i<=root;++i){
        x = parc(i);

        ret = max(x,ret);
    }if(ret >= 2)return ret;
    else return ciur();
}

int main()
{
    freopen("subgeom.in","r",stdin);
    freopen("subgeom.out","w",stdout);

    int T;
    scanf("%d",&T);
    while(T--){
        read();
        printf("%d\n",solve());
    }
    return 0;
}
