#include <fstream>
#include <cstring>
#include <iostream>

using namespace std;

const int MAX_N = 51;
const int MAX_V = 10000 + 1;
const int INF = 0x3f3f3f3f;

int mx;
int n, E;
int v[MAX_N];

int DP[MAX_N][MAX_V];
int bst[MAX_N][MAX_V];

int dist(int a, int b) {
    if(a <= b) {
        return b - a;
    } else {
        return dist(b, a);
    }
}

struct deque{
    int lo, hi;
    int v[MAX_V * 2];

    void clear() {
        lo = hi = 0;
    }

    deque():
        lo(0),
        hi(0) {}
    bool empty() {

        if(lo == hi) {
            clear();
            return 1;
        } else {
            return 0;
        }

    }
    void pop_front() {
        --hi;
    }
    void pop_back() {
        ++lo;
    }

    int front() {
        return v[hi - 1];
    }

    int back() {
        return v[lo];
    }

    void push_front(int x) {
        v[hi] = x;
        ++hi;
    }
} D;

bool good(int d) {
    memset(DP, 0x3f, sizeof(DP));
    memset(bst, 0x3f, sizeof(bst));

    DP[1][0] = 0;

    for(int i = 0 ; i < d ; ++i)
        bst[1][i] = 0;

    for(int i = 2 ; i <= n ; ++i) {
        for(int j = 0 ; j <= mx ; ++j) {
            DP[i][j] = dist(v[i], j);
            if(DP[i - 1][j] < bst[i - 1][j - 1])
                DP[i][j] += DP[i - 1][j];
            else
                DP[i][j] += bst[i - 1][j - 1];
        }


        D.clear();
        for(int j = 0 ; j <= mx ; ++j) {

            while(!D.empty() && DP[i][j] < DP[i][D.front()])
                D.pop_front();
            while(!D.empty() && D.back() <= j - d)
                D.pop_back();

            D.push_front(j);
            bst[i][j] = DP[i][D.back()];
        }

    }

    return DP[n][v[n]] <= E;
}

int bsearch(int mx) {
    int i, step;
    for(step = 1 ; step < mx ; step <<= 1);

    for(i = mx ; step ; step >>= 1) {
        if(i - step >= 0 && good(i - step))
            i -= step;
    }

    return i;
}

int main() {
    ifstream in("stalpi2.in");
    in >> n >> E;

    for(int i = 2 ; i <= n ; ++i) {
        in >> v[i];
    }

    mx = v[n];

    ofstream out("stalpi2.out");
    out << bsearch(MAX_V) << "\n";
    return 0;
}
