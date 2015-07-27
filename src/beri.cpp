#include <tr1/unordered_map>
#include <fstream>
#include <iostream>

using namespace std;

ifstream in("pariuri.in");
ofstream out("pariuri.out");

typedef long long LL;

tr1::unordered_map<int, LL> H;

int main(){
    int n,a,b,m;
    in >> n;
    while(n--){
        in >> m;
        for(int i = 0 ; i < m ; ++i){
            in >> a >> b;
            H[a] += b;
        }
    }
    out << H.size() << "\n";
    tr1::unordered_map<int, LL> :: iterator it;
    for(it = H.begin() ; it != H.end() ; ++it)
        out << it->first << " " << it->second << " ";
    out << "\n";
}
