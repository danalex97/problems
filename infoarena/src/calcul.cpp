#include <cmath>
#include <fstream>
#include <cstring>
#include <queue>
#include <set>

using namespace std;

typedef long double ldouble;

const int MAX_N = 1500 + 100;
const int MAX_M = 2500 + 100;
const int MOD = 104659;
const ldouble e = 2.7182818284590452353602874713527;
const ldouble EPS = 1e-9;

const long long INF = (1LL << 62) - 1;

struct edge {
    int to;
    int next;
    ldouble c;
};

edge E[MAX_M * 2];
int at;

int fst[MAX_N];

void addEdge(const int from, const int to, const ldouble c) {
    E[at].to = to;
    E[at].c = c;
    E[at].next = fst[from];
    fst[from] = at;
    at++;
}

ldouble best[MAX_N];
long long ans[MAX_N];
int n, m;

struct comp {
    bool operator() (const int &a, const int &b) {
        return best[a] - best[b] < -EPS;
    }
};

set<int, comp> Q;

void insert(const int node) {
    Q.erase(node);
    Q.insert(node);
}

void BFS() {
    for(int i = 1 ; i <= n ; ++i)
        best[i] = INF;

    ans[1] = 1;
    best[1] = 0;
    Q.insert(1);

    while(!Q.empty()) {
        const int node = *Q.begin();
        Q.erase(Q.begin());
        for(int i = fst[node] ; i != -1 ; i = E[i].next) {
            const int son = E[i].to;
            const ldouble c = E[i].c;


            if(abs(best[node] + c - best[son]) <= EPS) {
                ans[son] = (ans[son] + ans[node]) % MOD;
            } else if(best[node] + c - best[son] < -EPS) {
                best[son] = best[node] + c;
                ans[son] = ans[node];
                insert(son);
            }
        }
    }

}


int main() {
    ifstream in("dmin.in");
    in >> n >> m;
    for(int i = 1 ; i <= n ; ++i)
        fst[i] = -1;

    int a, b;
    long long cc;
    ldouble c;

    for(int i = 1 ; i <= m ; ++i) {
        in >> a >> b >> cc;
        c = log(cc);

        addEdge(a, b, c);
        addEdge(b, a, c);
    }
    in.close();

    BFS();
    ofstream out("dmin.out");
    for(int i = 2 ; i <= n ; ++i) {
        out << ans[i] << " ";
    }
    out << "\n";
}
