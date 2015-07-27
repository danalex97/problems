#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAX_N = 1022 + 1;
const int MAX_M = 1022 + 1;
const int MAX_LG = 12;

int n, m, k, q;
int ans[MAX_N];

int lg[MAX_N];
int rmq[MAX_N][MAX_N][MAX_LG];

int gcd(int a, int b) {
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

int v[4];

int getGcd() {
    int a = gcd(v[0], v[1]),
        b = gcd(v[2], v[3]);

    return gcd(a, b);
}

int query(int i, int j, int len) {
    int k = lg[len];
    int ii = i + len - (1 << k),
        jj = j + len - (1 << k);

    v[0] = rmq[i][j][k];
    v[1] = rmq[ii][j][k];
    v[2] = rmq[i][jj][k];
    v[3] = rmq[ii][jj][k];

    return getGcd();
}

bool good(int x, int y, int len) {
    if(len <= 0)
        return 0;

    if(x + len - 1 <= n && y + len - 1 <= m)
        return 1;

    return 0;
}

int losearch(int x, int y) {
    int i, step;
    for(step = 1 ; step < n ; step *= 2);

    for(i = min(n - x + 1, m - y + 1) ; step ; step /= 2) {
        if(good(x, y, i - step) && query(x, y, i - step) <= k)
            i -= step;
    }

    return i;
}

int hisearch(int x, int y) {
    int i, step;
    for(step = 1 ; step < n ; step *= 2);

    for(i = 0 ; step ; step /= 2) {
        if(good(x, y, i + step) && query(x, y, i + step) >= k)
            i += step;
    }
    return i;
}

void bsearch(int i, int j) {



    int lo = losearch(i, j),
        hi = hisearch(i, j);

    if(query(i, j, lo) == k && query(i, j, hi) == k && lo <= hi) {

        ans[hi]++;
        ans[lo - 1]--;
    }
}

int main() {

    lg[1] = 0;

    for(int i = 2 ; i < MAX_N ; ++i)
        lg[i] = lg[i / 2] + 1;

    ifstream in("xcmmdc.in");

    in >> n >> m >> k >> q;

    int x, p;
    for(int i = 1 ; i <= n ; ++i) {
        for(int j = 1 ; j <= m ; ++j) {
            in >> rmq[i][j][0];
        }
    }

    for(int k = 1 ; (1 << k) <= n ; ++k) {
        for(int i = 1 ; i + (1 << k) - 1 <= n ; ++i) {
            for(int j = 1 ; j + (1 << k) - 1 <= m ; ++j) {
                int ii = i + (1 << (k - 1)),
                    jj = j + (1 << (k - 1));

                v[0] = rmq[i][j][k - 1];
                v[1] = rmq[ii][j][k - 1];
                v[2] = rmq[i][jj][k - 1];
                v[3] = rmq[ii][jj][k - 1];

                rmq[i][j][k] = getGcd();
            }
        }
    }


    for(int i = 1 ; i <= n ; ++i)
        for(int j = 1 ; j <= m ; ++j)
            bsearch(i, j);

    int s = 0;

    for(int i = n ; i >= 0 ; --i) {
        s += ans[i];
        ans[i] = s;
    }

    ofstream out("xcmmdc.out");
    for(int i = 1 ; i <= q ; ++i) {
        in >> x;
        out << ans[x] << "\n";
    }

    return 0;
}
