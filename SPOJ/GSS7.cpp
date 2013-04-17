#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 100000;
int n, seq[kMaxN], cnt, begin[kMaxN], end[(kMaxN - 1) * 2], next[(kMaxN - 1) * 2];
int q[kMaxN], qh, qt, dep[kMaxN], par[kMaxN], sz[kMaxN], hvst[kMaxN], jump[kMaxN];
int buf[kMaxN], buf_idx;
int m;

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

struct Info {
	int s, v, lv, rv, l;
	Info() {}
	Info(int s_, int v_, int lv_, int rv_, int l_) : s(s_), v(v_), lv(lv_), rv(rv_), l(l_) {}
};

struct Mark {
	bool e;
	int v;
	Mark() : e(false) {}
	Mark(bool e_, int v_) : e(e_), v(v_) {}
};

Info operator + (const Info &a, const Info &b) {
	return Info(a.s + b.s, max(a.rv + b.lv, max(a.v, b.v)), max(a.lv, a.s + b.lv), max(b.rv, b.s + a.rv), a.l + b.l);
}

Info operator * (const Info &a, const Mark &b) {
	if (!b.e) return a;
	else return (b.v >= 0 ? Info(b.v * a.l, b.v * a.l, b.v * a.l, b.v * a.l, a.l) : Info(b.v * a.l, b.v, b.v, b.v, a.l));
}

Mark operator * (const Mark &a, const Mark &b) {
	if (!b.e) return a; else return b;
}

struct Node {
	Info info;
	Mark mark;
	int l, r;
	Node *son[2];
	void update() {
		info = son[0]->info + son[1]->info;
	}
} node_pool[kMaxN * 2 - 1], *node_idx = node_pool, *root[kMaxN];

Node *BuildTree(int l, int r) {
	Node *res = node_idx ++;
	res->l = l, res->r = r;
	if (l == r) {
		int v = seq[buf[dep[buf[0]] - l]];
		res->info = Info(v, max(v, 0), max(v, 0), max(v, 0), 1);
	}
	else {
		int mid = (l + r) >> 1;
		res->son[0] = BuildTree(l, mid);
		res->son[1] = BuildTree(mid + 1, r);
		res->update();
	}
	return res;
}

void DoPush(Node *pos, const Mark &p) {
	if (pos && p.e) {
		pos->info = pos->info * p;
		pos->mark = pos->mark * p;
	}
}

void Push(Node *pos) {
	if (pos && pos->mark.e) {
		DoPush(pos->son[0], pos->mark);
		DoPush(pos->son[1], pos->mark);
		pos->mark.e = false;
	}
}

void ChangeOnRange(int l, int r, const Mark &p, Node *pos) {
	if (l > pos->r || r < pos->l) return;
	if (l <= pos->l && r >= pos->r) {
		DoPush(pos, p);
		return;
	}
	Push(pos);
	ChangeOnRange(l, r, p, pos->son[0]);
	ChangeOnRange(l, r, p, pos->son[1]);
	pos->update();
}

Info AskOnRange(int l, int r, Node *pos) {
	if (l > pos->r || r < pos->l) return Info(0, 0, 0, 0, 0);
	if (l <= pos->l && r >= pos->r) return pos->info;
	Push(pos);
	return (AskOnRange(l, r, pos->son[0]) + AskOnRange(l, r, pos->son[1]));
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

void Change(int u, int p, const Mark &_) {
	for ( ; root[u] != root[p]; u = jump[u])
		ChangeOnRange(0, dep[u], _, root[u]);
	if (dep[p] <= dep[u])
		ChangeOnRange(dep[p], dep[u], _, root[u]);
}

Info Ask(int u, int p, bool t) {
	Info res(0, 0, 0, 0, 0);
	for ( ; root[u] != root[p]; u = jump[u])
		res = AskOnRange(0, dep[u], root[u]) + res;
	if (dep[p] + t <= dep[u])
		res = AskOnRange(dep[p] + t, dep[u], root[u]) + res;
	if (t) swap(res.lv, res.rv);
	return res;
}

int main() {
	memset(begin, -1, sizeof(begin));
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d", &seq[i]);
	for (int u, v, i = 0; i < n - 1; ++ i) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		AddEdge(u, v);
		AddEdge(v, u);
	}
	par[q[qt ++] = 0] = -1;
	while (qh < qt) {
		int u = q[qh ++];
		for (int now = begin[u], v; now != -1; now = next[now])
			if ((v = end[now]) != par[u]) {
				par[q[qt ++] = v] = u;
				dep[v] = dep[u] + 1;
			}
	}
	memset(hvst, -1, sizeof(hvst));
	for (int i = n - 1; i >= 0; -- i) {
		int u = q[i];
		++ sz[u];
		if (par[u] != -1) {
			sz[par[u]] += sz[u];
			if (hvst[par[u]] == -1 || sz[u] > sz[hvst[par[u]]])
				hvst[par[u]] = u;
		}
	}
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
	scanf("%d", &m);
	for (int t, a, b, c; m --; ) {
		scanf("%d%d%d", &t, &a, &b);
		-- a, -- b;
		int p = Lca(a, b);
		if (t == 1) printf("%d\n", (Ask(a, p, 1) + Ask(b, p, 0)).v);
		else {
			scanf("%d", &c);
			Change(a, p, Mark(1, c));
			Change(b, p, Mark(1, c));
		}
	}
	return 0;
}
