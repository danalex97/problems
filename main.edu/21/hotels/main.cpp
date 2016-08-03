#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5000 + 2;

vector<int> G[MAX_N];
int n;

short cnt[MAX_N][MAX_N];
long long DP[MAX_N][4];

bool viz[MAX_N];

int nodes[MAX_N];
int k;
int vals[MAX_N];

int subarb;
int depth;

int st[MAX_N];

void DFS(const int start) {

	st[0] = 0;

	int at = 1;
	st[++st[0]] = start;

	while(at <= st[0]) {
		int up = st[0];
		while(at <= up) {
			const int nod = st[at];
			at++;

			viz[nod] = 1;
			cnt[subarb][depth]++;

			const int lim = G[nod].size();
			for(int i = 0; i < lim; ++i) {
				int son = G[nod][i];
				if(!viz[son]) {
					viz[son] = 1;
					st[++st[0]] = son;
				}
			}
		}

		depth++;
	}
	
}

long long root(int nod) {
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n && cnt[i][j] > 0; ++j) {
			cnt[i][j] = 0;
		}
	}
	memset(viz, 0, sizeof(viz));
	memset(DP, 0, sizeof(DP));
	k = 0;

	for(int i = 0; i <= n; ++i)
		DP[i][0] = 1;

	viz[nod] = 1;
	for(size_t i = 0; i < G[nod].size(); ++i) {
		int son = G[nod][i];
		subarb = son;
		depth = 1;
		DFS(son);
		k++;
		nodes[k] = son;
	}

	long long ret = 0;

	for(int d = 1; d <= n && k > 0; ++d) {
		for(int i = 1; i <= k; ++i) {
			if(cnt[nodes[i]][d] == 0) {
				swap(nodes[i], nodes[k]);
				--i;
				--k;
			}
		}

		for(int i = 1; i <= k; ++i) 
			vals[i] = cnt[nodes[i]][d];

		for(int i = 1; i <= k; ++i) {
			for(int j = 1; j <= 3; ++j) {
				/* we either do not include anything from i's subtree */
				DP[i][j] = DP[i - 1][j];

				/* or we choose one of vals[i] possible nodes */
				DP[i][j] += 1LL * DP[i - 1][j - 1] * vals[i];
			}
		}

		ret += DP[k][3];
	}

	return ret;
}

int main() {
	cin >> n;
	for(int i = 1, a, b; i < n; ++i) {
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}

	long long ans = 0;

	for(int i = 1; i <= n; ++i) {
		ans += root(i);

	}

	cout << ans << "\n";

	return 0;
}
