#include <cstdio>
#include <cstring>

using namespace std;
#define cint const int&


const int maxn = 210;
int n,p;
const int baza = 10;
char line[1000];

struct big_num{
    short cif[500];
    void reset(){
        memset(cif,0,sizeof(cif));
    }
    void operator = (int x){
        big_num();
        while(x){
            cif[++cif[0]] = x % baza;
            x /= baza;
        }
    }
    void operator += (const big_num &c){
        int i,t;
        for(i = 1 , t = 0 ; i <= cif[0] || i <= c.cif[0] || t ; ++i , t/= baza){
            cif[i] = (t += cif[i] + c.cif[i]) % baza;
        }
        cif[0] = i-1;
    }
    void read(){
        scanf("%s\n",line);
        char *p = line;
        for(; *p ; ++ p);
        --p;
        cif[0] = p - line + 1;
        for(;p >= line; -- p)
            cif[cif[0]-(p-line)] = *p - 48;
    }
    void show(){
        for(int i = cif[0] ; i > 0 ; -- i)
            printf("%d",cif[i]);
        printf("\n");
    }
    bool operator > (const big_num &x){
        if(cif[0] > x.cif[0])
            return 1;
        else if(cif[0] < x.cif[0])
            return 0;
        for(int i = cif[0] ; i > 0 ; -- i){
            if(cif[i] > x.cif[i])
                return 1;
            else if(x.cif[i] > cif[i])
                return 0;
        }return 0;
    }

    void operator -= (const big_num &x){
        int i,t;
        for(i = 1 , t = 0 ; i <= cif[0] ; ++ i){
            cif[i] -= x.cif[i] + t;
            cif[i] += (t = cif[i] < 0) * baza;
        }
        for(;cif[0] > 1 && cif[cif[0]] == 0;--cif[0]);
    }

};

big_num C[maxn][maxn];
big_num S[2][maxn];
big_num P;
void solve(){
    int i,j;
    int last = 0;
    memset(&S[0][0],0,sizeof(S[0][0]));
    for(j = n - 1 ; j > 0 ; -- j){
        C[n][j] = 1;
        S[n&1][j] += S[n&1][j+1];
        S[n&1][j] += C[n][j];
    }
    for(i=n-1;i>0;--i){
        memset(S[i&1],0,sizeof(S[i&1]));
        for(j=i-1;j>0;--j){
            C[i][j].reset();
            C[i][j] += S[~i&1][j];
            S[i&1][j] += S[i&1][j+1];
            S[i&1][j] += C[i][j];
        }
    }

    for(i=1;i<=n;++i){

        for(j = last ; j < i-1 && P > C[i][j] ; ++ j)
            P -= C[i][j];

        printf("%d ",j);

        last = j;
    }
    printf("\n");
}

int main()
{
    freopen("arbsort.in","r",stdin);
    freopen("arbsort.out","w",stdout);

    scanf("%d\n",&n);
    P.read();
    solve();
    return 0;
}
