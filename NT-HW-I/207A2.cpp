#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 5000, kMaxM = 200000;
int n;

struct Triple {
	int a, b, c;
	Triple() {}
	Triple(int a_, int b_, int c_) : a(a_), b(b_), c(c_) {}
	bool operator > (const Triple &t) const {
		if (a != t.a) return (a > t.a);
		if (b != t.b) return (b > t.b);
		return (c > t.c);
	}
};

priority_queue<Triple, vector<Triple>, greater<Triple> > heap;

int main() {
	scanf("%d", &n);
	int sz = 0, res = 0;
	for (int i = 0; i < n; ++ i) {
		int k, a, x, y, m;
		scanf("%d%d%d%d%d", &k, &a, &x, &y, &m);
		int pre = 0;
		for (int j = 0, c = 0; j < k; ++ j) {
			if (a < pre) res = max(res, ++ c);
			pre = a;
			++ sz;
			if (sz <= kMaxM) heap.push(Triple(c, a, i));
			a = ((long long)a * x + y) % m;
		}
	}
	printf("%d\n", res);
	if (sz <= kMaxM)
		while (heap.size()) {
			printf("%d %d\n", heap.top().b, heap.top().c + 1);
			heap.pop();
		}
	return 0;
}
