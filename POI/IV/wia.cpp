/*
 * $File: wia.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a agreement directed graph and
 *   a disagreement directed graph, and we
 *   know if i agree with j, j agree with k,
 *   then i agree with k, and if i agree with j,
 *   j disagree with k, then i disagree with k.
 *   Find all x, that we can find a y satisfied
 *   that x agree with y and x disagree with y.
 *
 * Solution:
 *   Just a simple bfs.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 3000, kMaxM = 8000;
int n, m;
vector<int> a[kMaxN], b[kMaxN];
int vis[kMaxN], dcnt;
int q[kMaxN], qh, qt;

bool Check(int u) {
	++ dcnt;
	qh = qt = 0;
	vis[q[qt ++] = u] = dcnt;
	while (qh < qt) {
		int u = q[qh ++];
		for (vector<int>::iterator it = a[u].begin(); it != a[u].end(); ++ it) {
			int v = *it;
			if (vis[v] != dcnt) {
				vis[v] = dcnt;
				q[qt ++] = v;
			}
		}
	}
	for (int i = 0; i < qt; ++ i) {
		int u = q[i];
		for (vector<int>::iterator it = b[u].begin(); it != b[u].end(); ++ it)
			if (vis[*it] == dcnt) return false;
	}
	return true;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int u, v; m --; ) {
		scanf("%d%d", &u, &v);
		-- u;
		if (v > 0)
			a[u].push_back(v - 1);
		else
			b[u].push_back(-v - 1);
	}
	bool out = false;
	for (int i = 0; i < n; ++ i)
		if (!Check(i)) {
			printf("%d\n", i + 1);
			out = true;
		}
	if (!out) printf("NIKT\n");
	return 0;
}
