#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 100000;
int n, m, seq[kMaxN], pos[kMaxN], r;

struct Node {
	int cnt;
	Node *son[2];
	void update() {
		cnt = son[0]->cnt + son[1]->cnt;
	}
} node_pool[kMaxN * 2 - 1 + kMaxN * 18], *node_idx = node_pool;

Node *memo[kMaxN + 1], **at = memo + 1;

Node *BuildTree(int l, int r) {
	Node *res = node_idx ++;
	if (l + 1 < r) {
		int mid = (l + r) >> 1;
		res->son[0] = BuildTree(l, mid);
		res->son[1] = BuildTree(mid, r);
	}
	return res;
}

Node *Insert(int x, Node *pos, int pos_l, int pos_r) {
	if (pos_l + 1 == pos_r) {
		Node *res = node_idx ++;
		res->cnt = pos->cnt + 1;
		return res;
	}
	Node *res = node_idx ++;
	int mid = (pos_l + pos_r) >> 1;
	if (x < mid) {
		res->son[0] = Insert(x, pos->son[0], pos_l, mid);
		res->son[1] = pos->son[1];
	}
	else {
		res->son[0] = pos->son[0];
		res->son[1] = Insert(x, pos->son[1], mid, pos_r);
	}
	return res->update(), res;
}

int Find(int k, Node *l, Node *r, int pos_l, int pos_r) {
	if (pos_l + 1 == pos_r) return pos_l;
	int mid = (pos_l + pos_r) >> 1;
	if (r->son[0]->cnt - l->son[0]->cnt >= k)
		return Find(k, l->son[0], r->son[0], pos_l, mid);
	else
		return Find(k - (r->son[0]->cnt - l->son[0]->cnt), l->son[1], r->son[1], mid, pos_r);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i) {
		scanf("%d", &seq[i]);
		pos[i] = seq[i];
	}
	sort(pos, pos + n);
	r = unique(pos, pos + n) - pos;
	for (int i = 0; i < n; ++ i) seq[i] = lower_bound(pos, pos + r, seq[i]) - pos;
	at[-1] = BuildTree(0, r);
	for (int i = 0; i < n; ++ i) at[i] = Insert(seq[i], at[i - 1], 0, r);
	for (int a, b, k; m --; ) {
		scanf("%d%d%d", &a, &b, &k);
		-- a, -- b;
		printf("%d\n", pos[Find(k, at[a - 1], at[b], 0, r)]);
	}
	return 0;
}
