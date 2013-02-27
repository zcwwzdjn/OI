#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 200, kMaxM = 50000;
int n, m, g, s;
int pre[kMaxN], vis[kMaxN], w[kMaxN];

struct Dsu {
	int root[kMaxN];
	void init() {
		for (int i = 0; i < n; ++ i) root[i] = i;
	}
	int find(int x) {
		return (x == root[x] ? x : root[x] = find(root[x]));
	}
	void merge(int a, int b) {
		root[a] = b;
	}
} ds;

struct Edge {
	int u, v, g, s;
	bool operator < (const Edge &t) const {
		if (g != t.g) return (g < t.g);
		return (s < t.s);
	}
} e[kMaxM];

int main() {
	scanf("%d%d%d%d", &n, &m, &g, &s);
	for (int i = 0; i < m; ++ i) {
		scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].g, &e[i].s);
		-- e[i].u, -- e[i].v;
	}
	sort(e, e + m);
	ds.init();
	memset(pre, -1, sizeof(pre));
	memset(vis, -1, sizeof(vis));
	long long ans = LONG_LONG_MAX;
	int cnt = n;
	for (int i = 0; i < m; ++ i) {
		static int far[kMaxN];
		static long long raf[kMaxN];
		int u = e[i].u, v = e[i].v;
		int ru = ds.find(u), rv = ds.find(v);
		if (ru != rv) {
			-- cnt;
			ds.merge(ru, rv);
			int idx = 0;
			for (int t = v; t != -1; t = pre[t]) {
				raf[idx] = w[t];
				far[idx ++] = t;
			}
			pre[v] = u;
			w[v] = e[i].s;
			for (int j = 0; j < idx - 1; ++ j) {
				pre[far[j + 1]] = far[j];
				w[far[j + 1]] = raf[j];
			}
		}
		else {
			for (int t = u; t != -1; t = pre[t]) vis[t] = i;
			int lca;
			for (int t = v; t != -1; t = pre[t])
				if (vis[t] == i) {
					lca = t;
					break;
				}
			long long p = 0;
			int q, b;
			for (int t = u; t != lca; t = pre[t])
				if (w[t] > p) {
					p = w[t];
					q = t;
					b = 0;
				}
			for (int t = v; t != lca; t = pre[t])
				if (w[t] > p) {
					p = w[t];
					q = t;
					b = 1;
				}
			if (p > e[i].s) {
				if (b == 1) swap(u, v);
				int idx = 0;
				for (int t = u; t != pre[q]; t = pre[t]) {
					raf[idx] = w[t];
					far[idx ++] = t;
				}
				pre[u] = v;
				w[u] = e[i].s;
				for (int j = 0; j < idx - 1; ++ j) {
					pre[far[j + 1]] = far[j];
					w[far[j + 1]] = raf[j];
				}
			}
		}
		if (cnt == 1) {
			int maxs = 0;
			for (int j = 0; j < n; ++ j)
				maxs = max(maxs, w[j]);
			ans = min(ans, (long long)g * e[i].g + (long long)s * maxs);
		}
	}
	if (ans == LONG_LONG_MAX) puts("-1");
	else printf("%I64d\n", ans);
	return 0;
}
