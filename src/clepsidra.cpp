#include <fstream>
#include <set>
#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

#define x first
#define y second

const int MAX_N = 200000 + 1;
const int MAX_LOG = 18;

int n, m, q;

int RMQ[MAX_N][MAX_LOG];

int best[MAX_N];

set< pair<int, int> > T;

pair<int, int> SEG[MAX_N];

pair<int, int> Q[MAX_N];

void buildRMQ() {
    for(int i = 1 ; i <= n ; ++i)
        RMQ[i][0] = best[i];

    for(int j = 1 ; j < MAX_LOG ; ++j) {
        for(int i = 1 ; i <= n ; ++i) {
            const int nxt = RMQ[i][j - 1];
            RMQ[i][j] = RMQ[nxt][j-1];
        }
    }
}

int advance(int now, int much) {

    for(int i = 0 ; much ; ++i) {
        if(much & (1 << i)) {
            much ^= 1 << i;
            now = RMQ[now][i];
        }
    }

    return now;
}

int bsearch(const int at) {
    int i, step;
    for(step = 1 ; step < m ; step *= 2);

    if(advance(Q[at].x, m) < Q[at].y)
        return -1;

    for(i = m ; step ; step /= 2)
        if(i - step >= 0 && advance(Q[at].x, i - step) >= Q[at].y)
            i -= step;

    return i;
}

int main() {
    ifstream in("reborn.in");
    in >> n >> m >> q;
    for(int i = 1 ; i <= m ; ++i) {
        in >> SEG[i].x >> SEG[i].y;
    }
    for(int i = 1 ; i <= q ; ++i) {
        in >> Q[i].x >> Q[i].y;

        if(Q[i].y < Q[i].x)
            swap(Q[i].x, Q[i].y);
    }

    sort(SEG + 1, SEG + m + 1);
    int at = 1;

    int bst = 0;

    for(int i = 1 ; i <= n ; ++i) {
        while(at <= m && SEG[at].x <= i) {
            if(SEG[at].y > bst)
                bst = SEG[at].y;
            at++;
        }
        if(bst > i)
            best[i] = bst;
        else
            best[i] = i;
    }

    buildRMQ();

    ofstream out("reborn.out");
    for(int i = 1 ; i <= q ; ++i) {
        out << bsearch(i) << "\n";
    }
    out.close();

    return 0;
}
