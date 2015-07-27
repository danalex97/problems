#include <cstdio>
#include <algorithm>
#include <cstring>
#include <deque>
#include <cmath>

using namespace std;

typedef long long LL;

const int MAX_N = 100100;
const LL INF = 1LL << 60;

int n,k;

LL P,S[MAX_N];
LL best[2][MAX_N];

deque<int> D;

int main()
{
    freopen("secvbest.in", "r", stdin);
    freopen("secvbest.out", "w", stdout);

    scanf("%d%d%lld",&n,&k,&P);
    int i,j;
    int split;
    LL before;

    for(i = 1 ; i <= n ; ++ i){
        scanf("%lld",S+i);
        S[i] += S[i-1];
    }

    memset(best,0x7f,sizeof(best));
    best[0][0] = 0;
    for(j = 1 ; j <= k ; ++ j){

        split = 0;

        D.clear();
        D.push_back(0);

        before = INF;

        for(i = 1 ; i <= n ; ++ i){

            while(split < i && S[split] <= S[i] - P){

                if(!D.empty() && D.front() == split)
                    D.pop_front();

                if(best[~j & 1][split] - S[split] < before)
                    before = best[~j & 1][split] - S[split];

                ++split;

            }

            best[j & 1][i] = before + S[i] - P;

            if(!D.empty()){

                LL now = D.front();

                now = best[~j & 1][now] + S[now] + P - S[i];

                if(now < best[j & 1][i])
                    best[j & 1][i] = now;
            }

            if(split < i){

                LL now = best[~j & 1][i] + S[i];

                while(!D.empty() && now <= best[~j & 1][D.back()] + S[D.back()])
                    D.pop_back();

                D.push_back(i);
            }
        }

        best[0][0] = INF;
        printf("%lld ",best[j & 1][n]);
    }
    return 0;
}
