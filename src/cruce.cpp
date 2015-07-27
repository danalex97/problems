#include <fstream>
using namespace std;

struct node{
    int idx;
    node *L, *R;
    node(const int idx):
        idx(idx),
        L(0),
        R(0){}
};

const int MAX_N = 500100;

int inord[MAX_N];
int preord[MAX_N];
int CR;
int n;

ifstream in("curatenie.in");
ofstream out("curatenie.out");

node * root;

int which[MAX_N];

int son[MAX_N][2];

void down(const int left, const int right, node * &root){
    if(left > right)
        return;
    const int poz = which[root->idx];
    if(left < poz){
        root->L = new node(preord[++CR]);
        son[root->idx][0] = root->L->idx;
        down(left, poz - 1, root->L);
    }
    if(poz < right){
        root->R = new node(preord[++CR]);
        son[root->idx][1] = root->R->idx;
        down(poz + 1, right, root->R);
    }
}

int main(){
    in >> n;

    for(int i = 1 ; i <= n ; ++i){
        in >> inord[i];
        which[inord[i]] = i;
    }

    for(int i = 1 ; i <= n ; ++i)
        in >> preord[i];

    root = new node(preord[++CR]);

    down(1, n, root);
    for(int i = 1 ; i <= n ; ++i){
        for(int j = 0 ; j < 2 ; ++j)
            out << son[i][j] << " ";
        out << "\n";
    }
}
