#include <cstdio>
#include <vector>
#include <cstring>

#define forEach(G) for(__typeof(G.begin()) it = G.begin() ; it != G.end() ; ++ it)

using namespace std;

const int MAX_N = 51*51;

vector<int> G[MAX_N];

int right[MAX_N][MAX_N];
int down[MAX_N][MAX_N];

char mat[MAX_N][MAX_N];

int A,B;
int n,m;

int mate[MAX_N];
int other[MAX_N];

bool tried[MAX_N];

bool pair_up(const int &nod)
{
    if(tried[nod])
        return false;

    tried[nod] = 1;

    forEach(G[nod]){
        if(other[*it] == 0){
            mate[nod] = *it;
            other[*it] = nod;
            return true;
        }
    }

    forEach(G[nod]){
        if(pair_up(other[*it])){
            mate[nod] = *it;
            other[*it] = nod;
            return true;
        }
    }

    return false;
}

void matching()
{
    int i;
    bool changed = 1;
    while(changed){
        changed = 0;
        memset(tried,0,sizeof(tried));
        for(i = 1 ; i <= A ; ++ i)
            if(!mate[i] && pair_up(i))
                changed |= 1;
    }
}
int main()
{
    freopen("s013.in", "r", stdin);
    freopen("s013.out", "w", stdout);

    scanf("%d%d",&n,&m);

    int i,j;

    for(i = 1 ; i <= n ; ++ i)
        scanf("%s\n",mat[i] + 1);

    int now = 0;
    for(i = 1 ; i <= n ; ++ i)for(j = 1 ; j <= m ; ++ j){
        if(mat[i][j] == '*'){
            if(mat[i][j-1] != '*')
                ++now;
            right[i][j] = now;
        }
    }
    A = now;
    now = 0;

    for(j = 1 ; j <= m ; ++ j)for(i = 1 ; i <= n ; ++ i){
        if(mat[i][j] == '*'){
            if(mat[i-1][j] != '*')
                ++now;
            down[i][j] = now;
        }
    }
    B = now;
    now = 0;


    for(i = 1 ; i <= n ; ++ i)for(j = 1 ; j <= m ; ++ j)
        if(mat[i][j] == '*')
            G[right[i][j]].push_back(down[i][j]);

    matching();

    int ans = 0;
    for(i = 1 ; i <= A ; ++ i)
        ans += mate[i] > 0;

    printf("%d\n",ans);
    return 0;
}
