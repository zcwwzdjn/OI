/*
 * $File: mud.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a tree, choose a root to make the cost
 *   smallest. Each node cost w * d, where w is the
 *   cost of the node, d is the distance to the root.
 *
 * Solution:
 *   Dfs. Do 2 dfs, first to calculate the cost of a subtree,
 *   then calculate the cost of making some vertex root.
 */

#include <cstdio>
#include <cstring>

const int kMaxV = 350 * 500 + 1, kMaxE = kMaxV - 1;
int cnt, begin[kMaxV], end[kMaxE], next[kMaxE], cost[kMaxE];
int n, p[kMaxV];
int l;
int s[kMaxV], f[kMaxV], g[kMaxV], c[kMaxV];
int a[kMaxV], b[kMaxV], w[kMaxV];

void AddEdge(int u, int v, int c) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt] = v;
	cost[cnt ++] = c;
}

void Dfs(int u) {
	s[u] = p[u];
	for (int now = begin[u], v; now != -1; now = next[now]) {
		Dfs(v = end[now]);
		s[u] += s[v];
		f[u] += f[v] + s[v] * cost[now];
	}
}

void Dfs(int u, int h) {
	g[u] = f[u] + h;
	int tmp = 0;
	for (int now = begin[u], v; now != -1; now = next[now]) {
		v = end[now];
		c[v] = f[v] + s[v] * cost[now];
		tmp += c[v];
	}
	for (int now = begin[u], v; now != -1; now = next[now]) {
		v = end[now];
		Dfs(v, h + (s[0] - s[v]) * cost[now] + tmp - c[v]);
	}
}

int main() {
	memset(begin, -1, sizeof(begin));
	scanf("%d%d", &l, &p[0]);
	n = 1;
	for (int i = 0, x, y, z; i < l; ++ i) {
		int pre = 0;
		scanf("%d", &x);
		while (x --) {
			scanf("%d%d", &y, &z);
			p[n] = z;
			AddEdge(pre, n, y);
			a[n] = i + 1, b[n] = b[pre] + 1, w[n] = y;
			pre = n ++;
		}
	}
	Dfs(0);
	Dfs(0, 0);
	int res = 0x3f3f3f3f, rec;
	for (int i = 0; i < n; ++ i) {
		if (g[i] < res) {
			res = g[i];
			rec = i;
		}
	}
	printf("%d\n%d %d\n", res, a[rec], b[rec]);
	return 0;
}
