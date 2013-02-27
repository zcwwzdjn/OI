#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 1000, kMaxK = 30;
int n, k, x[kMaxN], y[kMaxN];
int dis[kMaxN][kMaxN];
bool del[kMaxN];
int bel[kMaxN];
int s1[kMaxN], d1, s2[kMaxN], d2;
bool mark[kMaxN];
int rec[kMaxN];
int mat[kMaxN];

struct Pair {
	int u, v;
	Pair() {}
	Pair(int u_, int v_) : u(u_), v(v_) {}
} seq[kMaxN * (kMaxN + 1) / 2];
int idx;

bool Cmp(const Pair &a, const Pair &b) {
	return (dis[a.u][a.v] > dis[b.u][b.v]);
}

namespace flow {
#define OP(x) ((x) ^ 1)
	const int kInf = 0x3f3f3f3f;
	const int kMaxV = kMaxN + 2, kMaxE = (kMaxN + kMaxN * kMaxN) * 2;
	int cnt, begin[kMaxV], end[kMaxE], next[kMaxE], cap[kMaxE];
	int s, t, label[kMaxV], start[kMaxV], q[kMaxV], qh, qt, stack[kMaxV], edge[kMaxV], stop;
	int maxflow;

	void Init(int s_, int t_) {
		cnt = 0;
		memset(begin, -1, sizeof(int) * (n + 2));
		s = s_, t = t_;
	}

	void AddEdge(int u, int v, int c) {
		next[cnt] = begin[u];
		begin[u] = cnt;
		end[cnt] = v;
		cap[cnt ++] = c;
	}

	void AddPair(int u, int v, int c) {
		AddEdge(u, v, c);
		AddEdge(v, u, 0);
	}

	bool Relabel() {
		qh = qt = 0;
		memset(label, -1, sizeof(label));
		for (label[s] = 0, start[s] = begin[s], q[qt ++] = s; qh < qt; ) {
			int u = q[qh ++];
			for (int now = begin[u], v; now != -1; now = next[now])
				if (cap[now] && label[v = end[now]] < 0) {
					label[v] = label[u] + 1;
					start[v] = begin[v];
					q[qt ++] = v;
				}
		}
		return (label[t] != -1);
	}

	void DoAug() {
		stop = 0;
		stack[stop ++] = s;
		while (stop) {
			int u = stack[stop - 1];
			if (u != t) {
				int &now = start[u], v;
				for ( ; now != -1; now = next[now])
					if (cap[now] && label[v = end[now]] == label[u] + 1) break;
				if (now >= 0) {
					stack[stop] = v;
					edge[stop ++] = now;
				}
				else {
					-- stop;
					label[u] = -1;
				}
			}
			else {
				int flow = kInf;
				for (int i = stop - 1; i >= 1; -- i)
					flow = min(flow, cap[edge[i]]);
				for (int i = stop - 1; i >= 1; -- i) {
					cap[edge[i]] -= flow, cap[OP(edge[i])] += flow;
					if (!cap[edge[i]]) stop = i;
				}
				maxflow += flow;
			}
		}
	}

	int Maxflow() {
		maxflow = 0;
		while (Relabel()) DoAug();
		return maxflow;
	}

	bool Check(int lim) {
		maxflow = 0;
		while (Relabel()) {
			DoAug();
			if (maxflow > lim) return false;
		}
		return true;
	}
#undef OP
}

void Dfs(int u) {
	mark[u] = true;
	for (int now = flow::begin[u], v; now != -1; now = flow::next[now])
		if ((v = flow::end[now]) < n && !mark[v] && !flow::cap[now]) {
			mark[v] = true;
			if (mat[v] != -1 && !mark[mat[v]]) Dfs(mat[v]);
		}
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++ i) scanf("%d%d", &x[i], &y[i]);
	for (int i = 0; i < n; ++ i)
		for (int j = i; j < n; ++ j) {
			int dx = x[i] - x[j], dy = y[i] - y[j];
			dis[j][i] = dis[i][j] = dx * dx + dy * dy;
			seq[idx ++] = Pair(i, j);
		}
	sort(seq, seq + idx, Cmp);
	int req = 0;
	for (int i = 1; i <= k; ++ i) req += n - i;
	++ req;
	req = min(req, idx);
	for (int i = req - 1; i >= 0; -- i) {
		memset(del, false, n);
		int u = seq[i].u, v = seq[i].v;
		int cnt = 0, lim = dis[u][v];
		for (int j = 0; j < n; ++ j)
			if (dis[j][u] > lim || dis[j][v] > lim) {
				del[j] = true;
				if ((++ cnt) > k) break;
			}
		if (cnt > k) continue;
		d1 = d2 = 0;
		int x1 = x[u] - x[v], y1 = y[u] - y[v];
		flow::Init(n, n + 1);
		for (int j = 0; j < n; ++ j)
			if (!del[j] && j != u && j != v) {
				int x2 = x[j] - x[v], y2 = y[j] - y[v];
				if (x1 * y2 - x2 * y1 >= 0) bel[j] = 0, rec[j] = flow::cnt, flow::AddPair(n, j, 1), s1[d1 ++] = j;
				else bel[j] = 1, rec[j] = flow::cnt, flow::AddPair(j, n + 1, 1), s2[d2 ++] = j;
			}
			else bel[j] = -1;
		for (int j = 0; j < i; ++ j) {
			int a = seq[j].u, b = seq[j].v;
			if (dis[a][b] > lim && bel[a] != -1 && bel[b] != -1 && bel[a] != bel[b]) {
				if (bel[a] == 1) swap(a, b);
				flow::AddPair(a, b, 1);
			}
		}
		bool succ = flow::Check(k - cnt);
		if (succ) {
			static int ans[kMaxN], m;
			for (int j = 0; j < n; ++ j)
				if (del[j]) ans[m ++] = j;
			k -= m;
			for (int j = 0; j < d1; ++ j) mark[s1[j]] = false;
			for (int l = 0; l < d2; ++ l) mark[s2[l]] = false;
			for (int j = 0; j < d1; ++ j) {
				mat[s1[j]] = -1;
				if (flow::cap[rec[s1[j]]]) continue;
				for (int now = flow::begin[s1[j]]; now != -1; now = flow::next[now])
					if (flow::cap[now] == 0) {
						mat[s1[j]] = flow::end[now];
						break;
					}
			}
			for (int l = 0; l < d2; ++ l)
				if (flow::cap[rec[s2[l]]]) Dfs(s2[l]);
			for (int l = 0; l < d2; ++ l)
				if (!mark[s2[l]]) {
					ans[m ++] = s2[l];
					-- k;
				}
			for (int j = 0; j < d1; ++ j)
				if (mark[s1[j]]) {
					ans[m ++] = s1[j];
					-- k;
				}
			for (int j = 0; j < n && k; ++ j)
				if (!del[j] && j != u && j != v) {
					ans[m ++] = j;
					-- k;
				}
			for (int j = 0; j < m; ++ j) {
				printf("%d", ans[j] + 1);
				if (j + 1 == k) printf("\n");
				else printf(" ");
			}
			break;
		}
	}
	return 0;
}
