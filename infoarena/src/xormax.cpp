#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int MAX_N = 1100;
const int MAX_M = MAX_N * 100;
typedef pair<int,int> point;

point v[MAX_M];
bool u[MAX_M];
int line[MAX_N];
int col[MAX_N];
int n,m;

const int R = 1;
const int A = 0;

vector<int> red,blu;
queue<int> Q;
void solve(int now)
{
    int type = R,x;

    while(!u[now]){
        u[now] = 1;
        Q.push(now);
        if(type == R)
            now = col[v[now].second];
        else
            now = line[v[now].first];
        type ^= 1;
    }
    type = R;

    while(Q.front() != now){
        Q.pop();
        type ^= 1;
    }

    while(!Q.empty()){
        x = Q.front();
        Q.pop();
        if(type == R)
            red.push_back(x);
        else blu.push_back(x);
        type ^= 1;
    }

    printf("%d\n",red.size());

    int i;
    for(i = 0 ; i < red.size() ; ++ i)
        printf("%d %d ",v[red[i]].first,v[red[i]].second);

    printf("\n");
    for(i = 0 ; i < blu.size() ; ++ i)
        printf("%d %d ",v[blu[i]].first,v[blu[i]].second);

    printf("\n");

}

int main()
{
    freopen("zaharel.in","r",stdin);
    freopen("zaharel.out","w",stdout);

    scanf("%d %d",&n,&m);

    int i,start = 0;
    int x,y;
    char C;

    for(i = 1 ; i <= m ; ++ i){
        scanf("%d %d %c",&x,&y,&C);
        v[i].first = x;
        v[i].second = y;
        if(C == 'R'){
            line[x] = i;
            start = i;
        }
        else col[y] = i;
    }

    solve(start);

    return 0;
}
