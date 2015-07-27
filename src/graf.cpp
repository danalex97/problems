#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long long LL;

const int MAX_N = 50010;

LL v[MAX_N],P,S;
int n;
short semn[MAX_N];
char show[MAX_N];

template<class _type>
void swap(_type &a,_type &b)
{
    _type aux = a;
    a = b;
    b = aux;
}

template<class _type>
class vector{
private:

    int now;
    _type v[MAX_N];

public:

    vector():now(0){}

    _type & operator[](const int poz)
    {return v[poz];}

    void push_back(const _type x)
    {v[now++] = x;}

    void pop_back()
    {--now;}

    int size()
    {return now;}
    _type & back()
    {return v[now-1];}

};

vector<int> plus;
vector<int> minus;



int get(vector<int> & now)
{
    if(now.size() == 0)
        return 0;

    int ret = rand() % now.size();
    swap(now[ret],now.back());
    ret = now.back();
    now.pop_back();

    return ret;
}

int main()
{
    srand(time(0));

    freopen("semne.in", "r", stdin);
    freopen("semne.out", "w", stdout);

    scanf("%d%lld",&n,&P);

    int i;

    for(i = 0 ; i < n ; ++ i){
        scanf("%lld",v+i);

        if(i & 1){
            semn[i] = 1;
            plus.push_back(i);
        }else{
            semn[i] = -1;
            minus.push_back(i);
        }
        S += semn[i] * v[i];
    }

    while(S != P){
        if ( S < P ){

            i = get(minus);
            plus.push_back(i);
        } else {

            i = get(plus);
            minus.push_back(i);
        }
        semn[i] *= -1;
        S += 2 * semn[i] * v[i];
    }
    for(i = 0 ; i < n ; ++ i)
        if(semn[i] == 1)
            show[i] = '+';
        else show[i] = '-';

    printf("%s\n",show);
}
