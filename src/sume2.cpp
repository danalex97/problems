#include <fstream>
#include <iostream>

using namespace std;

const int MOD = 194767;

int n, s;

int DP[2][32900];

int bkt(int i, int last, int sum) {
    if(i == n + 1)
        return sum == s;

    int ret = 0;
    ret += bkt(i + 1, last + 1, sum + (last + 1));
    ret += bkt(i + 1, last - 1, sum + (last - 1));

    return ret;
}

int solve() {
    int mx = n * (n + 1) / 2;
    if(s > mx)
        return 0;
    DP[1][0] = 1;

    for(int i = 2 ; i <= n ; ++i) {
        int pp = i % 2;
        for(int j = 0 ; 2 * j <= i * (i - 1) ; ++j) {

            DP[pp][j] = 0;

            int a = j - (i - 1),
                b = j + (i - 1);

            if(a < 0)
                a = -a;

            if(a <= mx)
                DP[pp][j] += DP[!pp][a];

            if(b <= mx)
                DP[pp][j] += DP[!pp][b];

            while(DP[pp][j] >= MOD)
                DP[pp][j] -= MOD;
        }
    }
    return DP[n % 2][s];
}

int main() {
    ifstream in("1-sir.in");
    in >> n >> s;
    if(s < 0)
        s = -s;
    in.close();

    ofstream out("1-sir.out");
    int sol = solve();
    out << sol << "\n";
    out.close();


    cout << sol << "\n";
    //cout << bkt(2, 0, 0) << "\n";
}
