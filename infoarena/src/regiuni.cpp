#include <vector>
#include <cstdio>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 50100;

struct edge{
  int to;
  bool u;
  edge * mate;
};

vector<edge*> G[MAX_N];
vector<edge*> extra[MAX_N];
vector<int> path;
stack<int> ST;

char buff[1 << 22];
char *at = buff;

int n,m;
bool bad[MAX_N];
bool faked;
bool viz[MAX_N];

void euler(const int, const bool);

void add_edge(const int one, const int two, vector<edge*> * G){

  edge * one_to_two = new edge;
  edge * two_to_one = new edge;

  one_to_two->mate = two_to_one;
  two_to_one->mate = one_to_two;

  one_to_two->u = 0;
  two_to_one->u = 0;

  one_to_two->to = two;
  two_to_one->to = one;

  G[one].push_back(one_to_two);
  G[two].push_back(two_to_one);
}

void current_path(){
  int i;
  bool cycle = 1;
  for(i = 0 ; i < path.size() ; ++ i)
    if(bad[i])
      cycle = 0;
  if(cycle){
    if(path.size() > 1){
      at += sprintf(at, "%d ", path.size());
      for(i = 0 ; i < path.size() ; ++ i)
        at += sprintf(at, "%d ", path[i]);
      at += sprintf(at, "\n");
    }
  } else {
    const int sz = path.size();
    if(!bad[i = 0]){
      for(i = 1 ; i < sz && bad[i] == 0 ; ++ i)
        path.push_back(path[i]);
      path.push_back(i);
    }
    int lst = i + 1;
    for(i = lst ; i < path.size() ; ++ i){
      if(bad[i] || i == path.size() - 1){
        if(i - lst + 1 > 1){
          at += sprintf(at, "%d ", i - lst + 1);
          for(int j = lst ; j <= i ; ++ j)
            at += sprintf(at, "%d ", path[j]);
          at += sprintf(at, "\n");
        }
        lst = i + 1;
      }
    }
  }
}

void expand(const int nod, vector<edge*> * G){
  while(!G[nod].empty()){
    if(G[nod].back()->u){
      delete G[nod].back();
      G[nod].pop_back();
    }
    else{
      const int aux = G[nod].back()->to;
      G[nod].back()->mate->u = 1;
      delete G[nod].back();
      G[nod].pop_back();
      euler(aux, G == extra);
    }
  }
}

void euler(const int nod, const bool is_bad){
  viz[nod] = 1;
  expand(nod, G);
  expand(nod, extra);

  path.push_back(nod);

  bad[path.size() - 1] = is_bad;
}

int main(){
  freopen("johnie.in", "r", stdin);
  freopen("johnie.out", "w", stdout);
  scanf("%d%d", &n, &m);
  for(int i = 0 ; i < m ; ++ i){
    int a,b;
    scanf("%d%d", &a, &b);
    add_edge(a, b, G);
  }

  vector<int> alone;
  for(int i = 1 ; i <= n ; ++ i)
    if(G[i].size() % 2 == 1)
      alone.push_back(i);

  for(int i = 0 ; i < alone.size() ; i += 2)
    add_edge(alone[i], alone[i + 1], extra);

  for(int i = 1 ; i <= n ; ++ i){
    if(!viz[i] && G[i].size() % 2 == 1){
      path.clear();
      euler(i, 0);
      current_path();
    }
  }
  for(int i = 1 ; i <= n ; ++ i)
    if(!viz[i]){
      path.clear();
      euler(i, 0);
      current_path();
    }
  printf("%d\n", count(buff, at, '\n'));
  printf("%s", buff);
  return 0;
}
