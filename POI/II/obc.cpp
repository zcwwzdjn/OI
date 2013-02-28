/*
 * $File: obc.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a tree, return a sequence that
 *   satisfied the distance between each 
 *   consecutive 2 vertices not more than 3.
 *
 * Solution:
 *   Just do a dfs, but when at a even depth,
 *   out before iterate next vertices, and
 *   when at odd, iterate first.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 5000, kMaxM = (kMaxN - 1) * 2;
int n, cnt, begin[kMaxN], end[kMaxM], next[kMaxM];

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

void Dfs(int u, int p, int d) {
	if (d == 0) {
		printf("%d\n", u + 1);
		for (int now = begin[u], v; now != -1; now = next[now])
			if ((v = end[now]) != p) Dfs(v, u, 1);
	}
	else {
		for (int now = begin[u], v; now != -1; now = next[now])
			if ((v = end[now]) != p) Dfs(v, u, 0);
		printf("%d\n", u + 1);
	}
}

int main() {
	memset(begin, -1, sizeof(begin));
	scanf("%d", &n);
	for (int u, v, i = 0; i < n - 1; ++ i) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		AddEdge(u, v);
		AddEdge(v, u);
	}
	Dfs(0, -1, 0);
	return 0;
}
