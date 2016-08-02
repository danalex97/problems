#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_N = int(1e4) + 10;

int n;
int poz[MAX_N];
int DP[2][MAX_N];

int v[MAX_N];

int main()
{
    freopen("towerx.in", "r", stdin);
    freopen("towerx.out", "w", stdout);

    scanf("%d",&n);
    int i,j;
    DP[0][1] = DP[1][1] = 1;
    poz[1] = 1;
    for(i = 2 ; i <= n ; ++ i){
        memset(&DP[i&1][0],0,sizeof(DP[i&1]));
        DP[i&1][1] = 1;
        for(j = 2 ; j <= i ; ++ j){
            DP[i&1][j] = DP[i&1][j-1] + DP[~i&1][j-1];
            if(DP[i&1][j] > i)
                DP[i&1][j] -= i;
        }

        poz[i] = DP[i&1][i];
    }
    int now = 1;

    for(i = n ; i ; -- i){
        while(v[now])
            now = ++now > n ? now - n : now;

        for(j = 1 ; j < poz[i] ; ){
            ++now;
            if(now > n)
                now -= n;
            j += v[now] == 0;
        }
        v[now] = i;
    }

    for(i = 1 ; i <= n ; ++ i)
        printf("%d ",v[i]);
    printf("\n");

    return 0;
}
