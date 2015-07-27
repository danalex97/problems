#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <cstdio>

using namespace std;

const int MAX_N = 13;


ifstream in("avd.in");
ofstream out("avd.out");

int n;
vector< pair<int, int> > G[MAX_N];
pair<int, int> E[MAX_N];

vector< vector<int> > C;
vector<int> comp;

bool viz[MAX_N];
int now;

bool u[MAX_N];

int DP[MAX_N + 1][MAX_N + 1];

int f(const int n, const int lim){

  if(n < 0 || lim <= 0)
    return 0;
  if(n <= 1 || lim == 1)
    return 1;

  int &now = DP[n][lim];

  if(now != -1)
    return now;

  return (now = f(n - lim, lim) + f(n, lim - 1));
}

void dfs(const int nod){
  viz[nod] = 1;
  ++now;
  for(vector< pair<int,int> > :: iterator it = G[nod].begin() ; it != G[nod].end() ; ++ it)
    if(u[it->second] && !viz[it->first])
      dfs(it->first);
}

void add(){
  for(vector< vector<int> > :: iterator it = C.begin() ; it != C.end() ; ++ it)
    if(comp == *it)
      return;
  C.push_back(comp);
}

void conex(const int conf){
  int i;

  for(i = 0 ; i < n - 1 ; ++ i)
    u[i] = conf & ( 1 << i );

  memset(viz, 0, sizeof(viz));
  comp.clear();
  for(i = 0 ; i < n ; ++ i)
    if(!viz[i]){
      now = 0;
      dfs(i);
      comp.push_back(now);
    }
  sort(comp.begin(), comp.end());

  add();
}

double solve(){
  in >> n;

  int i,a,b;

  for(i = 0 ; i < n ; ++i)
    G[i].clear();

  C.clear();

  for(i = 0 ; i < n - 1 ; ++i){
    in >> E[i].first >> E[i].second;

    E[i].first--,
    E[i].second--;

    G[E[i].first].push_back(make_pair(E[i].second, i));
    G[E[i].second].push_back(make_pair(E[i].first, i));
  }

  for(i = 0 ; i < (1 << (n-1)) ; ++i)
    conex(i);

  int get = C.size();
  int total = f(n, n);

  return double(get) / total;
}

int main(){
  memset(&DP[0][0], 0xff, sizeof(DP));
  int T;
  in >> T;
  freopen("avd.out", "w", stdout);
  while(T--){
    const double rez = solve();

    printf("%.5f\n", rez);
    //fprintf(stderr, "%.5f\n", rez);
  }
}
