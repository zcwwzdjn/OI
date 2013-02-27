#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 10000, kMaxM = 20000;
int n, m, cnt, begin[kMaxN], end[kMaxM], next[kMaxM];
vector<pair<int, int> > tr[kMaxN + 1];
bool vis[kMaxN], on[kMaxM];
int lb[kMaxN + 1], rb[kMaxN + 1], dcnt;
int col[kMaxN + 1], dep[kMaxN + 1];
int anc[14][kMaxN + 1];
vector<int> ans;

struct IndexTree {
#define LB(x) ((x) & (-(x)))
	int node[(kMaxN + 1) * 2 + 2];
	void add(int i, int d) {
		for ( ; i <= dcnt + 1; i += LB(i)) node[i] += d;
	}
	int sum(int i) {
		int res = 0;
		for ( ; i; i -= LB(i)) res += node[i];
		return res;
	}
#undef LB
} a, b;

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

void Dfs(int u) {
	if (vis[u]) return;
	vis[u] = true;
	for (int now = begin[u], v; now != -1; now = next[now])
		if (!vis[v = end[now]]) {
			tr[u].push_back(make_pair(v, now >> 1));
			on[now] = on[now ^ 1] = true;
			Dfs(v);
		}
}

void GetColor(int u, int c) {
	col[u] = c;
	lb[u] = ++ dcnt;
	for (vector<pair<int, int> >::iterator it = tr[u].begin(); it != tr[u].end(); ++ it) {
		anc[0][it->first] = u;
		dep[it->first] = dep[u] + 1;
		GetColor(it->first, c ^ 1);
	}
	rb[u] = ++ dcnt;
}

int Lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int d = dep[u] - dep[v];
	for (int j = 13; j >= 0; -- j)
		if (d >> j & 1) u = anc[j][u];
	for (int j = 13; j >= 0; -- j)
		if (anc[j][u] != anc[j][v]) u = anc[j][u], v = anc[j][v];
	if (u != v) u = anc[0][u];
	return u;
}

int main() {
	memset(begin, -1, sizeof(begin));
	scanf("%d%d", &n, &m);
	for (int u, v; m --; ) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		AddEdge(u, v), AddEdge(v, u);
	}
	for (int i = 0; i < n; ++ i)
		if (!vis[i]) {
			Dfs(i);
			tr[n].push_back(make_pair(i, -1));
		}
	memset(anc, -1, sizeof(anc));
	GetColor(n, 0);
	for (int j = 1; j < 14; ++ j)
		for (int i = 0; i <= n; ++ i)
			if (anc[j - 1][i] != -1) anc[j][i] = anc[j - 1][anc[j - 1][i]];
	int err = 0;
	for (int i = 0; i < cnt; i += 2) {
		int u = end[i], v = end[i ^ 1];
		if (col[u] == col[v]) ++ err;
	}
	if (err == 0) {
		for (int i = 0; i < cnt; i += 2)
			if (!on[i]) ans.push_back(i >> 1);
	}
	else if (err == 1) {
		for (int i = 0; i < cnt; i += 2)
			if (col[end[i]] == col[end[i ^ 1]]) ans.push_back(i >> 1);
	}
	int nerr = 0;
	for (int i = 0; i < cnt; i += 2)
		if (col[end[i]] != col[end[i ^ 1]] && !on[i]) ++ nerr;
	for (int i = 0; i < cnt; i += 2)
		if (!on[i]) {
			int u = end[i], v = end[i ^ 1], p = Lca(u, v);
			if (col[u] == col[v]) {
				a.add(lb[u] + 1, -1);
				a.add(lb[v] + 1, -1);
				a.add(lb[p] + 1, 2);
			}
			else {
				b.add(lb[u] + 1, -1);
				b.add(lb[v] + 1, -1);
				b.add(lb[p] + 1, 2);
			}
		}
	for (int i = 0; i < cnt; i += 2)
		if (on[i]) {
			int u;
			if (dep[end[i]] > dep[end[i ^ 1]]) u = end[i]; else u = end[i ^ 1];
			int s1 = a.sum(lb[u]) - a.sum(rb[u]), s2 = b.sum(lb[u]) - b.sum(rb[u]);
			if (s1 == err && ((s1 != 0 && s2 == 0) || (s1 == 0))) ans.push_back(i >> 1);
		}
	sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	for (int i = 0; i < int(ans.size()); ++ i) {
		if (i) printf(" ");
		printf("%d", ans[i] + 1);
	}
	puts("");
	return 0;
}
