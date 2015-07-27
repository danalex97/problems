#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define rock 1
#define paper 0
#define sci 2

const int MAX_N = 1000100;
const int INF = (1 << 30) - 1;

int n,k,W,D;

int norm['Z' + 10];
int counters[3];
char ch[3];

char * s,
     * show;

struct trie{
    trie * next[3];
    int best,ap,dn;
    trie(){
        best = 0;
        ap = 0;
        dn = 0;
        memset(next,0,sizeof(next));
    }
};

trie fre[MAX_N];
int CR = 1;
trie * head = fre + 0;

void down(trie * now , const char * p)
{
    now ->ap ++;
    if(*p){
        const int fol = norm[*p];
        if(now ->next[fol] == 0)
            now ->next[fol] = fre + (CR++);
        down(now ->next[fol], p+1);
        now->best = -INF;
        for(int i = 0 ; i < 3 ; ++ i){
            int next = 0;

            if(now ->next[i])
                next += now ->next[i] ->best;

            if(now ->next[counters[i]])
                next += now ->next[counters[i]] ->ap * W;

            if(next > now->best)
                now->best = next,
                now->dn = i;
        }
    } else {
        now ->best = now ->ap * D;
    }
}

inline void add()
{down(head,s);}

inline void output()
{
    int i,j;
    trie * now = head;
    for(i = 0 ;i < k ; ++ i){
        if(now == 0)
            show[i] = 'P';
        else {
            show[i] = ch[now->dn];
            now = now->next[now->dn];
        }
    }
    show[i] = 0;
    printf("%s\n",show);
}

int main()
{
    freopen("rps.in", "r", stdin);
    freopen("rps.out", "w", stdout);

    scanf("%d%d%d%d\n",&n,&k,&W,&D);
    s = new char[k];
    show = new char[k];
    int i,j;
    norm['R'] = rock;
    norm['S'] = sci;
    norm['P'] = paper;

    counters[rock] = sci;
    counters[sci] = paper;
    counters[paper] = rock;

    ch[paper] = 'P';
    ch[rock] = 'R';
    ch[sci] = 'S';

    for(i = 0 ; i < n ; ++ i){
        scanf("%s\n",s);
        add();
        output();
    }
    return 0;
}
