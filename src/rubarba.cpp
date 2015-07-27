#include <cstdio>
#include <cstring>
#include <utility>

using namespace std;

const int MAX_N = 19;
const int INF = (1 << 29 ) - 1;

char s[MAX_N][30010];

int len[MAX_N];
int fitness[MAX_N][MAX_N];

int n;
int T[30010];

int DP[1 << MAX_N][MAX_N];
int before[1 << MAX_N][MAX_N];


void table(char * what , int len_w)
{
    int s,i;

    T[0] = -1,T[1] = 0;
    s = 0;

    for(i = 2 ; i < len_w ; ){

        if(what[i - 1] == what[s]){
            ++s;
            T[i++] = s;
        } else if(s > 0)
            s = T[s];

        else T[i++] = 0;
    }

}

int KMP(char * what,int len_w,char * into,int len_i)
{
    int s,i;
    i = s = 0;

    for(i = 0 ; i + s < len_i ;){

        if(into[i + s] == what[s]){
            ++s;

            if(s == len_w)
                return len_w;

        } else {
            i = i + s - T[s];
            if(T[s] > 0)
                s = T[s];
            else s = 0;
        }
    }

    return s;
}

void read()
{
    freopen("adn.in","r",stdin);
    freopen("adn.out","w",stdout);

    scanf("%d\n",&n);

    for(int i = 0 ; i < n ; ++ i){
        scanf("%s\n",s[i]);
        len[i] = strlen(s[i]);
    }
}

void ending(const int conf,const int at)
{

    const int bitwise = 1 << at;
    int i,posib;

    if( (conf & (conf - 1) ) == 0){

        DP[conf][at] = len[at];

    } else {

        DP[conf][at] = INF;

        for(i = 0 ; i < n ; ++ i)
            if( ((1 << i) & conf) && i != at){

                posib = len[at] - fitness[i][at];
                posib += DP[conf ^ bitwise][i];

                if(posib < DP[conf][at]){

                    before[conf][at] = i;
                    DP[conf][at] = posib;
                }
            }
    }
}

void process(const int conf)
{
    for(int i = 0 ; i < n ; ++ i)
        if( (1 << i) & conf)
            ending(conf,i);
}

void show(const int conf,const int last)
{

    if( (conf & (conf - 1)) == 0){
        printf("%s",s[last]);
    } else {
        const int & prev = before[conf][last];
        show(conf ^ (1 << last) , prev);
        printf("%s",s[last] + fitness[prev][last]);
    }
}

int main()
{
    read();

    int i,j;

    for(i = 0 ; i < n ; ++ i){
        table(s[i],len[i]);
        for(j = 0 ; j < n ; ++ j)
            if(i != j)
                fitness[j][i] = KMP(s[i],len[i],s[j],len[j]);
    }

    for(i = 1 ; i < (1 << n) ; ++ i)
        process(i);

    int conf = (1 << n) - 1 , end = 0;

    for(i = 1 ; i < n ; ++ i)
        if(DP[conf][i] < DP[conf][end])
            end = i;

    show(conf,end);
    printf("\n");

    return 0;
}
