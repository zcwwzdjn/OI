#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 2000, kMaxM = 200000;
int n, m, cnt, begin[kMaxN], end[kMaxM], next[kMaxM];
int dcnt, dfn[kMaxN], low[kMaxN];
bool use[kMaxM], bri[kMaxM], vis[kMaxN];
int ans = -1;
vector<int> tr[kMaxN], a[kMaxN];
int bcnt, bel[kMaxN], sz;
int f[kMaxN], g[kMaxN][2], pre[kMaxN], h[kMaxN];
int add;
bool vv[kMaxN];

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

void Dfs(int u) {
	low[u] = dfn[u] = ++ dcnt;
	for (int now = begin[u], v; now != -1; now = next[now]) {
		if (use[now]) continue;
		use[now] = use[now ^ 1] = true;
		if (!dfn[v = end[now]]) {
			Dfs(v);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) bri[now] = bri[now ^ 1] = true;
		}
		else
			low[u] = min(low[u], dfn[v]);
	}
}

void Dfs2(int u) {
	++ sz;
	vis[u] = true;
	bel[u] = bcnt;
	for (int now = begin[u], v; now != -1; now = next[now])
		if (!vis[v = end[now]] && !bri[now]) Dfs2(v);
}

void Dfs3(int u) {
	vis[u] = true;
	int son = 0;
	for (vector<int>::iterator it = tr[u].begin(); it != tr[u].end(); ++ it) {
		int v = *it;
		if (!vis[v]) {
			pre[v] = u;
			Dfs3(v);
			++ son;
			a[u].push_back(v);
		}
	}
	if (!son) f[u] = 0;
	else if (son == 1) f[u] = 1 + f[a[u][0]];
	else {
		f[u] = 1;
		for (int i = 0; i < son; ++ i) {
			f[u] += f[a[u][i]];
		}
	}
}

void Dfs5(int u, int fb) {
	vv[u] = true;
	int son = 0;
	vector<int> b;
	for (vector<int>::iterator it = tr[u].begin(); it != tr[u].end(); ++ it) {
		int v = *it;
		if (!vv[v]) {
			Dfs5(v, fb);
			b.push_back(v);
			++ son;
		}
	}
	if (!son) h[u] = 0;
	else if (son == 1) h[u] = 1 + h[b[0]];
	else {
		h[u] = 1;
		for (int i = 0; i < son; ++ i) {
			h[u] += h[b[i]];
		}
	}
}

int Solve(int p, int forbid) {
	memset(vv, false, sizeof(vv));
	vv[forbid] = true;
	Dfs5(p, forbid);
	return h[p];
}

void Dfs4(int u) {
	int son = a[u].size();
	for (int i = 0; i < son; ++ i) Dfs4(a[u][i]);
	if (son == 0) g[u][0] = 0;
	else {
		int tot = 0;
		for (int i = 0; i < son; ++ i) tot += f[a[u][i]];
		for (int i = 0; i < son - 1; ++ i)
			for (int j = i + 1; j < son; ++ j)
				g[u][1] = min(g[u][1], g[a[u][i]][0] + g[a[u][j]][0] + tot - f[a[u][i]] - f[a[u][j]]);
		for (int i = 0; i < son; ++ i)
			g[u][0] = min(g[u][0], g[a[u][i]][0] + tot - f[a[u][i]]);
	}
	add = min(add, min(g[u][0], g[u][1]) + (pre[u] != -1 ? Solve(pre[u], u) : 0));
}

void Check(int o) {
	pre[o] = -1;
	Dfs3(o);
	add = 0x3f3f3f3f;
	Dfs4(o);	
	ans += add;
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
		if (!dfn[i]) {
			Dfs(i);
			++ ans;
		}
	memset(bel, -1, sizeof(bel));
	for (int i = 0; i < n; ++ i)
		if (!vis[i]) {
			sz = 0;
			Dfs2(i);
			++ bcnt;
			ans += sz - 1;
		}
	for (int i = 0; i < cnt; i += 2)
		if (bri[i]) {
			int u = end[i], v = end[i ^ 1];
			tr[bel[u]].push_back(bel[v]);
			tr[bel[v]].push_back(bel[u]);
		}
	memset(f, 0x3f, sizeof(f));
	memset(g, 0x3f, sizeof(g));
	memset(vis, false, sizeof(vis));
	for (int i = 0; i < bcnt; ++ i)
		if (!vis[i]) {
			Check(i);
		}
	printf("%d\n", ans);
	return 0;
}
