/*
 * $File: sza.cpp
 * $Author: Wayne <tletletle@163.com>
 *
 * Task:
 *   Given a N * N Matrix with exactly 3 cells
 *   blocked, find a perfect match.
 *
 * Solution:
 *   Find a match greedily, then do hungry algo.
 */

#include <cstdio>
#include <cstring>

const int kMaxV = 49 * 49, kMaxE = kMaxV * 4;
const int kFx[4] = {-1, 1, 0, 0}, kFy[4] = {0, 0, -1, 1};
int cnt, begin[kMaxV], end[kMaxE], next[kMaxE];
bool ban[kMaxV];
int n;
int res[kMaxV], col[kMaxV];
bool vis[kMaxV], done[kMaxV];

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

bool Dfs(int u) {
	for (int now = begin[u], v; now != -1; now = next[now])
		if (!vis[v = end[now]]) {
			vis[v] = true;
			if (res[v] == -1 || Dfs(res[v])) {
				res[v] = u;
				return true;
			}
		}
	return false;
}

int main() {
	scanf("%d", &n);
	for (int i = 0, x; i < 3; ++ i) {
		scanf("%d", &x);
		-- x;
		ban[x] = true;
	}
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < n; ++ j)
			col[i * n + j] = (i + j) & 1;
	memset(res, -1, sizeof(res));
	memset(begin, -1, sizeof(begin));
	int mat = 0;
	for (int i = 0; i < n * n; ++ i)
		if (!col[i] && !ban[i]) {
			for (int d = 0; d < 4; ++ d) {
				int x = (i / n) + kFx[d];
				int y = (i % n) + kFy[d];
				if (x >= 0 && x < n && y >= 0 && y < n && !ban[x * n + y] && res[x * n + y] == -1) {
					res[x * n + y] = i;
					++ mat;
					done[i] = true;
					break;
				}
			}
			for (int d = 0; d < 4; ++ d) {
				int x = (i / n) + kFx[d];
				int y = (i % n) + kFy[d];
				if (x >= 0 && x < n && y >= 0 && y < n && !ban[x * n + y])
					AddEdge(i, x * n + y);
			}
		}
	for (int i = 0; i < n * n; ++ i)
		if (!done[i]) {
			memset(vis, false, sizeof(vis));
			if (Dfs(i)) ++ mat;
		}
	if (mat != (n * n - 3) / 2) puts("NIE");
	else
		for (int i = 0; i < n * n; ++ i)
			if (res[i] != -1) printf("%d %d\n", res[i] + 1, i + 1);
	return 0;
}
