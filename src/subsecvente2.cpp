#include <fstream>
#include <set>

using namespace std;

set<long long> T;

void fun(long long a){
    if(a <= 2)
        return;
    T.insert(a/2);
    if(a % 2)
        T.insert(a/2 + 1);
    return fun(a/2);
}

int main(){
    ifstream in("lantaditiv.in");


    long long a;
    in >> a;
    T.insert(a);
    T.insert(1);
    fun(a);

    ofstream out("lantaditiv.out");
    
    out << T.size() << "\n";
    for(set<long long> :: iterator it = T.begin() ; it != T.end() ; ++it)
        out << *it << " ";
    out << "\n";
    

    return 0;
}
