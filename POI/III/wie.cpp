/*
 * $File: wie.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a N * N chess board, try to put
 *   N rooks on it, and the rook i is supposed
 *   to be placed in a given rectangle Ri.
 *   Find a solution.
 *
 * Solution:
 *   The X-axis and Y-axis have no connections.
 *   So the task is like this: given N segments,
 *   and N points, for every point decide which
 *   segment it belongs to. We can do it greedily.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 3000;
int n, ans[kMaxN][2];

struct Node {
	int l, r, d;
	Node() {}
	Node(int l_, int r_, int d_) : l(l_), r(r_), d(d_) {}
	bool operator < (const Node &t) const {
		return (r < t.r);
	}
} x[kMaxN], y[kMaxN];

bool Solve(Node *s, int t) {
	sort(s, s + n);
	for (int i = 0; i < n; ++ i) {
		bool found = false;
		for (int j = 0; j < n; ++ j)
			if (ans[s[j].d][t] == -1 && i >= s[j].l && i <= s[j].r) {
				ans[s[j].d][t] = i;
				found = true;
				break;
			}
		if (!found) return false;
	}
	return true;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d%d%d%d", &x[i].l, &y[i].l, &x[i].r, &y[i].r);
		-- x[i].l, -- y[i].l, -- x[i].r, -- y[i].r;
		x[i].d = y[i].d = i;
	}
	memset(ans, -1, sizeof(ans));
	bool has_res = Solve(x, 0) & Solve(y, 1);
	if (!has_res) puts("NIE");
	else {
		for (int i = 0; i < n; ++ i) printf("%d %d\n", ans[i][0] + 1, ans[i][1] + 1);
	}
	return 0;
}
