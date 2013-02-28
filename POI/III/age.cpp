/*
 * $File: age.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a directed graph, each vertex
 *   has a cost. If we pay for a vertex,
 *   we can reach all vertices it can reach
 *   for free. Find the minimal cost.
 *
 * Solution:
 *   Do Tarjan to find SCC. From every block
 *   whose in degree equals 0, we just need to
 *   choose a minimal cost to pay.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 3000, kMaxM = 8000, kInf = 0x3f3f3f3f;
int n, p, cost[kMaxN], m;
int cnt, begin[kMaxN], end[kMaxM], next[kMaxM];
int ind[kMaxN];

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

int dcnt, bcnt, dfn[kMaxN], low[kMaxN], bel[kMaxN], stack[kMaxN], stop;
bool ins[kMaxN];
int w[kMaxN];

void Dfs(int u) {
	ins[stack[stop ++] = u] = true;
	low[u] = dfn[u] = ++ dcnt;
	for (int now = begin[u], v; now != -1; now = next[now])
		if (!dfn[v = end[now]]) {
			Dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else if (ins[v])
			low[u] = min(low[u], dfn[v]);
	if (low[u] == dfn[u]) {
		do {
			ins[stack[stop - 1]] = false;
			bel[stack[stop - 1]] = bcnt;
			w[bcnt] = min(w[bcnt], cost[stack[stop - 1]]);
		} while (stack[-- stop] != u);
		++ bcnt;
	}
}

int main() {
	scanf("%d%d", &n, &p);
	memset(cost, 0x3f, sizeof(cost));
	for (int x, y; p --; ) {
		scanf("%d%d", &x, &y);
		-- x;
		cost[x] = min(cost[x], y);
	}
	scanf("%d", &m);
	memset(begin, -1, sizeof(begin));
	for (int u, v; m --; ) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		AddEdge(u, v);
	}
	memset(w, 0x3f, sizeof(w));
	for (int i = 0; i < n; ++ i)
		if (!dfn[i]) Dfs(i);
	for (int u = 0; u < n; ++ u)
		for (int now = begin[u], v; now != -1; now = next[now])
			if (bel[u] != bel[v = end[now]]) ++ ind[bel[v]];
	int res = 0;
	for (int i = 0; i < bcnt; ++ i)
		if (ind[i] == 0) {
			if (w[i] == kInf) {
				int u = 0;
				while (bel[u] != i || cost[u] != kInf) ++ u;
				printf("NIE\n%d\n", u + 1);
				return 0;
			}
			res += w[i];
		}
	printf("TAK\n%d\n", res);
	return 0;
}
