#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 100000, kMaxM = kMaxN - 1;
int n, m, anc[17][kMaxN], r, rec[kMaxN];
int lb[kMaxN], rb[kMaxN], dcnt;
int cnt, begin[kMaxN], end[kMaxM], next[kMaxM], dep[kMaxN];

void AddEdge(int u, int v) {
	next[cnt] = begin[u];
	begin[u] = cnt;
	end[cnt ++] = v;
}

void Dfs() {
	static int stack[kMaxN], start[kMaxN];
	int stop = 0;
	start[stack[stop ++] = r] = begin[r];
	memset(lb, -1, sizeof(lb));
	memset(rb, -1, sizeof(rb));
	while (stop) {
		int u = stack[stop - 1];
		int &now = start[u], v;
		if (lb[u] == -1) lb[u] = dcnt ++;
		if (now == -1) {
			-- stop;
			rb[u] = dcnt ++;
			continue;
		}
		v = end[now];
		now = next[now];
		dep[v] = dep[u] + 1;
		start[stack[stop ++] = v] = begin[v];
	}
}	

int Lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int delta = dep[u] - dep[v];
	for (int d = 16; d >= 0; -- d)
		if (delta >> d & 1) u = anc[d][u];
	for (int d = 16; d >= 0; -- d)
		if (anc[d][u] != anc[d][v]) u = anc[d][u], v = anc[d][v];
	if (u != v) u = anc[0][u];
	return u;
}

int Anc(int u, int s) {
	for (int d = 16; d >= 0; -- d)
		if (s >> d & 1) u = anc[d][u];
	return u;
}

namespace sgt {
	struct Node {
		int v;
		Node *son[2];
		Node() : v(0) {
			son[0] = son[1] = NULL;
		}
		void update() {
			v = son[0]->v + son[1]->v;
		}
	};

	Node *Alloc(int v) {
		Node *res = new Node;
		res->v = v;
		return res;
	}

	Node *BuildTree(int l, int r) {
		Node *res = Alloc(0);
		if (l + 1 < r) {
			int mid = (l + r) >> 1;
			res->son[0] = BuildTree(l, mid);
			res->son[1] = BuildTree(mid, r);
		}
		return res;
	}

	Node *Insert(int x, int v, Node *pos, int pos_l, int pos_r) {
		Node *res = Alloc(0);
		if (pos_l + 1 == pos_r) {
			res->v = v;
			return res;
		}
		int mid = (pos_l + pos_r) >> 1;
		if (x < mid) {
			res->son[0] = Insert(x, v, pos->son[0], pos_l, mid);
			res->son[1] = pos->son[1];
		}
		else {
			res->son[0] = pos->son[0];
			res->son[1] = Insert(x, v, pos->son[1], mid, pos_r);
		}
		return (res->update(), res);
	}

	int Ask(int l, int r, Node *pos, int pos_l, int pos_r) {
		if (l <= pos_l && r >= pos_r) return pos->v;
		int mid = (pos_l + pos_r) >> 1;
		if (l >= mid) return Ask(l, r, pos->son[1], mid, pos_r);
		if (r <= mid) return Ask(l, r, pos->son[0], pos_l, mid);
		return (Ask(l, r, pos->son[0], pos_l, mid) + Ask(l, r, pos->son[1], mid, pos_r));
	}
}

sgt::Node *root[kMaxN + 1];

int Count(sgt::Node *root, int u, int v, int p, int y) {
	int a = sgt::Ask(0, lb[u] + 1, root, 0, n * 2);
	int b = sgt::Ask(0, lb[v] + 1, root, 0, n * 2);
	int c = sgt::Ask(0, lb[p] + 1, root, 0, n * 2);
	int res = a + b - c * 2 + (rec[p] <= y);
	return res;
}

int main() {
	memset(begin, -1, sizeof(begin));
	scanf("%d", &n);
	memset(anc, -1, sizeof(anc));
	for (int i = 0; i < n; ++ i) {
		scanf("%d", &anc[0][i]);
		-- anc[0][i];
		if (anc[0][i] == -1) r = i;
		else AddEdge(anc[0][i], i);
	}
	for (int d = 1; d < 17; ++ d)
		for (int i = 0; i < n; ++ i)
			if (anc[d - 1][i] != -1) anc[d][i] = anc[d - 1][anc[d - 1][i]];
	Dfs();
	root[0] = sgt::BuildTree(0, n * 2);
	scanf("%d", &m);
	for (int t = 1; t <= m; ++ t) {
		int cmd;
		scanf("%d", &cmd);
		if (cmd == 1) {
			int c;
			scanf("%d", &c);
			-- c;
			sgt::Node *pos = root[t - 1];
			pos = sgt::Insert(lb[c], 1, pos, 0, n * 2);
			pos = sgt::Insert(rb[c], -1, pos, 0, n * 2);
			root[t] = pos;
			rec[c] = t;
		}
		else {
			root[t] = root[t - 1];
			int a, b, k, y;
			scanf("%d%d%d%d", &a, &b, &k, &y);
			-- a, -- b;
			int p = Lca(a, b);
			int d = Count(root[t], a, b, p, t) - Count(root[y], a, b, p, y);
			int tot = dep[a] + dep[b] - dep[p] * 2 + 1 - d;
			bool ban_a = (rec[a] > y);
			bool ban_b = (rec[b] > y);
			if (!ban_a) -- tot;
			if (!ban_b) -- tot;
			if (tot < k) puts("-1");
			else {
				int u;
				if (p == a || p == b) {
					if (p == a) u = b, k = tot - k + 1;
					else u = a;
				}
				else {
					int left = dep[a] - dep[p] + 1 - (Count(root[t], a, p, p, t) - Count(root[y], a, p, p, y));
					if (!ban_a) -- left;
					if (left >= k) u = a;
					else {
						u = b;
						k = tot - k + 1;
					}
				}
				int lb = 0, rb = dep[u] - dep[p] + 1;
				bool ban = (u == a ? ban_a : ban_b);
				while (lb + 1 < rb) {
					int mid = (lb + rb) >> 1;
					int tmp = Anc(u, mid);	
					int pmt = Count(root[t], u, tmp, tmp, t) - Count(root[y], u, tmp, tmp, y);
					pmt = dep[u] - dep[tmp] + 1 - pmt;
					if (!ban) -- pmt;
					bool bbb = (rec[tmp] > y);
					if (bbb) ++ pmt;
					if (pmt <= k) lb = mid;
					else rb = mid;
				}
				printf("%d\n", Anc(u, lb) + 1);
			}
		}
	}
	return 0;
}
