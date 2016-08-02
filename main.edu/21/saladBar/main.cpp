#include <bits/stdc++.h>

using namespace std;

#define DEBUG 0
#define dprintf(...) if(DEBUG)printf(__VA_ARGS__)

const int MAX_N = 1e6;

char s[MAX_N + 2];
int  S[MAX_N + 2];
int ans[MAX_N + 2];
int queries[MAX_N + 2];

int dr[MAX_N + 2];
int st[MAX_N + 2];
int _st[MAX_N + 2];

int n;

namespace Stack {
	int _stack[MAX_N + 1];
	int _top;

	void init() {
		_top = 0;
	}

	void push(int x) {
		_stack[_top] = x;
		_top++;
	}

	bool empty() {
		return _top == 0;
	}

	int top() {
		return _stack[_top - 1];
	}

	int size() {
		return _top;
	}

	void pop() {
		_top--;
	}

	int at(int x) {
		return _stack[x];
	}

	int depth(int x) {
		return at(_top - x - 1);
	}
}

namespace AIB {
	int _AIB[MAX_N + 2];

	int lsb(int x) {
		return x & (-x);
	}

	void update(int pos, int val) {
		for(int i = pos; i <= n; i += lsb(i)) 
			_AIB[i] = max(_AIB[i], val);
	}

	int query(int pos) {
		int ret = 0;
		for(int i = pos; i > 0; i -= lsb(i))
			ret = max(ret, _AIB[i]);
		return ret;
	}

}

int bsearch() {
		const int val = S[Stack::top() - 1];
		const int n = Stack::size();
		int i, step;
		for(step = 1; step <= n && S[Stack::depth(step)] >= val; step *= 2);

		for(i = -1; step; step /= 2) {
			if(i + step < n && S[Stack::depth(i + step)] >= val)
				i += step;
		}
		return Stack::depth(i + 1) - 1;
}

void solveForLimits(char* s, int* arr) {
	for(int i = 1; i <= n; ++i) {
		S[i] = S[i - 1];
		if(s[i] == 'p')
			S[i]++;
		else
			S[i]--;
	}

	Stack::init();

	dprintf("S = ");
	for(int i = 1; i <= n; ++i)
		dprintf("%d ", S[i]);
	dprintf("\n");

	S[n + 1] = numeric_limits<int>::min();
	Stack::push(n + 1);

	/* 
	 * We want to find our far deep into the stack we can go
	 * And have an element >= S[i]
	 */
	for(int i = n; i >= 1; --i) {
		while(!Stack::empty() && S[i] <= S[Stack::top()])
			Stack::pop();

		Stack::push(i);

		arr[i] = bsearch();
	}

}

bool comp(int a, int b) {
	if(dr[a] == dr[b])
		return a < b;
	return dr[a] < dr[b];
}

namespace BucketSort {

	struct Node {
		int i;
		int next;
	};

	Node _nodes[MAX_N + 2];
	int at = 1;

	int first[MAX_N + 2];

	void add(int pos, int val) {
		_nodes[at].i = val;
		_nodes[at].next = first[pos];
		first[pos] = at;

		at++;
	}

	int head(int pos) {
		return first[pos];
	}

	int val(int pos) {
		return _nodes[pos].i;
	}

	int next(int pos) {
		return _nodes[pos].next;
	}
}

int main() {
	cin >> n;
	cin >> (s + 1);

	solveForLimits(s, dr);

	reverse(s + 1, s + n + 1);

	solveForLimits(s, _st);
	for(int i = 1; i <= n; ++i) {
		int diff = _st[i] - i;
		int reflection = n - i + 1;

		st[reflection] = reflection - diff;
	}

	/* 
	 * Now for each *i* we would like to find maximal *j*
	 * such that i <= j <= dr[i]
	 * and st[j] <= i
	 */

	for(int i = 1; i <= n; ++i) 
		BucketSort::add(dr[i], i);

	/* the last J which has yet been introduced */
	int lastJ = 1;

	for(int dr = 1; dr <= n; ++dr) {

		while(lastJ <= dr) {
			AIB::update(st[lastJ], lastJ);
			lastJ++;
		}

		for(int idx = BucketSort::head(dr); idx != 0; idx = BucketSort::next(idx)) {
			int i = BucketSort::val(idx);
			ans[i] = AIB::query(i);
		}
	}

	int maxAns = 0;

	for(int i = 1; i <= n; ++i) {
		dprintf("ans[%d] = %d\n", i, ans[i]);
		if(ans[i] < i)
			continue;
		int now = ans[i] - i + 1;
		if(now > maxAns)
			maxAns = now;
	}

	printf("%d\n", maxAns);
	

	return 0;
}
