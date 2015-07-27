#include <fstream>
#include <queue>
#include <cmath>
#include <vector>
using namespace std;

ifstream in("ephie.in");
ofstream out("ephie.out");
#define maxn 1000005
int n,k;

int good;
int S[maxn];
int best;
int now;
struct comp
{
    bool operator()(const int&a,const int &b)const
    {
        return a > b;
    }
};

priority_queue<int,vector<int>,comp>Q;


int main()
{
    int i,x,y;
    in >> n >> k;
    for(i=1;i<=n;++i)
    {
        in >> good >> y;
        S[i] = S[i-1] - y;
        good += y;

        if(i <= k)
        {
            Q.push(good);
            now += good;
            best = S[k] + now;
        }
        else
        {
            if(good > Q.top())
            {
                now -= Q.top();
                now += good;
                Q.pop();
                Q.push(good);
                best = max(best,S[i] + now);
            }
        }
    }
    out << best << "\n";
    return 0;
}
