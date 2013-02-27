#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;
const int kMaxN = 100000, kMaxM = (kMaxN - 1) * 2;
int n, q, cnt, begin[kMaxN], end[kMaxM], next[kMaxM], cost[kMaxM];
int pos[kMaxN], dfn[kMaxN], dcnt, anc[17][kMaxN], sz[kMaxN], dep[kMaxN];
ll sum[kMaxN], ans;
set<int> bst;

void AddEdge(int u, int v, int c) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt] = v;
	cost[cnt ++] = c;
}

void Bfs() {
	static int q[kMaxN], qh, qt;
	qh = qt = 0;
	q[qt ++] = 0;
	while (qh < qt) {
		int u = q[qh ++];
		for (int now = begin[u], v; now != -1; now = next[now])
			if (anc[0][u] != (v = end[now])) {
				anc[0][v] = u;
				sum[v] = sum[u] + cost[now];
				dep[v] = dep[u] + 1;
				q[qt ++] = v;
			}
	}
	for (int i = n - 1; i >= 0; -- i) {
		int u = q[i];
		++ sz[u];
		if (anc[0][u] != -1)
			sz[anc[0][u]] += sz[u];
	}
	for (int i = 0; i < n; ++ i) {
		int u = q[i];
		++ dfn[u];
		int tmp = dfn[u];
		for (int now = begin[u], v; now != -1; now = next[now])
			if (anc[0][u] != (v = end[now])) {
				dfn[v] = tmp;
				tmp += sz[v];
			}
	}
	for (int j = 1; j < 17; ++ j)
		for (int i = 0; i < n; ++ i)
			if (anc[j - 1][i] != -1) anc[j][i] = anc[j - 1][anc[j - 1][i]];
	for (int i = 0; i < n; ++ i) {
		-- dfn[i];
		pos[dfn[i]] = i;
	}
}

int Lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int delta = dep[u] - dep[v];
	for (int j = 16; j >= 0; -- j)
		if (delta >> j & 1) u = anc[j][u];
	for (int j = 16; j >= 0; -- j)
		if (anc[j][u] != anc[j][v]) u = anc[j][u], v = anc[j][v];
	if (u != v) u = anc[0][u];
	return u;
}

ll Val(int u, int v) {
	int p = Lca(u, v);
	return (sum[v] - sum[p]);
}

void Solve(set<int>::iterator it, int u, int sgn) {
	set<int>::iterator prev = it, succ = it;
	++ succ;
	bool has_prev = (it != bst.begin());
	bool has_succ = (succ != bst.end());
	if (has_prev) {
		-- prev;
		if (has_succ) {
			int p = pos[*prev], s = pos[*succ];
			ans -= Val(p, s) * sgn;
			ans += (Val(p, u) + Val(u, s)) * sgn;
		}
		else {
			int p = pos[*prev];
			ans += Val(p, u) * sgn;
		}
	}
	else {
		if (has_succ) {
			int s = pos[*succ];
			ans += Val(u, s) * sgn;
		}
	}
}

int main() {
	scanf("%d", &n);
	memset(begin, -1, sizeof(begin));
	for (int u, v, c, i = 0; i < n - 1; ++ i) {
		scanf("%d%d%d", &u, &v, &c);
		-- u, -- v;
		AddEdge(u, v, c);
		AddEdge(v, u, c);
	}
	memset(anc, -1, sizeof(anc));
	Bfs();
	scanf("%d", &q);
	while (q --) {
		static char cmd[2];
		static int u;
		scanf("%s", cmd);
		if (cmd[0] == '+') {
			scanf("%d", &u);
			-- u;
			set<int>::iterator it = bst.insert(dfn[u]).first;
			Solve(it, u, 1);
		}
		else if (cmd[0] == '-') {
			scanf("%d", &u);
			-- u;
			set<int>::iterator it = bst.lower_bound(dfn[u]);
			Solve(it, u, -1);
			bst.erase(it);
		}
		else {
			ll add = 0LL;
			if (bst.size() >= 2) {
				add = Val(pos[*bst.rbegin()], pos[*bst.begin()]);
			}
			printf("%I64d\n", ans + add);
		}
	}
	return 0;
}
