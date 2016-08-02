#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

int main(){
    ifstream in("perechi.in");
    int n;
    in >> n;
    int i,j;
    long long tot = 1;
    for(int i = 2 ; i * i <= n ; ++i){
        if(n % i == 0){
            int p = 0;
            while(n % i == 0){
                n /= i;
                ++p;
            }
            tot *= 2 * p + 1;
        }
    }
    if(n > 1)
        tot *= 3;
    tot = (tot + 1) / 2;
    ofstream out("perechi.out");
    out << tot << "\n";
}
