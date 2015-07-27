#include <cstdio>
#include <algorithm>
using namespace std;
#define maxn 2010
int L,P,D,C;
int n;
int G[maxn];
int best[maxn][maxn];
int S[maxn];
void prep()
{
    freopen("gaz.in","r",stdin);
    freopen("gaz.out","w",stdout);
    scanf("%d %d %d %d",&L,&P,&D,&C);
    scanf("%d",&n);
    for(int i = 1 ; i <= n ; ++ i){
        scanf("%d",G+i);
        S[i] = S[i-1] + G[i];
    }
}

void solve()
{
    int i,len,j,k;
    int cant;
    int other;
    for(i = 1 ; i <= n ; ++ i)
        best[i][i] = D * G[i] + P;
    for(len = 2 ; len <= n ; ++ len){
        for(i = 1 ; i + len - 1 <= n ; ++ i){
            j = i + len - 1;
            cant = S[j] - S[i-1];
            other = 1 << 30;
            best[i][j] = cant * D + P;
            for(k = i ; k <= j ; ++ k){
                cant -= G[k];
                best[i][j] += C * max(0,cant-L);
                if(k < j)
                    other = min(other , best[i][k] + best[k+1][j]);
            }
            best[i][j] = min(best[i][j],other);
        }
    }
}

int main()
{
    prep();
    solve();
    printf("%d\n",best[1][n]);
    return 0;
}
