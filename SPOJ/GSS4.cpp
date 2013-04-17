#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int kMaxN = 100000;
int n, m;
ll seq[kMaxN];

struct Node {
	ll v, s;
	Node *son[2];
	void update() {
		v = max(son[0]->v, son[1]->v);
		s = son[0]->s + son[1]->s;
	}
} node_pool[kMaxN * 2 - 1], *node_idx, *root;

Node *BuildTree(int l, int r) {
	Node *res = node_idx ++;
	if (l + 1 == r) {
		res->son[0] = res->son[1] = NULL;
		res->v = res->s = seq[l];
	}
	else {
		int mid = (l + r) >> 1;
		res->son[0] = BuildTree(l, mid);
		res->son[1] = BuildTree(mid, r);
		res->update();
	}
	return res;
}

void ChangeOnRange(int l, int r, Node *pos, int pos_l, int pos_r) {
	if (pos->v == 1) return;
	if (pos_l + 1 == pos_r) {
		pos->s = pos->v = (ll)(floor(sqrt(pos->v)) + 0.5);
		return;
	}
	int mid = (pos_l + pos_r) >> 1;
	if (l < mid) ChangeOnRange(l, r, pos->son[0], pos_l, mid);
	if (r > mid) ChangeOnRange(l, r, pos->son[1], mid, pos_r);
	pos->update();
}

ll AskOnRange(int l, int r, Node *pos, int pos_l, int pos_r) {
	if (l >= pos_r || r <= pos_l) return 0;
	if (l <= pos_l && r >= pos_r) return pos->s;
	int mid = (pos_l + pos_r) >> 1;
	return (AskOnRange(l, r, pos->son[0], pos_l, mid) + AskOnRange(l, r, pos->son[1], mid, pos_r));
}

int main() {
	int TST = 0;
	while (scanf("%d", &n) != EOF) {
		printf("Case #%d:\n", ++ TST);
		for (int i = 0; i < n; ++ i) scanf("%lld", &seq[i]);
		node_idx = node_pool, root = BuildTree(0, n);
		scanf("%d", &m);
		for (int t, l, r; m --; ) {
			scanf("%d%d%d", &t, &l, &r);
			if (l > r) swap(l, r);
			-- l;
			if (t == 0) ChangeOnRange(l, r, root, 0, n);
			else printf("%lld\n", AskOnRange(l, r, root, 0, n));
		}
		puts("");
	}
	return 0;
}
