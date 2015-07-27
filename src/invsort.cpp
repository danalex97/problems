#include <fstream>
#include <iomanip>
#include <cstdio>

using namespace std;

const int MAX_N = 300 + 2;
const long long INF = (1LL << 62) - 1;

struct point {
    int x, y;
};

int n, k;

point v[MAX_N];

int sub[MAX_N][MAX_N];


template<class T>
T abs(const T x){
    if(x > 0)
        return x;
    else
        return -x;
}

long long cross(const point &A, const point &B, const point &C) {
    const int x1 = B.x - A.x,
              y1 = B.y - A.y,
              x2 = C.x - B.x,
              y2 = C.y - B.y;

    return 1LL * x1 * y2 - 1LL * x2 * y1;
}

int area(const int i, const int j, const int k) {
    return abs(cross(v[i], v[j], v[k]));
}

bool right(const point &A, const point &B, const point &C) {
    return cross(A, B, C) < 0;
}

bool left(const point &A, const point &B, const point &C) {
    return cross(A, B, C) > 0;
}

int points(int i, int j, int k) {
    const point A = v[i],
                B = v[j],
                C = v[k];

    if(B.x < A.x || (B.x == A.x && B.y > A.y))
        return points(j, i, k);
    if(C.x < B.x || (C.x == B.x && C.y > B.y))
        return points(i, k, j);

    if(left(A, C, B)) {
        return sub[i][j] + sub[j][k] - sub[i][k];
    } else {
        return sub[i][k] - sub[i][j] - sub[j][k] - 1;
    }
}

double under[MAX_N];
double over [MAX_N];

double ans = INF;

void process(const int a, const int b) {

    if(v[b].x < v[a].x || (v[b].x == v[a].x && v[b].y > v[a].y))
        return process(b, a);

    for(int i = 0 ; i <= n ; ++i)
        under[i] = over[i] = INF;

    for(int k = 1 ; k <= n ; ++k) {
        const int A = area(a, b, k);
        const int inside = points(a, b, k);

        if(left(v[a], v[b], v[k])) {
        //k is over the ij line
            if(A < over[inside])
                over[inside] = A;
        } else if(right(v[a], v[b], v[k])) {
        //k is under the ij line
            if(A < under[inside])
                under[inside] = A;
        }
    }

    for(int i = n - 1 ; i >= 0 ; --i) {
        if(under[i] > under[i + 1])
            under[i] = under[i + 1];
        if(over[i] > over[i + 1])
            over[i] = over[i + 1];
    }

    for(int i = 0 ; i <= k ; ++i) {
        double now = under[i] + over[k - i];

        if(now < ans)
            ans = now;
    }
}

int main() {
    ifstream in("popandai.in");
    in >> n >> k;
    for(int i = 1 ; i <= n ; ++i) {
        in >> v[i].x >> v[i].y;
    }
    in.close();

    for(int i = 1 ; i <= n ; ++i) {
        for(int j = 1 ; j <= n ; ++j) {
            if(i == j || !(v[i].x < v[j].x))
                continue;
            //i is to the left of j

            for(int k = 1 ; k <= n ; ++k) {
                if(v[i].x <= v[k].x && v[k].x < v[j].x)
                    sub[i][j] += right(v[i], v[j], v[k]);
            }
            sub[j][i] = sub[i][j];
        }
    }

    for(int i = 1 ; i <= n ; ++i) {
        for(int j = i + 1 ; j <= n ; ++j) {
            process(i, j);
        }
    }

    double rez = (double)ans / 2.0;
    FILE * out = fopen("popandai.out", "w");
    fprintf(out, "%.1lf\n", rez);
    fclose(out);

    return 0;
}
