#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 50000, kInf = 0x3f3f3f3f;
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
} node_pool[kMaxN * 2 - 1], *node_idx = node_pool, *root = NULL;

Node *BuildTree(int l, int r) {
	Node *res = node_idx ++;
	if (l + 1 == r) res->info = Info(seq[l], seq[l], seq[l], seq[l]);
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
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d", &seq[i]);
	root = BuildTree(0, n);
	scanf("%d", &m);
	for (int l, r; m --; ) {
		scanf("%d%d", &l, &r);
		-- l;
		printf("%d\n", AskOnRange(l, r, root, 0, n).v);
	}
	return 0;
}
