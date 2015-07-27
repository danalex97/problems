#include <fstream>
#include <deque>
#include <iostream>

using namespace std;

ifstream in("sir.in");
ofstream out("sir.out");

#define pb push_back
#define rm_back(D,op) while(!D.empty() && v[i] op v[D.back()])D.pop_back()
const int maxn = 100100;
short v[maxn];
int n,lo,hi,Z;
int best = -(1<<30),st,fin;

deque<int> Q,q;

void check(int left,int right){
    if(v[Q.front()] - v[q.front()] <= Z && right-left+1 >= best){
        st = left;fin = right;
        best = right-left+1;
    }
}

int main()
{
    in >> n >> lo >> hi >> Z;
    register int le=1;

    for(register int i = 1;i <= n ; ++ i){
        in >> v[i];

        rm_back(Q,>=);
        rm_back(q,<=);


        Q.pb(i);q.pb(i);

        while(le < i-hi+1 || !Q.empty() && !q.empty() &&  v[Q.front()]-v[q.front()] > Z){
            if(!Q.empty() && Q.front() == le)Q.pop_front();
            if(!q.empty() && q.front() == le)q.pop_front();
            ++le;
        }

        check(le,i);
    }
    if(best >= lo)
        out << best << " " << st << " " << fin << "\n";
    else
        out << "-1\n";
    return 0;
}
