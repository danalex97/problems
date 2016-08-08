#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 10;

int k, p, q;

int n;

int fr[MAX_N];

struct node {
	int col;
	int nxt;
};

node _data[MAX_N];
int _at;

int first[MAX_N];

int nxt[MAX_N];

int qFr;
int qId;

void add(int fr, int col) {
	++_at;
	_data[_at].col = col;
	_data[_at].nxt = first[fr];

	first[fr] = _at;
}


void move(int from, int to) {
/* move the first element from @first[from] to @first[to] */

	int x = first[from];
	first[from] = _data[x].nxt;

	_data[x].nxt = first[to];
	first[to] = x;
}

void step(int fr) {
	move(fr, fr - 1);
}

int sol[MAX_N];

int at;

void debug() {
	for(int i = 1; i <= sol[0]; ++i)
		printf("%d ", sol[i]);
	printf("\n");
}

bool ok(int col) {
	return col != p;
}

bool tryToPlace(int at) {

	if(at == 0)
		return false;

	if(qFr == at && q != p) {
	/* we have an option to place the colour @q */
		swap(_data[first[at]].col, _data[qId].col);
		//printf("placed %d\n", q);
		qId = first[at];
		qFr--;
		sol[++sol[0]] = q;
		step(at);
		p = q;
		return true;
	}

	for(int i = first[at]; i != 0; i = _data[i].nxt) {
		int col = _data[i].col;
		int j = first[at];
		if(ok(col)) {
			//printf("placed %d\n", col);
			swap(_data[i].col, _data[j].col);
			sol[++sol[0]] = col;
			step(at);
			p = col;
			return true;
		}
	}
	return false;
}

bool place() {
	while(at > 0 && first[at] == 0)
		--at;

	int now = at;
	for(int i = 0; i <= 100; ++i) 
		if(tryToPlace(at))
			return true;
		else
			now = nxt[now];

	return false;
}

int main() {
	cin >> k >> p >> q;
	for(int i = 1; i <= k; ++i) {
		cin >> fr[i];

		if(i == p || i == q) {
			--fr[i];
		}

		n += fr[i];

		if(i == q) {
			qFr = fr[i];
			qId = i;
		}

		add(fr[i], i);
	}

	int last = 0;
	for(int i = 1; i <= n; ++i) {
		nxt[i] = last;
		if(first[i] != 0) {
			last = i;
		}
	}
	sol[++sol[0]] = p;

	at = n;

	while(first[at] == 0)
		--at;

	while(n > 0) {
//		debug();
		if(place()) {
			--n;
		} else {
			cout << "0\n";
			return 0;
		}
	}

	sol[++sol[0]] = q;

	for(int i = 1; i <= sol[0]; ++i)
		cout << sol[i] << " " ;
	cout << "\n";

	return 0;
}
