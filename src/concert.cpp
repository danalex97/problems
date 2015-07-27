#include <fstream>

using namespace std;

const int MAX_N = 10001;
const int MAX_K = 1001;

int val[MAX_N];
int S[MAX_N];

int n,k;

int DP[2][MAX_N];

void dynamic(const int st){
    for(int j = st ; j <= k ; ++j){

        int *const now = DP[j&1];
        int *const before = DP[~j&1];

        int choice = 0;

        for(int i = 1 ; i <= n ; ++i){

            if(before[i] - S[i] > choice)
                choice = before[i] - S[i];

            now[i] = S[i] + choice;

            if(now[i - 1] > now[i])
                now[i] = now[i-1];
        }
    }
}

int main(){
    ifstream in("ferma.in");

    in >> n >> k;

    for(int i = 1 ; i <= n ; ++i){
        in >> val[i];
        S[i] = S[i-1] + val[i];
    }

    dynamic(1);

    int bst = max(0, DP[k&1][n]);

    for(int i = 1 ; i <= n ; ++i)
        DP[1][i] = max(DP[1][i-1], S[i]);

    dynamic(2);

    for(int i = 1 ; i <= n ; ++i)
        bst = max(bst, DP[k&1][i] + S[n] - S[i]);

    ofstream out("ferma.out");
    out << bst << "\n";
}
