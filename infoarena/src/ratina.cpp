#include <fstream>
#include <cstring>

using namespace std;

const int MAX_N = 10100;
const int INF = (1 << 30) - 1;

struct trie{
    int next[26];
    trie(){
        memset(next, 0 , sizeof(next));
    }
};

trie pre[200010];
int CR = 1;
int root = 0;

char s[2010];
int ln[MAX_N];

int n,m;

ifstream in("ratina.in");
ofstream out("ratina.out");

int * which[MAX_N];

void insert(char const *const at, const int idx){
    int now = root;

    const int len = strlen(at);
    ln[idx] = len;
    which[idx] = new int[len];

    for(int i = 0 ; i < len ; ++i){

        const int nxt = at[i] - 'a';

        if(pre[now].next[nxt] == 0)
            pre[now].next[nxt] = CR++;

        now = pre[now].next[nxt];
        which[idx][i] = now;
    }
}

int query[10];

bool good(const int len, const int cnt){
    const int pref = which[query[0]][len];
    for(int i = 1 ; i < cnt ; ++i)
        if(which[query[i]][len] != pref)
            return 0;
    return 1;
}

int solve(const int cnt){
    int mn = INF;
    for(int i = 0 ; i < cnt ; ++i)
        if(ln[query[i]] < mn)
            mn = ln[query[i]];
    int i,step;
    for(step = 1 ; step <= mn ; step <<=1);
    for(i = -1 ; step ; step >>= 1)
        if(i + step < mn && good(i + step, cnt))
            i += step;
    return (i + 1);
}


int main(){
    in >> n >> m;
    for(int i = 1 ; i<= n ; ++i){
        in >> s;
        insert(s, i);
    }
    int cnt;
    for(int i = 1 ; i <= m ; ++i){
        in >> cnt;
        for(int j = 0 ; j < cnt ; ++j)
            in >> query[j];
        out << solve(cnt) << "\n";
    }
    return 0;
}
