/*
 * $File: gon.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a connected graph, A is at vertex
 *   a and B is at vertex b, and they play a
 *   game, in each turn A and B can move at
 *   most 1 step, and A moves first.
 *   Find if B can chase A in finite steps.
 *   If so, find the maximal steps A can prevent
 *   himself from being chased.
 *
 * Solution:
 *   Firstly we can find out that some blocks
 *   are 'safe' for A, if A can reach these
 *   vertices before B, then B can not reach A.
 *   We can see that BCCs are 'safe'. The vertices
 *   between BCCs are 'safe' too. Then we
 *   just calculate the distances from a to other
 *   vertices and from b to other vertices.
 *   The last thing is simple comparison.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 3000, kMaxM = 30000;
int n, m, a, b;
int cnt, begin[kMaxN], end[kMaxM], next[kMaxM];
bool vis[kMaxN];
int q[kMaxN], qh, qt, deg[kMaxN];
int da[kMaxN], db[kMaxN];

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

void Find(int s, int *d) {
	qh = qt = 0;
	d[q[qt ++] = s] = 0;
	while (qh < qt) {
		int u = q[qh ++];
		for (int now = begin[u], v; now != -1; now = next[now])
			if (d[v = end[now]] > d[u] + 1) d[q[qt ++] = v] = d[u] + 1;
	}
}

int main() {
	memset(begin, -1, sizeof(begin));
	scanf("%d%d%d%d", &n, &m, &a, &b);
	-- a, -- b;
	for (int u, v; m --; ) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		AddEdge(u, v);
		AddEdge(v, u);
		++ deg[u], ++ deg[v];
	}
	for (int i = 0; i < n; ++ i)
		if (deg[i] == 1) q[qt ++] = i;
	while (qh < qt) {
		int u = q[qh ++];
		vis[u] = true;
		for (int now = begin[u], v; now != -1; now = next[now])
			if ((-- deg[v = end[now]]) == 1) q[qt ++] = v;
	}
	memset(da, 0x3f, sizeof(da)), Find(a, da);
	memset(db, 0x3f, sizeof(db)), Find(b, db);
	for (int i = 0; i < n; ++ i)
		if (!vis[i] && da[i] < db[i]) {
			puts("NIE");
			return 0;
		}
	int res = 0;
	for (int i = 0; i < n; ++ i)
		if (da[i] < db[i]) res = max(res, db[i]);
	printf("%d\n", res);
	return 0;
}
