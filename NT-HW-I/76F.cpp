#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 100000;
int n, v, memo[kMaxN + 1], *dp = memo + 1, memo2[kMaxN + 1], *dp2 = memo2 + 1;
long long seq[kMaxN];
int m;

struct Node {
	int x, t;
	long long a, b;
	bool operator < (const Node &t) const {
		if (a != t.a) return (a > t.a);
		return (b < t.b);
	}
} node[kMaxN];

struct IndexTree {
#define LB(x) ((x) & (-(x)))
	int v[kMaxN + 1], r[kMaxN + 1];
	void add(int i, int d) {
		if (d <= r[i]) return;
		r[i] = d;
		for ( ; i <= m; i += LB(i))
			v[i] = max(v[i], d);
	}
	int sum(int i) {
		int res = 0;
		for ( ; i; i -= LB(i))
			res = max(res, v[i]);
		return res;
	}
#undef LB
} idt, idt2;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d%d", &node[i].x, &node[i].t);
	scanf("%d", &v);
	for (int i = 0; i < n; ++ i) {
		node[i].a = node[i].x - (long long)v * node[i].t;
		node[i].b = node[i].x + (long long)v * node[i].t;
		seq[i] = node[i].b;
	}
	sort(node, node + n);
	sort(seq, seq + n);
	m = unique(seq, seq + n) - seq;
	for (int i = 0; i < n; ++ i) {
		int p = lower_bound(seq, seq + m, node[i].b) - seq;
		dp[i] = 1 + idt.sum(p + 1);
		idt.add(p + 1, dp[i]);
		dp2[i] = idt2.sum(p + 1);
		if (dp2[i] == 0) {
			dp2[i] = (abs(node[i].x) <= (long long)v * node[i].t);
		}
		else ++ dp2[i];
		idt2.add(p + 1, dp2[i]);
	}
	int ans1 = 0, ans2 = 0;
	for (int i = 0; i < n; ++ i) {
		ans2 = max(ans2, dp[i]);
		ans1 = max(ans1, dp2[i]);
	}
	printf("%d %d\n", ans1, ans2);
	return 0;
}
