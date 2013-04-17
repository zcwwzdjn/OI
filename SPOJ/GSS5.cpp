#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 10000, kInf = 0x3f3f3f3f;
int n, seq[kMaxN];
int m;

struct Info {
	int s, v, lv, rv;
	Info() {}
	Info(int s_, int v_, int lv_, int rv_) : s(s_), v(v_), lv(lv_), rv(rv_) {}
};

Info operator + (const Info &a, const Info &b) {
	return Info(a.s + b.s, max(a.rv + b.lv, max(a.v, b.v)), max(a.lv, a.s + b.lv), max(b.rv, b.s + a.rv));
}

struct Node {
	Info info;
	Node *son[2];
	void update() {
		info = son[0]->info + son[1]->info;
	}
} node_pool[kMaxN * 2 - 1], *node_idx, *root;

Node *BuildTree(int l, int r) {
	Node *res = node_idx ++;
	if (l + 1 == r) {
		res->son[0] = res->son[1] = NULL;
		res->info = Info(seq[l], seq[l], seq[l], seq[l]);
	}
	else {
		int mid = (l + r) >> 1;
		res->son[0] = BuildTree(l, mid);
		res->son[1] = BuildTree(mid, r);
		res->update();
	}
	return res;
}

Info AskOnRange(int l, int r, Node *pos, int pos_l, int pos_r) {
	if (l >= pos_r || r <= pos_l) return Info(0, -kInf, -kInf, -kInf);
	if (l <= pos_l && r >= pos_r) return pos->info;
	int mid = (pos_l + pos_r) >> 1;
	return (AskOnRange(l, r, pos->son[0], pos_l, mid) + AskOnRange(l, r, pos->son[1], mid, pos_r));
}

int main() {
	int TST;
	for (scanf("%d", &TST); TST --; ) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++ i) scanf("%d", &seq[i]);
		node_idx = node_pool, root = BuildTree(0, n);
		scanf("%d", &m);
		for (int x1, y1, x2, y2, res; m --; ) {
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			-- x1, -- x2;
			if (y1 <= x2)
				res = AskOnRange(x1, y1, root, 0, n).rv + (y1 == x2 ? 0 : AskOnRange(y1, x2, root, 0, n).s) + AskOnRange(x2, y2, root, 0, n).lv;
			else {
				res = AskOnRange(x2, y1, root, 0, n).v;
				if (x1 < x2) res = max(res, AskOnRange(x1, x2, root, 0, n).rv + AskOnRange(x2, y2, root, 0, n).lv);
				if (y1 < y2) res = max(res, AskOnRange(y1, y2, root, 0, n).lv + AskOnRange(x1, y1, root, 0, n).rv);
			}
			printf("%d\n", res);
		}
	}
	return 0;
}
