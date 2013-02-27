#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> Pair;
const int kInf = 0x3f3f3f3f;
const int kMaxN = 100000, kMod = 1000000009;
int n, k, a, b, c, d, m;
Pair p[kMaxN];

struct Info {
	int a, b;
	Info() : a(0), b(0) {}
	Info(int a_, int b_) : a(a_), b(b_) {}
};

Info operator + (const Info &a, const Info &b) {
	return Info(max(a.a, a.b) + max(b.a, b.b), 1 + max(a.a + b.b, a.b + b.a));
}

#undef NULL
#define NULL Node::nil

struct Node {
	int l, r, mid;
	Info info;
	Node *son[2];
	Node() {
		son[0] = son[1] = NULL;
	}
	void update() {
		info = son[0]->info + son[1]->info;
	}
	static Node nil_ins, *nil;
} node_pool[kMaxN], *node_idx = node_pool, *root = NULL;

Node Node::nil_ins;
Node *Node::nil = &nil_ins;

Node *BuildTree(int l, int r) {
	if (l > r) return NULL;
	Node *res = node_idx ++;
	res->l = l, res->r = r;
	if (l == r) res->mid = l;
	else {
		int mid = l;
		for (int i = l + 1; i <= r; ++ i)
			if (p[i].second > p[mid].second) mid = i;
		res->mid = mid;
		res->son[0] = BuildTree(l, mid - 1);
		res->son[1] = BuildTree(mid + 1, r);
		res->update();
	}
	return res;
}

Info Ask(int l, int r, Node *pos = root) {
	if (pos == NULL || l > pos->r || r < pos->l) return (NULL->info);
	if (l <= pos->l && r >= pos->r) return pos->info;
	int mid = pos->mid;
	if (r < mid) return Ask(l, r, pos->son[0]);
	if (l > mid) return Ask(l, r, pos->son[1]);
	return (Ask(l, r, pos->son[0]) + Ask(l, r, pos->son[1]));
}

int Query(int l, int r) {
	if (l > r) return 0;
	Info res = Ask(l, r);
	return (max(res.a, res.b));
}

int main() {
	NULL->info = Info(-1, 0);
	scanf("%d%d", &n, &k);
	for (int i = 0; i < k; ++ i) scanf("%d%d", &p[i].first, &p[i].second);
	scanf("%d%d%d%d", &a, &b, &c, &d);
	for (int i = k; i < n; ++ i) {
		p[i].first = ((long long)p[i - 1].first * a + b) % kMod;
		p[i].second = ((long long)p[i - 1].second * c + d) % kMod;
	}
	sort(p, p + n);
	root = BuildTree(0, n - 1);
	scanf("%d", &m);
	for (int l, r; m --; ) {
		scanf("%d%d", &l, &r);
		int lb = lower_bound(p, p + n, make_pair(l, 0)) - p;
		int rb = lower_bound(p, p + n, make_pair(r, kMod)) - p;
		-- rb;
		printf("%d\n", Query(lb, rb));
	}
	return 0;
}
