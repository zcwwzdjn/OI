#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int kMaxN = 600, kMaxM = 100000;
int n, m, p;
int cnt, begin[kMaxN], end[kMaxM], next[kMaxM];
int ind[kMaxN], oud[kMaxN];
int source[kMaxN], sink[kMaxN];
int dp[kMaxN], q[kMaxN], qh, qt;
int mat[kMaxN][kMaxN];
bool vis[kMaxN];
int d[kMaxN];

#define ADD(x, y) { \
	(x) += (y); \
	if ((x) >= p) (x) -= p; \
}

#define DEC(x, y) { \
	(x) -= (y); \
	if ((x) < 0) (x) += p; \
}

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

int PowerMod(int a, int b) {
	int res = 1, tmp = a;
	while (b) {
		if (b & 1) res = (ll)res * tmp % p;
		b >>= 1;
		tmp = (ll)tmp * tmp % p;
	}
	return res;
}

int Solve() {
	int res = 1;
	for (int i = 0, j = 0, k; i < m; ++ i, ++ j) {
		for (k = j; k < m; ++ k)
			if (mat[k][i]) break;
		if (k == m) continue;
		if (k != j) {
			for (int l = i; l < m; ++ l) ADD(mat[j][l], mat[k][l]);
		}
		for (k = j + 1; k < m; ++ k)
			if (mat[k][i]) {
				int t = mat[k][i];
				res = (ll)res * mat[j][i] % p;
				for (int l = i; l < m; ++ l) {
					mat[k][l] = (ll)mat[k][l] * mat[j][i] % p;
					DEC(mat[k][l], (ll)t * mat[j][l] % p);
				}
			}
	}
	return res;
}

void Dfs(int u) {
	if (vis[u]) return;
	vis[u] = true;
	for (int now = begin[u], v; now != -1; now = next[now]) {
		++ d[v = end[now]];
		Dfs(v);
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &p);
	memset(begin, -1, sizeof(begin));
	for (int u, v; m --; ) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		AddEdge(v, u);
		++ oud[u], ++ ind[v];
	}
	int t;
	t = 0;
	for (int i = 0; i < n; ++ i)
		if (ind[i] == 0) source[t ++] = i;
	t = 0;
	for (int i = 0; i < n; ++ i)
		if (oud[i] == 0) sink[t ++] = i;
	m = t;
	for (int i = 0; i < m; ++ i) {
		memset(d, 0, sizeof(d));
		memset(vis, false, sizeof(vis));
		Dfs(sink[i]);
		qh = qt = 0;
		memset(dp, 0, sizeof(dp));
		dp[q[qt ++] = sink[i]] = 1;
		while (qh < qt) {
			int u = q[qh ++];
			for (int now = begin[u], v; now != -1; now = next[now]) {
				if (!(-- d[v = end[now]])) q[qt ++] = v;
				ADD(dp[v], dp[u]);
			}
		}
		for (int j = 0; j < m; ++ j) mat[i][j] = dp[source[j]];
	}
	int div = Solve();
	int res = 1;
	for (int i = 0; i < m; ++ i) res = (ll)res * mat[i][i] % p;
	res = (ll)res * PowerMod(div, p - 2) % p;
	printf("%d\n", res);
	return 0;
}
