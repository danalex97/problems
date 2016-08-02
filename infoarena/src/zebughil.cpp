#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

int n, g;

int v[18];
ifstream in("zebughil.in");
ofstream out("zebughil.out");

char DP[1 << 18][18];

long long S[1 << 18];

struct edge{
    int to;
    int next;
};

edge E[(1 << 18) * 18];
int et;

int fst[18];


bool comp(const int &a, const int &b) {
    return S[a] > S[b];
}

void addEdge(const int node, const int conf) {
    E[et].to = conf;
    E[et].next = fst[node];
    fst[node] = et;
    et++;
}


bool f(int conf, int rem) {

    if(rem == 0)
        return (!bool(conf));

    if(DP[conf][rem] != -1)
        return DP[conf][rem];

    DP[conf][rem] = 0;

    if(S[conf] <= g)
        return DP[conf][rem] = 1;

    int inc = 0;
    while(!(conf & (1 << inc)))
        ++inc;

    for(int i = fst[inc] ; i != -1 ; i = E[i].next) {
        if(f(conf & (~E[i].to), rem - 1))
            return DP[conf][rem] = 1;
    }

    return DP[conf][rem] = 0;
}

bool good(const int cam) {
    memset(DP, 0xff, sizeof(DP));
    return f((1 << n) - 1, cam);
}

int bsearch() {
    int i, step;
    for(step = 1 ; step < n ; step *= 2);

    for(i = n ; step ; step /= 2)
        if(i - step >= 1 && good(i - step))
            i -= step;

    return i;
}


void solve() {
    et = 0;
    in >> n >> g;
    for(int i = 0 ; i < n ; ++i) {
        in >> v[i];
        fst[i] = -1;
    }

    for(int i = 0 ; i < (1 << n) ; ++i) {
        S[i] = 0;

        for(int j = 0 ; j < n ; ++j) {
            if(i & (1 << j))
                S[i] += v[j];
        }
    }


    bool ok;
    for(int i = 0 ; i < (1 << n) ; ++i) {
        ok = 1;

        if(S[i] > g)
            continue;

        for(int j = 0 ; j < n && ok ; ++j) {
            if(i & (1 << j))
                continue;

            if(S[i | (1 << j)] <= g)
                ok = 0;
        }

        if(ok) {
            for(int j = 0 ; j < n ; ++j) {
                if(i & (1 << j))
                    addEdge(j, i);
            }
        }
    }

    out << bsearch() << "\n";
}


int main() {
    for(int i = 1 ; i <= 3 ; ++i)
        solve();
}
