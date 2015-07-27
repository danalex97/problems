#include <fstream>
#include <deque>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

const int maxn = 30100;


#define rm_front() while(!D.empty() && D.front() < i-hi )D.pop_front()
#define rm_back() while(!D.empty() && aux[i-lo] <= aux[D.back()])D.pop_back()
int cost[maxn];
int timp[maxn];
double aux[maxn];
int n,lo,hi,val;

ifstream in("secv3.in");
ofstream out("secv3.out");

const int prec = 4;
const double p10 = 1e4;

deque<int> D;

bool good(int cautat){

  double best= -(1<<30), fixat = cautat/p10;
  for(register int i = 1 ; i <= n ; ++ i)
    aux[i] = aux[i-1] + cost[i] - fixat * timp[i];

  D.clear();
  D.push_back(0);
  for(register int i = lo ; i <= n ; ++ i){
    rm_front();
    rm_back();
    D.push_back(i-lo);

    best = max(best,aux[i] - aux[D.front()]);
  }

  return best >= -(1e-4);
}

int bsearch(){
  int i,step;
  val *= p10;
  for(step=1;step<val;step<<=1);
  for(i=0;step;step>>=1){
    if(i+step <= val && good(i+step))
      i += step;
  }
  return i;
}


int main(){
  in >> n >> lo >> hi;
  for(register int i = 1 ; i <= n ; ++ i){
    in >> cost[i];
    val = max(val,cost[i]);
  }for(register int i = 1 ; i <= n ; ++ i){
    in >> timp[i];
  }
  out.precision(prec);
  float show = bsearch() / p10;
  out << show << "\n";
}
