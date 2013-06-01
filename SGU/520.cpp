#include <cstdio>
#include <cstring>

const int kMaxN = 1000, kMaxM = 2000;
int n, m, cnt, begin[kMaxN], end[kMaxM], next[kMaxM];
int dep[kMaxN];

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

bool Dfs(int u) {
	static bool memo[kMaxN];
	static bool done[kMaxN];
	if (done[u]) return memo[u];
	done[u] = true;
	bool &res = memo[u];
	res = false;
	for (int now = begin[u], v; now != -1; now = next[now])
		if (dep[v = end[now]] == dep[u] + 1) {
			if (!Dfs(v)) {
				res = true;
				break;
			}
		}
	return res;
}

int main() {
	scanf("%d%d", &n, &m);
	memset(begin, -1, sizeof(begin));
	for (int u, v; m --; ) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		AddEdge(u, v);
		AddEdge(v, u);
	}
	static int q[kMaxN], qh, qt;
	static bool vis[kMaxN];
	vis[q[qt ++] = 0] = true;
	while (qh != qt) {
		int u = q[qh ++];
		for (int now = begin[u], v; now != -1; now = next[now])
			if (!vis[v = end[now]]) {
				vis[q[qt ++] = v] = true;
				dep[v] = dep[u] + 1;
			}
	}
	puts(Dfs(0) ? "Vladimir" : "Nikolay");
	return 0;
}
