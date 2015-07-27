#include <fstream>
#include <utility>
#include <algorithm>

using namespace std;

const int MAX_N = 300;
const int MAX_Q = 20000;

int m[MAX_N][MAX_N];
int norm[MAX_N * MAX_N];


int id[MAX_N][MAX_N];
int xx[MAX_N * MAX_N];
int yy[MAX_N * MAX_N];
int n, q;

int v(const int poz) {
    const int x = xx[poz], y = yy[poz];
    return m[x][y];
}


bool c1(const int a, const int b){
    int xa = xx[a], ya = yy[a],
        xb = xx[b], yb = yy[b];

    return m[xa][ya] > m[xb][yb];
}

int ans[MAX_Q];
bool good[MAX_Q];



struct query{
    int x1,y1;
    int x2,y2;
    int id;
};

int v(const query &A) {
    return ans[A.id];
}

bool comp(const query &A, const query &B) {
    return ans[A.id] > ans[B.id];
}

query Q[MAX_Q];

int TT[MAX_N * MAX_N];
int under[MAX_N * MAX_N];

void resetForest() {
    for(int i = 0 ; i < n * n ; ++i) {
        TT[i] = i;
        under[i] = 1;
    }
}

int father(const int x) {
    if(TT[x] == x)
        return x;
    const int up = father(TT[x]);
    TT[x] = up;
    return up;
}

bool same(const int x, const int y) {
    return father(x) == father(y);
}

void unite(const int x, const int y) {
    if(TT[x] != x || TT[y] != y)
        return unite(father(x), father(y));

    if(same(x, y))
        return;

    if(under[x] >= under[y]) {
        TT[y] = x;
        under[x] += under[y];
    } else {
        TT[x] = y;
        under[y] += under[x];
    }
}

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

void unite(const int poz) {
    const int ox = xx[poz],
              oy = yy[poz];

    for(int i = 0 ; i < 4 ; ++i) {
        const int x = ox + dx[i],
                  y = oy + dy[i];

        if(x < 0 || y < 0 || x == n || y == n)
            continue;

        if(m[x][y] >= m[ox][oy])
            unite(id[x][y], id[ox][oy]);
    }
}

void solve(const int i) {

    const int a = id[Q[i].x1][Q[i].y1],
              b = id[Q[i].x2][Q[i].y2];

    good[Q[i].id] = same(a, b);
}

void solveQueries() {
    resetForest();
    sort(Q, Q + q, comp);

    int i, j;
    i = 0, j = 0;
    //i is the current cell
    //j is the current query
    while(j < q) {
        const int w = norm[i];

        if(i < n * n && v(w) >= v(Q[j])) {

            unite(w);
            ++i;
        } else {
            solve(j);
            ++j;
        }
    }
}


void bsearch(const int MAX_VAL) {
    int step;
    for(step = 1 ; step < MAX_VAL ; step *= 2);

    for(; step ; step >>= 1) {
        for(int i = 0 ; i < q ; ++i)
            ans[i] += step;

        solveQueries();

        for(int i = 0 ; i < q ; ++i) {
            if(!good[i])
                ans[i] -= step;
        }
    }
}

int main(){
    ifstream in("matrice2.in");
    in >> n >> q;

    int at = 0;
    int mx = 0;

    for(int i = 0 ; i < n ; ++i)
        for(int j = 0 ; j < n ; ++j) {
            in >> m[i][j];
            id[i][j] = at;
            xx[at] = i;
            yy[at] = j;
            ++at;

            if(m[i][j] > mx)
                mx = m[i][j];
        }

    for(int i = 0 ; i < q ; ++i) {
        in >> Q[i].x1 >> Q[i].y1;
        in >> Q[i].x2 >> Q[i].y2;

        --Q[i].x1, --Q[i].y1;
        --Q[i].x2, --Q[i].y2;

        Q[i].id = i;
    }
    in.close();

    for(int i = 0 ; i < n * n ; ++i)
        norm[i] = i;

    sort(norm, norm + n * n, c1);

    bsearch(mx);

    ofstream out("matrice2.out");
    for(int i = 0 ; i < q ; ++i)
        out << ans[i] << "\n";
    out.close();

    return 0;
}
