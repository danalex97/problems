#include <set>
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstring>
#include <tr1/unordered_map>

using namespace std;

const int MAX_N = 4000;

long long n;
int k;

set<long long> T;

void factorize(long long n) {
    int lim = sqrt(n);
    for(int i = 1 ; i <= lim + 1 ; ++i) {
        if(n % i == 0){
            T.insert(i);
            T.insert(n / i);
        }
    }
}

int brute(long long n, int last) {
    if(n == 1)
        return 1;

    int ret = 0;
    for(long long int i = last ; i <= n ; ++i)
        if(n % i == 0)
            ret += brute(n / i, i);
    return ret;
}

tr1::unordered_map<long long, int> H;
vector<long long> v;

long long f[MAX_N];

int DP[MAX_N][MAX_N];

//DP[i][j] = in cate moduri se poate forma divizorul i
// ca produs al divizorilor j, j + 1, ..., n


int main() {
    ifstream in("desc.in");
    in >> n >> k;
    factorize(n);

    //int brt = brute(n, 2);

    v = vector<long long> (T.begin(), T.end());
    T.clear();

    n = v.size();


    for(int i = 0 ; i < n ; ++i)
        f[i + 1] = v[i];
    v.clear();

    for(int i = 1 ; i <= n ; ++i){
        H[f[i]] = i;
    }

    for(int i = 1 ; i <= n ; ++i)
        DP[1][i] = 1;

    for(int i = 2 ; i <= n ; ++i) {
        for(int j = n ; j >= 1 ; --j) {
            DP[i][j] += DP[i][j + 1];

            if(f[i] % f[j] == 0) {
                long long nxt = f[i] / f[j];
                nxt = H[nxt];
                DP[i][j] += DP[nxt][j];
            }
        }
    }

    ofstream out("desc.out");
    #define cout out
    cout << DP[n][2] << "\n";

    int last = 2;

    while(last <= n) {

        if(f[n] % f[last]) {
            ++last;
            continue;
        }
        long long nxt = f[n] / f[last];
                  nxt = H[nxt];

        if(DP[nxt][last] < k) {
            k -= DP[nxt][last];
            ++last;
        } else {
            cout << f[last] << " ";
            n = nxt;
        }
    }

    return 0;
}
