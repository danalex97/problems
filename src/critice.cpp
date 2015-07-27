#include <fstream>
#include <set>
#include <vector>

using namespace std;

const int MAX_N = 5010;

int v[MAX_N],
    n;

int idx[MAX_N];

ifstream in("secv.in");
ofstream out("secv.out");

set<int> T;

vector<int> norm;

int bsearch(const int val){
    int i,step;

    for(step = 1 ; step < norm.size() ; step <<= 1);

    for(i = 0 ; step ; step >>= 1)
        if(i + step < norm.size() && norm[i + step] <= val)
            i += step;

    return i + 1;
}

int best[MAX_N];

int main(){
    in >> n;

    for(int i = 1 ; i <= n ; ++i){
        in >> v[i];
        T.insert(v[i]);
        best[i] = -1;
    }

    norm = vector<int>(T.begin(), T.end());

    T.clear();

    for(int i = 1 ; i <= n ; ++i)
        idx[i] = bsearch(v[i]);

    int i = 1;

    while(i <= n && v[i] != norm[0])
        ++i;

    best[1] = i;

    int ans = -1;

    for( ; i <= n ; ++i){

        if(idx[i] == 1)
            best[1] = i;

        else
            best[idx[i]] = best[idx[i]-1];

        if(idx[i] == norm.size() && best[idx[i]] != -1){
            if(ans == -1)
                ans = i - best[idx[i]] + 1;
            else if(i - best[idx[i]] + 1 < ans)
                ans = i - best[idx[i]] + 1;
        }

    }
    out << ans << "\n";
}
