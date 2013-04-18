#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 10000, kInf = 0x3f3f3f3f;
int n, seq[kMaxN], cnt, begin[kMaxN], end[(kMaxN - 1) * 2], next[(kMaxN - 1) * 2], cost[(kMaxN - 1) * 2], bel[kMaxN - 1];
int q[kMaxN], qh, qt, dep[kMaxN], par[kMaxN], sz[kMaxN], hvst[kMaxN], jump[kMaxN];
int buf[kMaxN], buf_idx;

void AddEdge(int u, int v, int c) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt] = v;
	cost[cnt ++] = c;
}

struct Node {
	int l, r, v;
	Node *son[2];
	void update() {
		v = max(son[0]->v, son[1]->v);
	}
} node_pool[kMaxN * 2 - 1], *node_idx, *root[kMaxN];

Node *BuildTree(int l, int r) {
	Node *res = node_idx ++;
	res->l = l, res->r = r;
	if (l == r) res->v = seq[buf[dep[buf[0]] - l]];
	else {
		int mid = (l + r) >> 1;
		res->son[0] = BuildTree(l, mid);
		res->son[1] = BuildTree(mid + 1, r);
		res->update();
	}
	return res;
}

void ChangeOnPoint(int x, int v, Node *pos) {
	if (pos->l == pos->r) {
		pos->v = v;
		return;
	}
	int mid = (pos->l + pos->r) >> 1;
	if (x <= mid) ChangeOnPoint(x, v, pos->son[0]);
	else ChangeOnPoint(x, v, pos->son[1]);
	pos->update();
}

int AskOnRange(int l, int r, Node *pos) {
	if (l > pos->r || r < pos->l) return -kInf;
	if (l <= pos->l && r >= pos->r) return pos->v;
	return max(AskOnRange(l, r, pos->son[0]), AskOnRange(l, r, pos->son[1]));
}

int Lca(int u, int v) {
	while (root[u] != root[v]) {
		int x = jump[u], y = jump[v];
		if (y != -1)
			if (x == -1 || dep[x] < dep[y]) swap(u, v), swap(x, y);
		u = x;
	}
	if (dep[u] > dep[v]) swap(u, v);
	return u;
}

int Ask(int u, int p) {
	int res = -kInf;
	for ( ; root[u] != root[p]; u = jump[u])
		res = max(res, AskOnRange(0, dep[u], root[u]));
	if (dep[p] + 1 <= dep[u])
		res = max(res, AskOnRange(dep[p] + 1, dep[u], root[u]));
	return res;
}

int main() {
	int TST;
	scanf("%d", &TST);
	while (TST --) {
		cnt = 0, memset(begin, -1, sizeof(begin));
		scanf("%d", &n);
		for (int u, v, c, i = 0; i < n - 1; ++ i) {
			scanf("%d%d%d", &u, &v, &c);
			-- u, -- v;
			AddEdge(u, v, c);
			AddEdge(v, u, c);
		}
		seq[0] = -kInf;
		qh = qt = 0;
		par[q[qt ++] = 0] = -1;
		while (qh < qt) {
			int u = q[qh ++];
			for (int now = begin[u], v; now != -1; now = next[now])
				if ((v = end[now]) != par[u]) {
					bel[now >> 1] = v;
					seq[v] = cost[now];
					par[q[qt ++] = v] = u;
					dep[v] = dep[u] + 1;
				}
		}
		memset(hvst, -1, sizeof(hvst));
		memset(sz, 0, sizeof(sz));
		for (int i = n - 1; i >= 0; -- i) {
			int u = q[i];
			++ sz[u];
			if (par[u] != -1) {
				sz[par[u]] += sz[u];
				if (hvst[par[u]] == -1 || sz[u] > sz[hvst[par[u]]])
					hvst[par[u]] = u;
			}
		}
		memset(root, 0, sizeof(root));
		node_idx = node_pool;
		for (int i = n - 1; i >= 0; -- i) {
			int u = q[i];
			if (root[u]) continue;
			buf_idx = 0;
			int p = u;
			do {
				buf[buf_idx ++] = p;
				if (par[p] == -1 || hvst[par[p]] != p) break;
				p = par[p];
			} while (true);
			Node *tmp = BuildTree(dep[buf[buf_idx - 1]], dep[buf[0]]);
			for (int j = 0; j < buf_idx; ++ j) {
				jump[buf[j]] = par[p];
				root[buf[j]] = tmp;
			}
		}
		static char cmd[8];
		static int a, b;
		while (scanf("%s", cmd) != EOF && cmd[0] != 'D') {
			scanf("%d%d", &a, &b);
			if (cmd[0] == 'C') {
				a = bel[a - 1];
				ChangeOnPoint(dep[a], b, root[a]);
			}
			else {
				-- a, -- b;
				int p = Lca(a, b);
				printf("%d\n", max(Ask(a, p), Ask(b, p)));
			}
		}
	}
	return 0;
}
