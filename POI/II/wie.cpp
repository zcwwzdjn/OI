/*
 * $File: wie.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a convex hull with some diagonals
 *   that do not intersect. Find the block of
 *   maximal edges.
 *
 * Solution:
 *   Just like finding blocks in a graph.
 *   Maybe there's some more efficient algo.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 5000;
int n, m;
vector<int> to[kMaxN];
vector<bool> used[kMaxN];
int ans;
bool out = false;

void Dfs(int u, int v, int l, int s, int t) {
	if (l && u == s && v == t) {
		if (l == n) {
			if (!out) out = true;
			else ans = max(ans, l);
		}
		else ans = max(ans, l);
		return;
	}
	int i = 0;
	while (to[v][i] != u) ++ i;
	int k = to[v].size();
	i = (i + 1) % k;
	while (used[v][i]) {
		++ i;
		if (i >= k) i -= k;
	}
	used[v][i] = true;
	Dfs(v, to[v][i], l + 1, s, t);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i) {
		to[i].push_back((i + 1) % n);
		to[i].push_back((i - 1 + n) % n);
	}
	for (int u, v; m --; ) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		to[u].push_back(v);
		to[v].push_back(u);
	}
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < (int)to[i].size(); ++ j)
			if (to[i][j] < i) to[i][j] += n;
		sort(to[i].begin(), to[i].end());
		reverse(to[i].begin(), to[i].end());
		for (int j = 0; j < (int)to[i].size(); ++ j)
			if (to[i][j] >= n) to[i][j] -= n;
		used[i].resize(to[i].size());
	}
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < (int)to[i].size(); ++ j)
			if (!used[i][j]) {
				Dfs(i, to[i][j], 0, i, to[i][j]);
			}
	printf("%d\n", ans);
	return 0;
}
