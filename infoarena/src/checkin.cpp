#include <cstdio>
#include <utility>
using namespace std;

int n,m;
int lv;
pair<int,int> st[15005];
inline int min(const int &a,const int &b){return a < b ? a : b;}
inline int max(const int &a,const int &b){return a > b ? a : b;}

bool add(const pair<int,int> &P){
    if(lv == 0 || P.first != st[lv].second+1 && P.second+1 != st[lv].first){
        ++lv;
        st[lv]=P;
        return 0;
    }else{
        st[lv].first = min(st[lv].first,P.first);
        st[lv].second = max(st[lv].second,P.second);
        return 1;
    }
}

bool good(){
    int i=1;pair<int,int> P;
    lv=0;
    while(i <= n){
        scanf("%d",&P.first);P.second = P.first;
        while(add(P))P = st[lv--];
        ++i;
    }
    return lv == 1;
}
int main()
{
    freopen("reactii.in","r",stdin);
    freopen("reactii.out","w",stdout);
    scanf("%d %d",&n,&m);
    while(m--)printf("%d\n",good());
}
