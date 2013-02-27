#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 100000, kMaxM = (kMaxN - 1) * 2;
int n, cnt, begin[kMaxN], end[kMaxM], next[kMaxM];
double x[kMaxN + 1], y[kMaxN + 1], ans;
int q[kMaxN], qh, qt, sz[kMaxN], pre[kMaxN];
bool vis[kMaxN];

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
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
	for (int i = 0; i < n; ++ i) {
		scanf("%lf%lf", &x[i], &y[i]);
		x[n] += x[i];
		y[n] += y[i];
	}
	for (int i = 0; i < n; ++ i) {
		x[i] /= x[n];
		y[i] /= y[n];
	}
	vis[q[qt ++] = 0] = true;
	pre[0] = -1;
	while (qh < qt) {
		int u = q[qh ++];
		for (int now = begin[u], v; now != -1; now = next[now])
			if (!vis[v = end[now]]) vis[q[qt ++] = v] = true, pre[v] = u;
	}
	for (int i = qt - 1; i >= 0; -- i) {
		int u = q[i];
		++ sz[u];
		if (pre[u] != -1) {
			ans += y[pre[u]] * x[u] * sz[u];
			ans += y[u] * (1.0 - x[u]) * (n - sz[u]);
			sz[pre[u]] += sz[u];
			x[pre[u]] += x[u];
		}
	}
	printf("%.10lf\n", ans);
	return 0;
}
