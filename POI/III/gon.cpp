/*
 * $File: gon.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a graph, and we can assume that
 *   from u to v there exist at least 2 paths.
 *   Start from vertex 1, we travel through
 *   the graph. In each move we can go to a
 *   vertex which is next to one that we've 
 *   visited. And we should make it legal when
 *   reverse the travel sequence.
 *
 * Solution:
 *   Choose 2 vertices that is next to vertex 1.
 *   Let them be a, b. We start something similar
 *   to bfs, start from a and at the same time
 *   start from b, and make the degree of b in the
 *   tree exactly 1. Then we just combine the
 *   two travel sequence.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 500;
int n, m;
vector<int> to[kMaxN];
bool vis[kMaxN], tmp[kMaxN];
vector<int> p, q, s, t;
vector<int> tp[kMaxN], tq[kMaxN];

void Dfs(int u) {
	if (u == q[0]) return;
	vis[u] = true;
	s.push_back(u);
	for (int i = 0; i < (int)tq[u].size(); ++ i)
		if (!vis[tq[u][i]]) Dfs(tq[u][i]);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int u, v; m --; ) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		to[u].push_back(v);
		to[v].push_back(u);
	}
	vis[0] = true;
	int a = to[0][0], b = to[0][1];
	vis[a] = vis[b] = true;
	p.push_back(a);
	q.push_back(b);
	while (true) {
		bool pf = false, qf = false;
		for (int j = 0; j < (int)p.size(); ++ j) {
			a = p[j];
			for (int i = 0; i < (int)to[a].size(); ++ i)
				if (!vis[to[a][i]]) {
					tp[a].push_back(to[a][i]);
					tp[to[a][i]].push_back(a);
					a = to[a][i];
					vis[a] = true;
					pf = true;
					p.push_back(a);
					break;
				}
			if (pf) break;
		}
		for (int j = ((int)q.size() != 1); j < (int)q.size(); ++ j) {
			b = q[j];
			for (int i = 0; i < (int)to[b].size(); ++ i)
				if (!vis[to[b][i]]) {
					tq[b].push_back(to[b][i]);
					tq[to[b][i]].push_back(b);
					b = to[b][i];
					vis[b] = true;
					qf = true;
					q.push_back(b);
					break;
				}
			if (qf) break;
		}
		if (!pf && !qf) break;
	}
	memset(vis, false, sizeof(vis));
	vis[0] = true;
	for (int i = 0; i < (int)p.size(); ++ i) {
		s.push_back(p[i]);
		vis[p[i]] = true;
	}
	for (int j = 0; j < (int)p.size(); ++ j) {
		int a = p[j];
		bool found = false;
		for (int i = 0; i < (int)to[a].size(); ++ i)
			if (!vis[to[a][i]] && to[a][i] != q[0]) {
				b = to[a][i];
				t = s;
				memcpy(tmp, vis, sizeof(vis));
				Dfs(b);
				if ((int)s.size() != n - 2) s = t, memcpy(vis, tmp, sizeof(tmp));
				else {
					found = true;
					break;
				}
			}
		if (found) break;
	}
	s.push_back(q[0]);
	printf("1");
	for (int i = 0; i < (int)s.size(); ++ i) printf(" %d", s[i] + 1);
	printf("\n1");
	for (int i = (int)s.size() - 1; i >= 0; -- i) printf(" %d", s[i] + 1);
	puts("");
	return 0;
}
