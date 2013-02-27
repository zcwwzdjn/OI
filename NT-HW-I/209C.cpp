#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <algorithm>

using namespace std;

const int kMaxN = 1000000;
int n, m, deg[kMaxN], root[kMaxN];
int mark[kMaxN], cnt[kMaxN];
pair<int, int> e[kMaxN];

int Root(int x) {
	return (x == root[x] ? x : root[x] = Root(root[x]));
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i) root[i] = i;
	for (int u, v; m --; ) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		++ deg[u], ++ deg[v];
		u = Root(u), v = Root(v);
		root[u] = v;
	}
	memset(mark, -1, sizeof(mark));
	m = 0;
	for (int i = 0; i < n; ++ i) {
		int u = Root(i);
		if (mark[u] == -1) mark[u] = m ++;
		if (deg[i] & 1) ++ e[mark[u]].first;
		else ++ e[mark[u]].second;
		cnt[mark[u]] += deg[i];
	}
	int nm = 0;
	for (int i = 0; i < m; ++ i)
		if (cnt[i] || mark[Root(0)] == i) e[nm ++] = e[i];
	m = nm;
	sort(e, e + m);
	int res = 0;
	if (m > 1) {
		for (int i = m - 1; i >= 0; -- i) {
			int j = (i - 1 + m) % m;
			if (e[i].first) {
				-- e[i].first;
				++ e[i].second;
			}
			else {
				++ e[i].first;
				-- e[i].second;
			}
			if (e[j].first) {
				-- e[j].first;
				++ e[j].second;
			}
			else {
				++ e[j].first;
				-- e[j].second;
			}
			++ res;
		}
	}
	int tmp = 0;
	for (int i = 0; i < m; ++ i) tmp += e[i].first;
	res += (tmp + 1) / 2;
	printf("%d\n", res);
	return 0;
}
