#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 300;
int n, m, g[10][kMaxN][kMaxN], d[kMaxN][kMaxN], f[kMaxN][kMaxN];

int main() {
	scanf("%d%d", &n, &m);
	memset(g[0], 0x3f, sizeof(g[0]));
	for (int u, v; m --; ) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		scanf("%d%d", &g[0][u][v], &g[0][v][u]);
		g[0][u][v] = -g[0][u][v];
		g[0][v][u] = -g[0][v][u];
	}
	for (int k = 1; k < 10; ++ k) {
		memcpy(g[k], g[k - 1], sizeof(g[k - 1]));
		for (int u = 0; u < n; ++ u)
			for (int v = 0; v < n; ++ v)
				for (int t = 0; t < n; ++ t)
					if (g[k - 1][u][t] + g[k - 1][t][v] < g[k][u][v]) g[k][u][v] = g[k - 1][u][t] + g[k - 1][t][v];
	}
	int ans = 0;
	memset(d, 0x3f, sizeof(d));
	for (int i = 0; i < n; ++ i) d[i][i] = 0;
	for (int k = 9; k >= 0; -- k) {
		memcpy(f, d, sizeof(d));
		for (int u = 0; u < n; ++ u)
			for (int v = 0; v < n; ++ v)
				for (int t = 0; t < n; ++ t)
					if (d[u][t] + g[k][t][v] < f[u][v]) f[u][v] = d[u][t] + g[k][t][v];
		bool found = false;
		for (int i = 0; i < n; ++ i)
			if (f[i][i] < 0) {
				found = true;
				break;
			}
		if (!found) {
			ans |= 1 << k;
			memcpy(d, f, sizeof(f));
		}
	}
	++ ans;
	if (ans > n) printf("%d\n", 0);
	else printf("%d\n", ans);
	return 0;
}
