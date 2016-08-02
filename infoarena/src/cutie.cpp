#include <iostream>
#include <fstream>
#include <deque>

#define pb push_back
#define pf push_front

using namespace std;

const int MAX_N = 500000 + 1;
const int MOD = 543217;

int n;

int best = 0;
int ap = 1;

bool viz[20];

int v[20];

inline int abs(const int x) {
    if(x < 0)
        return -x;
    else
        return x;
}

bool show;

void bkt(int at, int sum) {
    if(at == n + 1) {
        if(sum > best) {
            best = sum;
            ap = 1;
        } else if(sum == best) {
            ++ap;

            if(show) {
                for(int i = 1 ; i < at ; ++i)
                    cout << v[i] << " ";
                cout << "\n";
            }

        }
    } else {
        for(int i = 1 ; i <= n ; ++i) {
            if(viz[i])
                continue;

            viz[i] = 1;
            v[at] = i;
            int ns = sum;
            if(at > 1)
                ns += abs(v[at] - v[at - 1]);

            bkt(at + 1, ns);

            viz[i] = 0;
            v[at] = 0;
        }
    }
}

long long sol[MAX_N] =
    {0, 0, 2, 4, 2, 8, 8, 48, 72, 576, 1152, 11520, 28800};

deque<int> D;

int main() {
    ifstream in("urat.in");
    in >> n;

    long long now = -1;

    for(int i = 2 ; i <= n ; ++i) {
        now += i - i % 2;
    }

    ofstream out("urat.out");

    out << now << "\n";

    now = 1;

    int dat = 0;
    long long add = 0;

    for(int i = 4 ; i <= n ; ++i) {

        if(dat == 2) {
            ++now;

            if(now >= MOD)
                now -= MOD;

            dat = 0;
        }

        ++dat;

        add += now;

        if(add >= MOD)
            add -= MOD;

        sol[i] = (1LL * sol[i - 2] * add) % MOD;
    }

    out << sol[n] << "\n";

    D.pb(1);

    int lo = 2;
    int hi = n;

    bool at = 0;

    while(lo <= hi) {
        if(!at) {
            D.pb(hi);
            --hi;
            if(lo <= hi) {
                D.pf(hi);
                --hi;
            }
        } else {
            D.pb(lo);
            ++lo;
            if(lo <= hi) {
                D.pf(lo);
                ++lo;
            }
        }
        at ^= 1;
    }

    for(int i = 0 ; i < (int)D.size() ; ++i) {
        out << D[i] << " ";
    }
    out << "\n";
    return 0;
}

