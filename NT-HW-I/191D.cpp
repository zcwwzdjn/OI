#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 100000, kMaxM = 600000;
int n, m, cnt, begin[kMaxN], end[kMaxM], next[kMaxM], deg[kMaxN];
int dcnt, bcnt, dfn[kMaxN], low[kMaxN], belong[kMaxN], stack[kMaxN], stop;
bool used[kMaxM], bridge[kMaxM];
vector<int> block[kMaxN];

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

void Tarjan(int u) {
	low[u] = dfn[u] = ++ dcnt;
	for (int now = begin[u], v; now != -1; now = next[now])
		if (!used[now]) {
			used[now] = used[now ^ 1] = true;
			if (!dfn[v = end[now]]) {
				Tarjan(v);
				low[u] = min(low[u], low[v]);
				if (low[v] > dfn[u]) bridge[now] = bridge[now ^ 1] = true;
			}
			else
				low[u] = min(low[u], dfn[v]);
		}
}

void Dfs(int u) {
	if (belong[u] != -1) return;
	belong[u] = bcnt;
	block[bcnt].push_back(u);
	for (int now = begin[u]; now != -1; now = next[now])
		if (!bridge[now]) Dfs(end[now]);
}

int main() {
	memset(begin, -1, sizeof(begin));
	scanf("%d%d", &n, &m);
	for (int u, v, i = 0; i < m; ++ i) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		AddEdge(u, v);
		AddEdge(v, u);
		++ deg[u];
		++ deg[v];
	}
	for (int i = 0; i < n; ++ i)
		if (!dfn[i]) Tarjan(i);
	memset(belong, -1, sizeof(belong));
	for (int i = 0; i < n; ++ i)
		if (belong[i] == -1) {
			Dfs(i);
		   	++ bcnt;
		}
	int ans = 0;
	for (int i = 0; i < n; ++ i) ans += deg[i] & 1;
	ans >>= 1;
	for (int i = 0; i < bcnt; ++ i)
		if (int(block[i].size()) > 1) {
			int cnt = 0;
			for (int j = 0; j < int(block[i].size()); ++ j) cnt += (deg[block[i][j]] > 2);
			ans += (cnt < 2);
		}
	printf("%d %d\n", ans, m);
	return 0;
}
