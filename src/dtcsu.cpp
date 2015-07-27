#include <cstdio>
#include <tr1/unordered_set>

using namespace std;

typedef long long LL;

const int MAX_BUFF = 1024 * 36;
const int lines = 276997;

char buff[MAX_BUFF];
char * at = buff + MAX_BUFF;

inline void next_char(){
    ++at;
    if(at - buff >= MAX_BUFF){
        fread(buff, 1, MAX_BUFF, stdin);
        at = buff;
    }
}

inline LL const next_int(){
    while(*at < '0' || *at > '9')
        next_char();
    LL ret = 0;
    while(*at >= '0' && *at <= '9'){
        ret = ret * 10 + *at - 48;
        next_char();
    }
    return ret;
}


tr1::unordered_set<LL> H;

inline void insert(const LL &val){
    if(val % 2 == 0)
        return;
    H.insert(val);
}

inline bool good(LL val){
    const LL low = val & (-val);
    if(low)
        val /= low;
    return H.count(val);
}

int main(){
    freopen("dtcsu.in", "r", stdin);
    for(int i = 0 ; i < lines ; ++i){
        const LL now = next_int();
        insert(now);
    }

    const int Q = next_int();

    int total = 0;
    for(int i = 0 ; i < Q ; ++i){
        const LL now = next_int();
        total += good(now);
    }
    freopen("dtcsu.out", "w", stdout);
    printf("%d\n", total);
}
